#pragma once
#include "Organizm.h"
#include <string>
class Roslina : public Organizm
{
public:
	Roslina(int sila, int x, int y, Swiat& swiat) : Organizm(sila, 0, x, y, swiat) {}; 
	Roslina(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Organizm(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	virtual void akcja() override;
	virtual void kolizja(Organizm& atakujacy) override;
	virtual void rysowanie() = 0;
	virtual std::string getImie() = 0;
	virtual void rozmnozSie(int x, int y, Swiat& swiat) = 0;
	virtual ~Roslina();
};