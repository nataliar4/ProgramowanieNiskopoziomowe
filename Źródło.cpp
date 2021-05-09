#include <stdio.h>
#include <cmath>

struct Wielomian {
	int stopien;
	int* wspolczynniki;
};

Wielomian tworzenieWielomianu();
void wypiszWielomian(Wielomian wielomian);
int* obliczanieDzielnikow(int liczba);
void obliczaniePierwiastkow(Wielomian wielomian);

Wielomian tworzenieWielomianu() {
	Wielomian wielomian;
	printf("Podaj stopien wielomianu:");
	scanf_s("%d", &wielomian.stopien);
	wielomian.wspolczynniki = (int*)malloc((wielomian.stopien + 1) * sizeof(int));
		for (int i = wielomian.stopien; i >= 0 ; i--) {
			printf("Podaj %d wspolczynnik: ", i);
			scanf_s("%d", &wielomian.wspolczynniki[i]);
		}
	return wielomian;
}
void wypiszWielomian(Wielomian wielomian) {
	printf("stopien: %d\n", wielomian.stopien);
	for (int i = wielomian.stopien; i >= 0; i--) {
		if (i == 0) {
			printf("%d*x^%d\n", wielomian.wspolczynniki[i], i);
		}
		else {
			printf("%d*x^%d + ", wielomian.wspolczynniki[i], i);
		}
		
	}
	printf("\n\n");
}
int* obliczanieDzielnikow(int liczba) {
	int* dzielniki = (int*)malloc(liczba * sizeof(int));
	int indeks = 0;
	for (int i = 1; i <= liczba; i++) {
		if (liczba % i == 0) {
			dzielniki[indeks++] = i;
		}
		else {
			indeks++;
		}
	}
	return dzielniki;
}
void obliczaniePierwiastkow(Wielomian wielomian) {
	int ostatni = abs(wielomian.wspolczynniki[0]);
	//printf("%d * x^0", ostatni);
	int* dzielniki = obliczanieDzielnikow(ostatni);
	for (int i = -ostatni; i < 0; i++) {
		int suma = 0;
		for (int j = 0; j <= wielomian.stopien; j++) {
			suma += wielomian.wspolczynniki[j] * pow(i, j);
		}
		if (suma == 0) {
			printf("Pierwiastek wielomianu: %d\n", i);
		}
		/*
		else {
			printf("%d nie jest pierwiastkiem\n", i);
		}
		*/
	}
	for (int i = 0; i < ostatni; i++) {
		int suma = 0;
		for (int j = 0; j <= wielomian.stopien; j++) {
			suma += wielomian.wspolczynniki[j] * pow(i, j);
		}
		if (suma == 0) {
			printf("Pierwiastek wielomianu: %d\n", i);
		}
		/*
		else {
			printf("%d nie jest pierwiastkiem\n", i);
		}
		*/
	}

}
int main() {
	Wielomian wielomian = tworzenieWielomianu();
	wypiszWielomian(wielomian);
	obliczaniePierwiastkow(wielomian);
}
