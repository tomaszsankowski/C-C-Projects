#include "Owca.h"
#include <iostream>
#include <string>
#include <vector>
#include "Swiat.h"

Owca::Owca(int x, int y, Swiat& swiat) : Zwierze(4, 4, x, y, swiat) {};

void Owca::rysowanie() {
	std::cout << "O";
}

void Owca::rozmnozSie(int x, int y, Swiat& swiat) {
	Owca* nowyOrganizm = new Owca(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Owca::~Owca() {};