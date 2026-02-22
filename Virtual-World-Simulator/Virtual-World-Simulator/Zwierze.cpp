#include "Zwierze.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Swiat.h"

void Zwierze::akcja() {
	this->ustawPoprzednie();
	wiek++;
	int randomise = std::rand() % 4;
	if ((randomise == 0) && (x > 0))
		x--;
	else if ((randomise == 1) && (x < swiat.getM()-1))
		x++;
	else if ((randomise == 2) && (y < swiat.getN()-1))
		y++;
	else if ((randomise == 3) && (y<0))
		y--;
}
void Zwierze::kolizja(Organizm& atakujacy) {
	if (this->czyOdbilAtak(atakujacy)) {//odbijanie ataku
		if (dynamic_cast<Czlowiek*>(this)) {//tarcza Alzura
			atakujacy.cofnijRuch();
			swiat.dodajLog(this->getImie() + " odbil atak " + atakujacy.getImie() + " przy pomocy tarczy Alzura");
			return;
		}
		else {//zlow
			swiat.dodajLog(this->getImie() + " odbil atak " + atakujacy.getImie());
			atakujacy.cofnijRuch();
			return;
		}
	}
	else if (this->getImie() == atakujacy.getImie()) {//rozmnazanie
		if (dynamic_cast<Zwierze*>(&atakujacy) && swiat.sprawdzCzyZyje(atakujacy) && dynamic_cast<Zwierze*>(this) && swiat.sprawdzCzyZyje(*this)) {
			atakujacy.cofnijRuch();
			this->rozmnazanie();
		}
		return;
	}
	else if (atakujacy.getSila() >= sila) {//atakujacy wygrywa
		swiat.dodajLog(atakujacy.getImie() + " zabil " + this->getImie());
		swiat.zabijOrganizm(*this);
		return;
	}
	else {//atakujacy przegrywa
		swiat.dodajLog(atakujacy.getImie() + " zginal probujac atakowac " + this->getImie());
		swiat.zabijOrganizm(atakujacy);
		return;
	}
}

void Zwierze::rozmnazanie() {
	int where = std::rand() % 4;//proba rozmnozenia
	if ((where == 0) && (x > 0) && swiat.isTaken(x - 1, y)){
		rozmnozSie(x - 1, y, swiat);
		swiat.dodajLog(this->getImie() + " rozmnaza sie!");
		return;
	}
	else if ((where == 1) && (x < swiat.getM() - 1) && swiat.isTaken(x + 1, y)){
		rozmnozSie(x + 1, y, swiat);
		swiat.dodajLog(this->getImie() + " rozmnaza sie!");
		return;
	}
	else if ((where == 2) && (y < swiat.getN() - 1) && swiat.isTaken(x, y + 1)){
		rozmnozSie(x, y + 1, swiat);
		swiat.dodajLog(this->getImie() + " rozmnaza sie!");
		return;
	}
	else if ((where == 3) && (y > 0) && swiat.isTaken(x, y - 1)){
		rozmnozSie(x, y - 1, swiat);
		swiat.dodajLog(this->getImie() + " rozmnaza sie!");
		return;
	}
	swiat.dodajLog(this->getImie() + " probowal sie rozmnozyc, ale mu nie wyszlo!");
	return;
}
Zwierze::~Zwierze() {};