#pragma once
#include "Organizm.h"
#include "Zwierze.h"
#include <string>
class Lis : public Zwierze
{
public:
	Lis(int x, int y, Swiat& swiat);
	Lis(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Zwierze(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void akcja() override;
	void rysowanie() override;
	std::string getImie() override { return "Lis"; };
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	~Lis() override;
};