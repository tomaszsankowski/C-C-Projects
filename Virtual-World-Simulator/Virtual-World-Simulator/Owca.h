#pragma once
#include "Organizm.h"
#include "Zwierze.h"
#include <string>
class Owca : public Zwierze
{
public:
	Owca(int x, int y, Swiat& swiat);
	Owca(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Zwierze(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void rysowanie() override;
	std::string getImie() override { return "Owca"; };
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	~Owca() override;
};