#include "Roslina.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Swiat.h"
#include <string>
#include <vector>

void Roslina::akcja() {
	this->ustawPoprzednie();
	wiek++;
	int randomise = std::rand() % 10;
	if ((randomise == 0)) {//10% szans na probe rozmnozenia
		int where = std::rand() % 4;
		if ((where == 0) && (x > 0))
			rozmnozSie(x - 1, y, swiat);
		else if ((where == 1) && (x < swiat.getM() - 1))
			rozmnozSie(x + 1, y, swiat);
		else if ((where == 2) && (y < swiat.getN() - 1))
			rozmnozSie(x, y + 1, swiat);
		else if ((where == 3) && (y > 0))
			rozmnozSie(x, y - 1, swiat);
	}
}

void Roslina::kolizja(Organizm& atakujacy) {//domyslnie roslina przegrywa kazdy pojedynek
	swiat.zabijOrganizm(*this);
	swiat.dodajLog(atakujacy.getImie() + " zjadl " + this->getImie());
	return;
}

Roslina::~Roslina() {};