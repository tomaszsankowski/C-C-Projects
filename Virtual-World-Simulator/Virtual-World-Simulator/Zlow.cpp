#include "Zlow.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

Zlow::Zlow(int x, int y, Swiat& swiat) : Zwierze(2, 1, x, y, swiat) {};

void Zlow::akcja() {
	this->ustawPoprzednie();
	wiek++;
	int moveIf0 = std::rand() % 4;
	int randomise = std::rand() % 4;
	if (moveIf0 % 4 == 0) {
		if ((randomise == 0) && (x > 0))
			x--;
		else if ((randomise == 1) && (x < swiat.getM() - 1))
			x++;
		else if ((randomise == 2) && (y < swiat.getN() - 1))
			y++;
		else if ((randomise == 3) && (y < 0))
			y--;
	}
}

bool Zlow::czyOdbilAtak(Organizm& atakujacy) {
	if (atakujacy.getSila() < 5) {
		return true;
	}
	else
		return false;
}

void Zlow::rysowanie() {
	std::cout << "Z";
}

void Zlow::rozmnozSie(int x, int y, Swiat& swiat) {
	Zlow* nowyOrganizm = new Zlow(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Zlow::~Zlow() {};