#include "Mlecz.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

Mlecz::Mlecz(int x, int y, Swiat& swiat) : Roslina(0, x, y, swiat) {};

void Mlecz::rysowanie() {
	std::cout << "Y";
}

void Mlecz::akcja() {
	this->ustawPoprzednie();
	wiek++;
	int randomise;
	for (int i = 0; i < 3; i++) {
		randomise = std::rand() % 10;
		if ((randomise == 0)) {//10% szans na probe rozmnozenia
			int where = std::rand() % 4;
			if ((where == 0) && (x > 0)){
				rozmnozSie(x - 1, y, swiat);
				return;
			}
			else if ((where == 1) && (x < swiat.getM() - 1)){
				rozmnozSie(x + 1, y, swiat);
				return;
			}
			else if ((where == 2) && (y < swiat.getN() - 1)){
				rozmnozSie(x, y + 1, swiat);
				return;
			}
			else if ((where == 3) && (y > 0)){
				rozmnozSie(x, y - 1, swiat);
				return;
			}
		}
	}
}

void Mlecz::rozmnozSie(int x, int y, Swiat& swiat) {
	Mlecz* nowyOrganizm = new Mlecz(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Mlecz::~Mlecz() {};