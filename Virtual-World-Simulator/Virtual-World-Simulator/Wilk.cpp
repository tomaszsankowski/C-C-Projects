#include "Wilk.h"
#include <iostream>
#include <string>
#include <vector>
#include "Swiat.h"

Wilk::Wilk(int x, int y, Swiat& swiat) : Zwierze(9, 5, x, y, swiat) {};

void Wilk::rysowanie() {
	std::cout << "W";
}

void Wilk::rozmnozSie(int x, int y, Swiat& swiat) {
	Wilk* nowyOrganizm = new Wilk(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Wilk::~Wilk() {};