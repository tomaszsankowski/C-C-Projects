#include "Czlowiek.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

Czlowiek::Czlowiek(int x, int y, Swiat& swiat) : Zwierze(5, 4, x, y, swiat) { tarczaAlzura = -5; };

void Czlowiek::akcja() {
	wiek++;
	if (tarczaAlzura > -5)
		tarczaAlzura--;
	if (tarczaAlzura >= 0)
		swiat.dodajLog("Zostalo " + std::to_string(tarczaAlzura + 1) + " rund z tarcza Alzura!");
	else if(tarczaAlzura==-5)
		swiat.dodajLog("Mozesz aktywowac tarcze Alzura !");
	else
		swiat.dodajLog("Mozesz aktywowac tarcze Alzura za " + std::to_string(5+tarczaAlzura) + " rund!");
}

bool Czlowiek::czyOdbilAtak(Organizm& atakujacy) {
	if (tarczaAlzura >= 0)
		return true;
	else
		return false;
}

void Czlowiek::rozmnozSie(int x, int y, Swiat& swiat) {
	Czlowiek* nowyOrganizm = new Czlowiek(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

void Czlowiek::rysowanie() {
	std::cout << "C";
}

bool Czlowiek::ruchCzlowieka(char c, int m, int n) {
	this->ustawPoprzednie();
	if (c == 72) {
		if (x > 0)
			setX(x - 1);
		else
			return false;
	}
	else if (c == 80) {
		if (x < m - 1)
			setX(x + 1);
		else
			return false;
	}
	else if (c == 75) {
		if (y > 0)
			setY(y - 1);
		else
			return false;
	}
	else if (c == 77) {
		if (y < n - 1)
			setY(y + 1);
		else
			return false;
	}
	else
		return false;
	return true;
}

Czlowiek::~Czlowiek() {};