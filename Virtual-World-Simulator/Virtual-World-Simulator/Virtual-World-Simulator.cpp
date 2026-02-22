#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include "Organizm.h"
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"
#include "Guarana.h"
#include "Lis.h"
#include "Mlecz.h"
#include "Owca.h"
#include "Roslina.h"
#include "Trawa.h"
#include "WilczeJagody.h"
#include "Wilk.h"
#include "Zlow.h"
#include "Zwierze.h"
#include "Swiat.h"
#include <conio.h>

int main() {
	srand(time(NULL));
	int m, n;
	std::cout << "Podaj wielkosc planczy MxN:\n";
	std::cin >> m >> n;
	Swiat swiat(m,n);
	system("cls");
	swiat.wykonajTure();
	system("cls");
	std::cout << "KONIEC GRY!\n";
	return 0;
}