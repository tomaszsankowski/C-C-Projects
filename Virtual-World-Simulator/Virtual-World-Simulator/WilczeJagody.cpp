#include "WilczeJagody.h"
#include <iostream>
#include "Swiat.h"
#include <string>
#include <vector>

WilczeJagody::WilczeJagody(int x, int y, Swiat& swiat) : Roslina(99, x, y, swiat) {};

void WilczeJagody::rysowanie() {
	std::cout << "&";
}

void WilczeJagody::kolizja(Organizm& atakujacy) {
	swiat.dodajLog(atakujacy.getImie() + " zginal probujac zjesc " + this->getImie());
	swiat.zabijOrganizm(atakujacy);
	return;
}

void WilczeJagody::rozmnozSie(int x, int y, Swiat& swiat) {
	WilczeJagody* nowyOrganizm = new WilczeJagody(x, y, swiat);
	swiat.dodajOrganizm(*nowyOrganizm);
}

WilczeJagody::~WilczeJagody() {};