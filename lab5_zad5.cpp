#include <stdio.h>
#include <stdlib.h>

//tworze strukture wierzcholek przechowujaca wartosc wierzcholka oraz wskazniki
//na obu potomkow
//wstepnie tworze korzen drzewa poczatkowo NULL
struct Wierzcholek
{
	int wartosc;
	struct Wierzcholek* prawy;
	struct Wierzcholek* lewy;
} *bst;

struct Wierzcholek* wstaw_doDrzewa(struct Wierzcholek* drzewo, int wartosc);
bool czy_Element(struct Wierzcholek* drzewo, int wartosc);
struct Wierzcholek* usun_zDrzewa(struct Wierzcholek* drzewo, int wartosc);
int oblicz_Poziom(struct Wierzcholek* drzewo);
void wyprowadz_Drzewo(struct Wierzcholek* drzewo);
struct Wierzcholek* usun_Drzewo(struct Wierzcholek* drzewo);
bool czy_pusteDrzewo(struct Wierzcholek* drzewo);

struct Wierzcholek* wstaw_doDrzewa(struct Wierzcholek* drzewo, int wartosc)
{
	if (drzewo == nullptr)
	{
		struct Wierzcholek* nowy = (struct Wierzcholek*)malloc(sizeof(struct Wierzcholek));
		nowy->wartosc = wartosc;
		nowy->lewy = nullptr;
		nowy->prawy = nullptr;
		return nowy;
	}
	else
	{
		if (wartosc > drzewo->wartosc) drzewo->prawy = wstaw_doDrzewa(drzewo->prawy, wartosc);
		else drzewo->lewy = wstaw_doDrzewa(drzewo->lewy, wartosc);
	}
	return drzewo;
}

bool czy_Element(struct Wierzcholek* drzewo, int wartosc)
{
	if (drzewo == nullptr) return false;
	if (drzewo->wartosc == wartosc) return true;
	if (wartosc > drzewo->wartosc) return czy_Element(drzewo->prawy, wartosc);
	else return czy_Element(drzewo->lewy, wartosc);
}

struct Wierzcholek* min_zDrzewa(struct Wierzcholek* drzewo) {
	struct Wierzcholek* min = drzewo;

	while (min && min->lewy != nullptr) min = min->lewy;

	return min;
}

struct Wierzcholek* usun_zDrzewa(struct Wierzcholek* drzewo, int wartosc) {
	if (drzewo == nullptr) return drzewo;
	if (wartosc < drzewo->wartosc) drzewo->lewy = usun_zDrzewa(drzewo->lewy, wartosc);
	else if (wartosc > drzewo->wartosc) drzewo->prawy = usun_zDrzewa(drzewo->prawy, wartosc);
	else
	{
		if (drzewo->lewy == nullptr && drzewo->prawy == nullptr) return nullptr;
		else if (drzewo->lewy == nullptr)
		{
			struct Wierzcholek* prawy = drzewo->prawy;
			free(drzewo);
			return prawy;
		}
		else if (drzewo->prawy == nullptr)
		{
			struct Wierzcholek* lewy = drzewo->lewy;
			free(drzewo);
			return lewy;
		}
		else
		{
			struct Wierzcholek* min = min_zDrzewa(drzewo->prawy);
			drzewo->wartosc = min->wartosc;
			drzewo->prawy = usun_zDrzewa(drzewo->prawy, min->wartosc);
		}
	}
	return drzewo;
}

int oblicz_Poziom(struct Wierzcholek* drzewo)
{
	if (drzewo == nullptr) return 0;
	int lewy = oblicz_Poziom(drzewo->lewy);
	int prawy = oblicz_Poziom(drzewo->prawy);
	return (lewy > prawy ? lewy : prawy) + 1;
}

void wyprowadz_Drzewo(struct Wierzcholek* drzewo)
{
	if (drzewo == nullptr) return;
	wyprowadz_Drzewo(drzewo->lewy);
	printf("Wartosc: %d\n", drzewo->wartosc);
	wyprowadz_Drzewo(drzewo->prawy);
}

struct Wierzcholek* usun_Drzewo(struct Wierzcholek* drzewo)
{
	if (drzewo == nullptr) return drzewo;
	usun_Drzewo(drzewo->lewy);
	usun_Drzewo(drzewo->prawy);
	free(drzewo);
	return nullptr;
}

bool czy_pusteDrzewo(struct Wierzcholek* drzewo)
{
	return (drzewo == nullptr);
}

int main()
{
	printf(czy_pusteDrzewo(bst) ? "Drzewo jest puste\n" : "Drzewo nie jest puste\n");
	bst = wstaw_doDrzewa(bst, 5);
	bst = wstaw_doDrzewa(bst, 3);
	bst = wstaw_doDrzewa(bst, 7);
	bst = wstaw_doDrzewa(bst, 4);
	bst = wstaw_doDrzewa(bst, 2);
	printf(czy_pusteDrzewo(bst) ? "Drzewo jest puste\n" : "Drzewo nie jest puste\n");
	printf("Drzewo zawiera element o wartosci 3: %d\n", czy_Element(bst, 3));
	printf("Drzewo zawiera element o wartosci 9: %d\n", czy_Element(bst, 9));
	wyprowadz_Drzewo(bst);
	bst = usun_zDrzewa(bst, 4);
	wyprowadz_Drzewo(bst);
	bst = usun_zDrzewa(bst, 8);
	printf("Poziom drzewa: %d\n", oblicz_Poziom(bst));
	bst = usun_Drzewo(bst);
	printf(czy_pusteDrzewo(bst) ? "Drzewo jest puste\n" : "Drzewo nie jest puste\n");
}
