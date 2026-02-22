#pragma once
#include "Organizm.h"
#include "Roslina.h"
#include <string>
class Trawa : public Roslina
{
public:
	Trawa(int x, int y, Swiat& swiat);
	Trawa(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Roslina(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void rysowanie() override;
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	std::string getImie() override { return "Trawa"; };
	~Trawa() override;
};