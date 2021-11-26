#include <iostream>
#include <time.h>
#include <stdio.h>
using namespace std;


//Aufgabe 2
typedef int BOOL;
#define TRUE 1;
#define FALSE 0;

void werteeinlesen() {

	int sum{ 0 }, eingabe{ 1 }, counter{ 1 };

	printf("Bitte Zahlen zum aufsummieren eingeben (0 fuer exit)\n");
	while (eingabe != 0) {

		printf("%d. Zahl: ", counter++);

		int rgw = scanf("%d%*[^\n]", &eingabe);		
		sum += eingabe;
	}
	printf("Summe: %d\tMittelwert: %1.2f", sum, (double)sum / --counter);

}

BOOL istschaltjahr1(const int& y) {
	return y % 4 == 0 && !(y % 100 == 0 && !(y % 400 == 0));
}

BOOL istschaltjahr2(const int& y) {
	return (y % 400 == 0 || !(y % 100 == 0)) && y % 4 == 0;
}

void schaltjahr() {

	BOOL (*fp)(const int&) { &istschaltjahr1 };
	int i{ 0 }, c{ 0 };
	time_t start, end;

	for(int j = 0; j < 2; j++) {

		time(&start);
		while (i < 1'000'000'000) {
			if ((*fp)(++i))
				++c;
		}
		time(&end);

		printf("Anzahl Schaltjahre: %d\tZeit in Sekunden: %.2f\n", c, difftime(end, start));

		i = c = start = end = 0;
		fp = &istschaltjahr2;
	}
}

BOOL implikation() {

	int a{ 0 }, b{ 0 };

	printf("Bitte 2 Zahlen eingeben: ");
	int rgw = scanf("%d%d", & a, & b);

	if (!a && b)
		return FALSE;
	return TRUE;
}

BOOL aequivalenz() {

	int a{ 0 }, b{ 0 };

	printf("Bitte 2 Zahlen eingeben: ");
	int rgw = scanf("%d%d", &a, &b);

	if (a == b)
		return TRUE;
	return FALSE;
}

void wahrheitstabelle() {

	const char* wt[] { "Wahrheitstabelle Implikation:\n", "\nWahrheitstabelle Aequivalenz:\n"  };
	int werta[]{ 1, 1, 0, 0 };
	int wertb[]{ 0, 1, 0, 1 };


	//Lambdafunktionen 
	auto imp = [](int a, int b) {
		return a == b ? 1 : 0;
	};
	auto aeq = [](int a, int b) {
		if (a && !b)
			return 0;
		return 1;
	};

	int (*fp)(int a, int b) { imp };

	for (int i = 0; i < 2; i++) {
		
		printf("%s%c\t%c\tErgebnis\n", wt[i], 'a', 'b');

		for (int j = 0; j < sizeof(werta) / sizeof(*werta); j++)
			printf("%d\t%d\t%d\n", werta[j], wertb[j], (*fp)(werta[j], wertb[j]) );

		fp = aeq;
	}
}

int fakultaetrekursiv(int a) {
	return a <= 1 ? 1 : a * fakultaetrekursiv(a - 1);
}

int fakultaetiterativ(int& a) {
	int fk{ 1 };

	for (; a > 0; a--) {
		fk *= a;
	}
	return fk;
}

void fakultaet() {
	int i{ 0 };

	printf("Zahl zur Berechnung der Fakultaet: ");
	int rgw = scanf("%d%*[^\n]", &i);
	printf("Fakultaet: %d", fakultaetrekursiv(i));
}


//Metaprogrammierung
template<int n>
struct fkt {
	static const int f{ n * fkt<n - 1>::f };
};

template<>
struct fkt<1> {
	static const int f{ 1 };
};

template<int n, int i>
struct isprim {
	static const int isp {(i % n) && isprim<(i > 1 ? n : 0), }
};


template<int n>
struct printp {
	printp<n - 1> n;
	static const int p{ isprim<n>::prim };
}


int main() {

	//Aufgabe 1
	//werteeinlesen();

	//Aufabe 3
	//a)
	//implikation();

	//b)
	//aequivalenz();

	//c)
	wahrheitstabelle();


	//Aufgabe 4
	//schaltjahr();

	//Aufgabe 5
	//fakultaet();
}