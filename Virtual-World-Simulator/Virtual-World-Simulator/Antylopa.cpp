#include "Antylopa.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>
Antylopa::Antylopa(int x, int y, Swiat& swiat) : Zwierze(4, 4, x, y, swiat) {};

void Antylopa::akcja() {
	this->ustawPoprzednie();
	wiek++;
	srand(time(NULL));
	int randomise = std::rand() % 8;
	if ((randomise == 0) && (x > 0))
		x--;
	else if ((randomise == 1) && (x < swiat.getM() - 1))
		x++;
	else if ((randomise == 2) && (y < swiat.getN() - 1))
		y++;
	else if ((randomise == 3) && (y > 0))
		y--;
	else if ((randomise == 4) && (x < swiat.getM() - 2))
		x+=2;
	else if ((randomise == 5) && (y < swiat.getN() - 2))
		y+=2;
	else if ((randomise == 6) && (y > 1))
		y-=2;
	else if ((randomise == 7) && (x>1))
		x-=2;
	wiek++;
}

void Antylopa::kolizja(Organizm& atakujacy) {
	bool willFight = std::rand() % 2;//dla 0 antylopa walczy, dla 1 ucieka
	if (!willFight) {
		if (this->czyOdbilAtak(atakujacy)) {//odbijanie ataku
			swiat.dodajLog(this->getImie() + " odbil atak " + atakujacy.getImie());
			atakujacy.cofnijRuch();
			return;
		}
		else if (this->getImie() == atakujacy.getImie()) {//rozmnazanie
			if (dynamic_cast<Zwierze*>(&atakujacy) && swiat.sprawdzCzyZyje(atakujacy) && dynamic_cast<Zwierze*>(this) && swiat.sprawdzCzyZyje(*this)) {
				atakujacy.cofnijRuch();
				this->rozmnazanie();
			}
			return;
		}
		else if (atakujacy.getSila() >= sila) {//atakujacy wygrywa
			swiat.zabijOrganizm(*this);
			swiat.dodajLog(atakujacy.getImie() + " zabil " + this->getImie());
			return;
		}
		else {//atakujacy przegrywa
			swiat.dodajLog(atakujacy.getImie() + " zginal probujac atakowac " + this->getImie());
			swiat.zabijOrganizm(atakujacy);
			return;
		}
	}
	else {
		int direction = std::rand() % 4; //antylopa domyslnie przesuwa sie o jedno pole w lewo
		swiat.dodajLog("Antylopa uciekla przed atakiem!");
		if ((x > 0) && !swiat.isTaken(x - 1, y))
			x--;
		else if ((x < swiat.getM() - 1) && !swiat.isTaken(x + 1, y))
			x++;
		else if ((y < swiat.getN() - 1) && !swiat.isTaken(x, y+1))
			y++;
		else if ((y > 0) && !swiat.isTaken(x, y-1))
			y--;
		return;
	}
}

void Antylopa::rozmnozSie(int x, int y, Swiat& swiat) {
	Antylopa* nowyOrganizm = new Antylopa(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Antylopa::~Antylopa() {};

void Antylopa::rysowanie() {
	std::cout << "A";
}