#include "Guarana.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

Guarana::Guarana(int x, int y, Swiat& swiat) : Roslina(0, x, y, swiat) {};

void Guarana::rysowanie() {
	std::cout << "+";
}

void Guarana::kolizja(Organizm& atakujacy) {//domyslnie roslija przegrywa kazdy pojedynek
	atakujacy.setSila(atakujacy.getSila() + 3);//zwieksza sile organizmu, ktory ja je o 3
	swiat.zabijOrganizm(*this);
	swiat.dodajLog(atakujacy.getImie() + " zjadl " + this->getImie());
	return;
}

void Guarana::rozmnozSie(int x, int y, Swiat& swiat) {
	Guarana* nowyOrganizm = new Guarana(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

Guarana::~Guarana() {};