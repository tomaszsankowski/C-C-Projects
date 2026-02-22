#include "Organizm.h"
#include "Swiat.h"

Organizm::Organizm(int sila, int inicjatywa, int x, int y, Swiat& swiat) : sila(sila), inicjatywa(inicjatywa), x(x), y(y), swiat(swiat), wiek(0), poprzednieX(x), poprzednieY(y) {};

Organizm::Organizm(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) : sila(sila), inicjatywa(inicjatywa), x(x), y(y), swiat(swiat), wiek(wiek), poprzednieX(poprzednieX), poprzednieY(poprzednieY) {};

bool Organizm::isHere(int x, int y) {
	if (this == nullptr) {
		return false;
	}
	if ((this->x == x) && (this->y == y)) {
		return true;
	}
	else {
		return false;
	}
}

bool Organizm::czyOdbilAtak(Organizm& atakujacy) {
	return false;
}

std::string Organizm::organizmToString() {
	std::string output;
	output += this->getImie();
	output += " "; 
	output += std::to_string(sila);
	output += " ";
	output += std::to_string(inicjatywa);
	output += " ";
	output += std::to_string(x);
	output += " ";
	output += std::to_string(y);
	output += " ";
	output += std::to_string(poprzednieX);
	output += " ";
	output += std::to_string(poprzednieY);
	output += " "; 
	output += std::to_string(wiek);
	return output;
}

Organizm::~Organizm() {
};