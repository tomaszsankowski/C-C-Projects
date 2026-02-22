#include "Lis.h"
#include <iostream>
#include "Swiat.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

Lis::Lis(int x, int y, Swiat& swiat) : Zwierze(3, 7, x, y, swiat) {};

void Lis::rozmnozSie(int x, int y, Swiat& swiat) {
	Lis* nowyOrganizm = new Lis(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

void Lis::akcja() {
	this->ustawPoprzednie();
	wiek++;
	while(true) {//sprawdza czy pole na ktore poszedlby lis jest zajete, a jesli tak to czy sila oponenta jest wieksza od jego wlasnej
		int randomise = std::rand() % 4;
		if ((randomise == 0) && (x > 0)) {
			if (!swiat.isTaken(x - 1, y)) {
				Organizm& okupant = swiat.getOkupant(x - 1, y);
				if (okupant.getSila() <= sila) {
					x--;
					return;
				}
			}
			else {
				x--;
				return;
			}
		}
		else if ((randomise == 1) && (x < swiat.getM() - 1)) {
			if (!swiat.isTaken(x + 1, y)) {
				Organizm& okupant = swiat.getOkupant(x + 1, y);
				if (okupant.getSila() <= sila) {
					x++;
					return;
				}
			}
			else {
				x++;
				return;
			}
		}
		else if ((randomise == 2) && (y < swiat.getN() - 1)) {
			if (!swiat.isTaken(x, y + 1)) {
				Organizm& okupant = swiat.getOkupant(x, y + 1);
				if (okupant.getSila() <= sila) {
					y++;
					return;
				}
			}
			else {
				y++;
				return;
			}
		}
		else if ((randomise == 3) && (y > 0)) {
			if (!swiat.isTaken(x, y - 1)) {
				Organizm& okupant = swiat.getOkupant(x, y - 1);
				if (okupant.getSila() <= sila) {
					y--;
					return;
				}
			}
			else {
				y--;
				return;
			}
		}
	}
}

void Lis::rysowanie() {
	std::cout << "L";
}

Lis::~Lis() {};