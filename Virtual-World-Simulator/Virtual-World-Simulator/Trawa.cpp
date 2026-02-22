#include "Trawa.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

Trawa::Trawa(int x, int y, Swiat& swiat) : Roslina(0, x, y, swiat) {};

void Trawa::rysowanie() {
	std::cout << "*";
}

void Trawa::rozmnozSie(int x, int y, Swiat& swiat) {
	Trawa* nowyOrganizm = new Trawa(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Trawa::~Trawa() {};