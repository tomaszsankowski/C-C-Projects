#include "BarszczSosnowskiego.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y, Swiat& swiat) : Roslina(99, x, y, swiat) {};

void BarszczSosnowskiego::rysowanie() {
	std::cout << "%";
}

void BarszczSosnowskiego::kolizja(Organizm& atakujacy) {
	swiat.dodajLog(atakujacy.getImie() + " zginal probujac zjesc " + this->getImie());
	swiat.zabijOrganizm(atakujacy);
	return;
}

void BarszczSosnowskiego::akcja() {
	this->ustawPoprzednie();
	wiek++;
	swiat.zabijZwierze(x, y - 1);//zabija wszystkie zwierzeta dookola siebie
	swiat.zabijZwierze(x, y + 1);
	swiat.zabijZwierze(x + 1, y);
	swiat.zabijZwierze(x - 1, y);
	int randomise = std::rand() % 10;
	if ((randomise == 0)) {//10% szans na probe rozmnozenia
		int where = std::rand() % 4;
		if ((where == 0) && (x > 0)) {
			rozmnozSie(x - 1, y, swiat);
		}
		else if ((where == 1) && (x < swiat.getM() - 1)) {
			rozmnozSie(x + 1, y, swiat);
			return;
		}
		else if ((where == 2) && (y < swiat.getN() - 1)) {
			rozmnozSie(x, y + 1, swiat);
			return;
		}
		else if ((where == 3) && (y > 0)) {
			rozmnozSie(x, y - 1, swiat);
			return;
		}
	}
	wiek++;
}

void BarszczSosnowskiego::rozmnozSie(int x, int y, Swiat& swiat) {
	BarszczSosnowskiego* nowyOrganizm = new BarszczSosnowskiego(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

BarszczSosnowskiego::~BarszczSosnowskiego() {};