#pragma once
#include "Zwierze.h"
#include <string>
class Antylopa : public Zwierze
{
public:
	Antylopa(int x, int y, Swiat& swiat);
	Antylopa(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Zwierze(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void akcja() override;
	void kolizja(Organizm& atakujacy) override;
	void rysowanie() override;
	std::string getImie() override { return "Antylopa"; };
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	~Antylopa() override;
};