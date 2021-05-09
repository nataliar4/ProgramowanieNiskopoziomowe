#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <chrono>
using namespace std::chrono;

typedef struct listaJednokierunkowa {
	int wartosc;
	listaJednokierunkowa* nastepny;
} listaJednokierunkowa;

//losowanie liczby z zakresu <min;max>
int losowaLiczba(int min, int max);
//tworzenie tablicy 300 liczb losowych z zakresu <0;1000>
void wypelnijLosowymi(int* tablica, int rozmiar = 300, int min = 0, int max = 1000);
//tworzenie tablicy dynamicznej na podstawie tablicy losowych liczb
int* wygenerujTablice(int* losowe, int rozmiar = 300);
//tworzenie listy jednokierunkowej na podstawie tablicy losowych liczb
listaJednokierunkowa* wygenerujListe(int* losowe, int rozmiar = 300);
//wypisywanie tablicy dynamicznej na konsole
void wypiszTablice(int* tablica, int rozmiar = 300);
//wypisywanie listy jednokierunkowej na konsole
void wypiszListe(listaJednokierunkowa* lista, int rozmiar = 300);
//sortowanie tablicy dynamicznej
void sortowanieBabelkoweTablica(int* tablica, int rozmiar = 300);
//sortowanie listy jednokierunkowej
void sortowanieBabelkoweLista(listaJednokierunkowa* lista, int rozmiar = 300);

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

listaJednokierunkowa* wygenerujListe(int* losowe, int rozmiar = 300) {
	listaJednokierunkowa* lista = (listaJednokierunkowa*)malloc(sizeof(listaJednokierunkowa));
	listaJednokierunkowa* wskaznik = lista;
	for (int i = 0; i < rozmiar; i++) {
		wskaznik->wartosc = losowe[i];
		wskaznik->nastepny = (listaJednokierunkowa*)malloc(sizeof(listaJednokierunkowa));
		wskaznik = wskaznik->nastepny;
	}
	return lista;
}

void wypiszTablice(int* tablica, int rozmiar = 300) {
	printf("Tablica: \n");
	for (int i = 0; i < rozmiar; i++) {
		printf("%d ", tablica[i]);
		if (!((i + 1) % 10)) printf("\n");
	}
	printf("\n");
}

void wypiszListe(listaJednokierunkowa* lista, int rozmiar = 300) {
	printf("\nLista: \n");
	listaJednokierunkowa* wskaznik = lista;
	for (int i = 0; i < rozmiar; i++) {
		printf("%d ", wskaznik->wartosc);
		if (!((i + 1) % 10)) printf("\n");
		wskaznik = wskaznik->nastepny;
	}
	printf("\n");
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

void sortowanieBabelkoweLista(listaJednokierunkowa* lista, int rozmiar = 300) {
	for (int i = 0; i < rozmiar - 1; i++) {
		listaJednokierunkowa* lewa = lista;
		listaJednokierunkowa* prawa = lista->nastepny;
		for (int j = 0; j < rozmiar - i - 1; j++) {
			if (lewa->wartosc > prawa->wartosc) {
				int l = lewa->wartosc;
				int p = prawa->wartosc;
				lewa->wartosc = p;
				prawa->wartosc = l;
			}
			lewa = lewa->nastepny;
			prawa = prawa->nastepny;
		}
	}
}

int main() {
	srand(time(NULL));
	// W zwiazku z tym, ze time.h posiada bardzo niedok�adne odczyty u�ywam 
	// modu�u chrono ktory jest w stanie dokonac odczytu tak malych rozmiarow
	
	int iloscSortowan = 1000;
	int losowe[300];
	double lacznyczas1 = 0; // generowanie tablicy
	double lacznyczas2 = 0; // generowanie listy
	double lacznyczas3 = 0; // sortowanie tablicy
	double lacznyczas4 = 0; // sortowanie listy
	double lacznyczas5 = 0; // wypisywanie tabicy
	double lacznyczas6 = 0; // wypisywanie listy
	for (int i = 0; i < iloscSortowan; i++) {
		wypelnijLosowymi(losowe);

		auto start1 = steady_clock::now();
		int* tablica = wygenerujTablice(losowe);
		auto stop1 = steady_clock::now();

		auto start2 = steady_clock::now();
		listaJednokierunkowa* lista = wygenerujListe(losowe);
		auto stop2 = steady_clock::now();

		auto start3 = steady_clock::now();
		sortowanieBabelkoweTablica(tablica);
		auto stop3 = steady_clock::now();

		auto start4 = steady_clock::now();
		sortowanieBabelkoweLista(lista);
		auto stop4 = steady_clock::now();

		auto start5 = steady_clock::now();
		wypiszTablice(tablica);
		auto stop5 = steady_clock::now();

		auto start6 = steady_clock::now();
		wypiszListe(lista);
		auto stop6 = steady_clock::now();

		lacznyczas1 += duration_cast<microseconds>(stop1 - start1).count();
		lacznyczas2 += duration_cast<microseconds>(stop2 - start2).count();
		lacznyczas3 += duration_cast<microseconds>(stop3 - start3).count();
		lacznyczas4 += duration_cast<microseconds>(stop4 - start4).count();
		lacznyczas5 += duration_cast<microseconds>(stop5 - start5).count();
		lacznyczas6 += duration_cast<microseconds>(stop6 - start6).count();
	}
	printf("Sredni czas wynosi...\n");
	printf("Wygenerowanie tablicy: %lf ms\n", lacznyczas1 / iloscSortowan);
	printf("Wygenerowanie listy jednokierunkowej: %lf ms\n", lacznyczas2 / iloscSortowan);
	printf("Sortowanie tablicy: %lf ms\n", lacznyczas3 / iloscSortowan);
	printf("Sortowanie listy jednokierunkowej: %lf ms\n", lacznyczas4 / iloscSortowan);
	printf("Wypisanie tablicy: %lf ms\n", lacznyczas5 / iloscSortowan);
	printf("Wypisanie listy jednokierunkowej: %lf ms\n", lacznyczas6 / iloscSortowan);

	return 0;
}