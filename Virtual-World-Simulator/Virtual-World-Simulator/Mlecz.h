#pragma once
#include "Organizm.h"
#include "Roslina.h"
#include <string>
class Mlecz : public Roslina
{
public:
	Mlecz(int x, int y, Swiat& swiat);
	Mlecz(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Roslina(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void rysowanie() override;
	void akcja() override;
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	std::string getImie() override { return "Mlecz"; };
	~Mlecz() override;
};