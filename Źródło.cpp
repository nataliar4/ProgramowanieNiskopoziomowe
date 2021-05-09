#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std::chrono;

int losowaLiczba(int min, int max);
void wypelnijLosowymi(int* tablica, int rozmiar = 300, int min = 0, int max = 1000);
int* wygenerujTablice(int* losowe, int rozmiar = 300);
void sortowanieBabelkoweTablica(int* tablica, int rozmiar = 300);
double pomiar(int* tablica, int rozmiar, void(*sort)(int*, int));
void stoguj(int* tablica, int rozmiar, int i);
void sortowanieStogoweTablica(int* tablica, int rozmiar = 300);
int sortowanieSzybkieTablica(int* tablica, int lewa, int prawa, int rozmiar = 300);
void sortowanieSzybkieTablicaInicjacja(int* tablica, int rozmiar);


int losowaLiczba(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

void wypelnijLosowymi(int* tablica, int rozmiar = 300, int min = 0, int max = 1000) {
	for (int i = 0; i < rozmiar; i++) {
		tablica[i] = losowaLiczba(min, max);
	}
}
int* wygenerujTablice(int* losowe, int rozmiar = 300) {
	int* tablica = (int*)malloc(rozmiar * sizeof(int));
	for (int i = 0; i < rozmiar; i++) {
		tablica[i] = losowe[i];
	}
	return tablica;
}
void sortowanieBabelkoweTablica(int* tablica, int rozmiar = 300) {
	for (int i = 0; i < rozmiar - 1; i++) {
		for (int j = 0; j < rozmiar - i - 1; j++) {
			if (tablica[j] > tablica[j + 1]) {
				int lewa = tablica[j];
				int prawa = tablica[j + 1];
				tablica[j] = prawa;
				tablica[j + 1] = lewa;
			}
		}
	}
}
double pomiar(int* tablica, int rozmiar, void(*sort)(int*, int)) {
	auto start1 = steady_clock::now();
	sort(tablica, rozmiar);
	auto stop1 = steady_clock::now();
	return (double)duration_cast<microseconds>(stop1 - start1).count();
}

void stoguj(int* tablica, int rozmiar, int i) {
	int lewa = i * 2 + 1;
	int prawa = i * 2 + 2;
	int doZmiany = -1;
	if (prawa < rozmiar && lewa < rozmiar) {
		if (tablica[prawa] > tablica[i] || tablica[lewa] > tablica[i]) {
			doZmiany = (tablica[lewa] > tablica[prawa]) ? lewa : prawa;
		}
	}
	else if (lewa < rozmiar && tablica[lewa] > tablica[i]) doZmiany = lewa;
	if (doZmiany != -1) {
		int tmp = tablica[i];
		tablica[i] = tablica[doZmiany];
		tablica[doZmiany] = tmp;
		stoguj(tablica, rozmiar, doZmiany);
	}
}

void sortowanieStogoweTablica(int* tablica, int rozmiar = 300) {
	int* nowa = (int*)malloc(rozmiar * sizeof(int));
	int nowaRozmiar = 0;
	int n = rozmiar;
	for (int j = n / 2; j >= 0; j--) {
		stoguj(tablica, n, j);
	}
	for (int i = n; i > 0; i--) {
		int tmp = tablica[n - 1];
		tablica[n - 1] = tablica[0];
		tablica[0] = tmp;
		nowa[rozmiar - 1 - nowaRozmiar++] = tablica[--n];
		stoguj(tablica, n, 0);
	}
	for (int i = 0; i < rozmiar; i++) {
		tablica[i] = nowa[i];
	}
}

int sortowanieSzybkieTablica(int* tablica, int lewa, int prawa, int rozmiar = 300) {
	int tmp;
	if (prawa - lewa < 1) return 0;
	int i = lewa;
	int klucz = tablica[prawa];
	for (int j = i; j < prawa; j++) {
		if (tablica[j] < klucz) {
			tmp = tablica[j];
			tablica[j] = tablica[i];
			tablica[i] = tmp;
			i++;
		}
	}
	tmp = tablica[prawa];
	tablica[prawa] = tablica[i];
	tablica[i] = tmp;
	sortowanieSzybkieTablica(tablica, lewa, i - 1, rozmiar);
	sortowanieSzybkieTablica(tablica, i + 1, prawa, rozmiar);
	return 1;
}

void sortowanieSzybkieTablicaInicjacja(int* tablica, int rozmiar) {
	int res = sortowanieSzybkieTablica(tablica, 0, rozmiar - 1, rozmiar);
}

int main() {

	double BAczas = 0;
	double STczas = 0;
	double SZczas = 0;
	int iloscSortowan = 1000;
	int losowe[300];
	for (int i = 0; i < iloscSortowan; i++) {
		wypelnijLosowymi(losowe);

		int* BAtablica = wygenerujTablice(losowe);
		int* STtablica = wygenerujTablice(losowe);
		int* SZtablica = wygenerujTablice(losowe);

		BAczas += pomiar(BAtablica, 300, sortowanieBabelkoweTablica);
		STczas += pomiar(STtablica, 300, sortowanieStogoweTablica);
		SZczas += pomiar(SZtablica, 300, sortowanieSzybkieTablicaInicjacja);
	}
	printf("BA %lf ms\n", BAczas / iloscSortowan);
	printf("ST %lf ms\n", STczas / iloscSortowan);
	printf("SZ %lf ms\n", SZczas / iloscSortowan);

	/*
	Z 3 powyzej uzytych algorytmow najwolniejszym z nich jest sortowanie babelkowe gdyz jego
	zlozonosc wynosi O(n^2) wynika to z faktu, iz n razy musi przeleciec przez (n minus iteracja)
	elementow i sprawia, iz z wszystkich 3 jest on najwolniejszy. Zaraz po nim znajduje sie
	sortowanie przez kopcowanie, ktory ma coprawda ta sama zlozonosc co sortowanie szybkie
	czyli O(n log(n)) lecz w ka¿dej iteracji wymaga wykonania wiekszej ilosci operacji co
	sprawia, ze jest on wolniejszy. Sortowanie szybkie jest najszybszym algorytmem dla tego
	zestawu danych ale w aktualnej implementacji radzi on sobie najlepiej dla danych losowych
	nie monotonicznych co sprawia, ze jest on jedynym z 3 algorytmow, ktory posiada duza
	roznice w czasie w zaleznosci od danych wejsciowych co jest nieodczuwalne dla wykonanych
	testow.
	*/
	return 0;

}