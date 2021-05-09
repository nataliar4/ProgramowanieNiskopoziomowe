#include <stdio.h>
#include <cmath>
#include <time.h>

double zad1_wyrazenie(int i);
double sumuj_rosnaco(int dolne_ogr, int gorne_ogr, double(*oblicz_wyrazenie)(int));
double sumuj_malejaco(int dolne_ogr, int gorne_ogr, double(*oblicz_wyrazenie)(int));
void zad1();

double zad2_wyrazenie(int i);
void zad2();

int** rezerwujMacierz(int wysokosc, int szerokosc);
int losujWartosc(int min, int maks);
int** losujMacierz(int** tablica, int wysokosc, int szerokosc);
int** sumujMacierze(int** tablica1, int** tablica2, int wysokosc, int szerokosc);
int** mnozMacierze(int** tablica1, int** tablica2, int wysokosc1, int szerokosc1, int wysokosc2, int szerokosc2);
int obliczWykladnik2(int** tablica, int wysokosc, int szerokosc);
int obliczWykladnik3(int** tablica, int wysokosc, int szerokosc);
void wypiszMacierz(int** tablica, int wysokosc, int szerokosc);
void zad3();


int main() {
	srand(time(0));
	bool wyjscie = false;
	do {
		int numer = 0;
		printf("Ktore zadanie chcesz wykonac?\n");
		scanf_s("%d", &numer);
		switch (numer) {
		case 1:
			zad1();
			break;
		case 2:
			zad2();
			break;
		case 3:
			zad3();
			break;
		default:
			printf("Musisz podac numer pomiedzy 1 a 3 wlacznie\n");
			break;
		}
		printf("Czy chcesz zakonczyc program ? (1 = Tak, 0 = Nie)\n");
		int odp;
		scanf_s("%d", &odp);
		if (odp == 1) wyjscie = true;

	} while (!wyjscie);
	return 0;
}


double zad1_wyrazenie(int i) {
	return (double)1 / (i * i);
}
double sumuj_rosnaco(int dolne_ogr, int gorne_ogr, double(*oblicz_wyrazenie)(int)) {
	double suma = 0.0;
	for (int i = dolne_ogr; i <= gorne_ogr; i++) {
		suma += oblicz_wyrazenie(i);
	}
	return suma;
}
double sumuj_malejaco(int dolne_ogr, int gorne_ogr, double(*oblicz_wyrazenie)(int)) {
	double suma = 0.0;
	for (int i = dolne_ogr; i >= gorne_ogr; i--) {
		suma += oblicz_wyrazenie(i);
	}
	return suma;
}
void zad1() {
	int min, maks;
	printf("podaj dolne ograniczenie:");
	scanf_s("%d", &min);
	printf("podaj gorne ograniczenie:");
	scanf_s("%d", &maks);
	double wynik = sumuj_rosnaco(min, maks, zad1_wyrazenie);
	if (wynik == sumuj_malejaco(maks, min, zad1_wyrazenie)) {
		printf("wynik funkcji niezalezny od kierunku iteracji, wynosi %lf\n", wynik);
	}
	else {
		printf("Wynik funkcji zalezny od kierunku iteracji.\n Iterowanie rosnaco: %lf.\n Iterowanie malejaco: %lf.\n", sumuj_rosnaco(min, maks, zad1_wyrazenie), sumuj_malejaco(maks, min, zad1_wyrazenie));
	}
}

double zad2_wyrazenie(int i) {
	double suma = 0.0;
	int n = 0;
	if (i % 2 == 0) {
		suma += (double)1 / (2 * i + 1);
	}
	else {
		suma += (double)-1 / (2 * i + 1);
	}
	return suma;
}

void zad2() {
	printf("Podaj oczekiwana dokladnosc (ilosc miejsc po przecinku):");
	int dokladnosc;
	scanf_s("%d", &dokladnosc);
	double eps = pow(10, -dokladnosc);
	double s0 = 0.0, s1 = 0.0, suma = 0.0;
	int i = 0;

	do {
		s0 += zad2_wyrazenie(i);
		s1 = s0 + zad2_wyrazenie(++i);
	} while (abs(s1 - s0) > eps);
	printf("Obliczony wynik wyrazenia, pomnozony przez 4 z zadana dokladnoscia: %lf\n", 4 * s1);
}
int** rezerwujMacierz(int wysokosc, int szerokosc) {
	int** tablica = (int**)malloc(wysokosc * sizeof(int*));
	for (int i = 0; i < wysokosc; i++) {
		tablica[i] = (int*)malloc(szerokosc * sizeof(int));
	}

	for (int x = 0; x < wysokosc; x++) {
		for (int y = 0; y < szerokosc; y++) {
			tablica[x][y] = 0;
		}
	}
	return tablica;
}
int losujWartosc(int min, int maks) {
	return (rand() % (maks - min + 1) + min);
}
//w celu unikniecia zbyt duzej ilosci argumentow wartosci w macierzy sa losowanymi cyframi od 0 do 9
int** losujMacierz(int** tablica, int wysokosc, int szerokosc) {
	for (int i = 0; i < wysokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			tablica[i][j] = losujWartosc(0, 9);
		}
	}
	return tablica;
}

