#pragma once
#include "Organizm.h"
#include <string>
class Zwierze : public Organizm
{
private:
public:
	Zwierze(int sila, int inicjatywa, int x, int y, Swiat& swiat) : Organizm(sila, inicjatywa, x, y, swiat) {};
	Zwierze(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Organizm(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	virtual void akcja() override;
	virtual void kolizja(Organizm& atakujacy) override;
	virtual void rysowanie() = 0;
	void rozmnazanie();
	virtual void rozmnozSie(int x, int y, Swiat& swiat) = 0;
	virtual std::string getImie() = 0;
	virtual ~Zwierze();
};