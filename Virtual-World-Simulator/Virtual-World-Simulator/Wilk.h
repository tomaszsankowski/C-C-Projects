#pragma once
#include "Organizm.h"
#include "Zwierze.h"
#include <string>
class Wilk : public Zwierze
{
public:
	Wilk(int x, int y, Swiat& swiat);
	Wilk(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Zwierze(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void rysowanie() override;
	std::string getImie() override { return "Wilk"; };
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	~Wilk() override;
};