int** sumujMacierze(int** tablica1, int** tablica2, int wysokosc, int szerokosc) {
	int** tablicaWynikowa = rezerwujMacierz(wysokosc, szerokosc);
	for (int i = 0; i < wysokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			tablicaWynikowa[i][j] = tablica1[i][j] + tablica2[i][j];
		}
	}
	return tablicaWynikowa;
}

int** mnozMacierze(int** tablica1, int** tablica2, int wysokosc1, int szerokosc1, int wysokosc2, int szerokosc2) {
	if (szerokosc1 == wysokosc2) {
		int** tablicaWynikowa = rezerwujMacierz(wysokosc1, szerokosc2);
		for (int n = 0; n < wysokosc1; n++) {
			for (int p = 0; p < szerokosc1; p++) {
				for (int m = 0; m < szerokosc2; m++) {
					tablicaWynikowa[n][m] = tablica1[n][p] * tablica2[p][m];
				}
			}
		}
		return tablicaWynikowa;
	}
	printf("nie mozna wymnozyc macierzy, nieodpowiednie wymiary");
	return nullptr;
}
int obliczWykladnik2(int** tablica, int wysokosc, int szerokosc) {
	return tablica[0][0] * tablica[1][1] - tablica[0][1] * tablica[1][0];
}
int obliczWykladnik3(int** tablica, int wysokosc, int szerokosc) {
	return tablica[0][0] * tablica[1][1] * tablica[2][2] + tablica[1][0] * tablica[2][1] * tablica[0][2] + tablica[2][0] * tablica[0][1] * tablica[1][2]
		- tablica[1][0] * tablica[0][1] * tablica[2][2] - tablica[0][0] * tablica[2][1] * tablica[1][2] - tablica[2][0] * tablica[1][1] * tablica[0][2];
}
void wypiszMacierz(int** tablica, int wysokosc, int szerokosc) {
	printf("Macierz o wymiarach %dx%d:\n", wysokosc, szerokosc);
	for (int i = 0; i < wysokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			printf("%d ", tablica[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void zad3() {
	int wysokosc = 3;
	int szerokosc = 3;
	int** macierz1 = rezerwujMacierz(wysokosc, szerokosc);
	int** macierz2 = rezerwujMacierz(wysokosc, szerokosc);
	losujMacierz(macierz1, wysokosc, szerokosc);
	losujMacierz(macierz2, wysokosc, szerokosc);

	printf("Wygenerowane macierze:\n");
	wypiszMacierz(macierz1, wysokosc, szerokosc);
	wypiszMacierz(macierz2, wysokosc, szerokosc);

	printf("Suma macierzy:\n");
	int** suma_macierzy = sumujMacierze(macierz1, macierz2, wysokosc, szerokosc);
	wypiszMacierz(suma_macierzy, wysokosc, szerokosc);

	printf("Iloczyn macierzy:\n");
	int** iloczyn_macierzy = mnozMacierze(macierz1, macierz2, wysokosc, szerokosc, wysokosc, szerokosc);
	wypiszMacierz(iloczyn_macierzy, wysokosc, szerokosc);

	printf("Wyznacznik macierzy: %d\n", obliczWykladnik3(macierz1, wysokosc, szerokosc));



	int wysokosc3 = 2;
	int szerokosc3 = 2;
	int** macierz3 = rezerwujMacierz(wysokosc3, szerokosc3);

	losujMacierz(macierz3, wysokosc3, szerokosc3);

	printf("Wygenerowana macierz:\n");
	wypiszMacierz(macierz3, wysokosc3, szerokosc3);

	printf("Wyznacznik macierzy: %d\n", obliczWykladnik2(macierz3, wysokosc3, szerokosc3));

}

