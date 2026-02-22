#pragma once
#include "Organizm.h"
#include "Zwierze.h"
#include <string>
class Zlow : public Zwierze
{
public:
	Zlow(int x, int y, Swiat& swiat);
	Zlow(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Zwierze(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {};
	void akcja() override;
	void rysowanie() override;
	bool czyOdbilAtak(Organizm& atakujacy) override;
	std::string getImie() override { return "Zlow"; };
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	~Zlow() override;
};//definicje funkcji dla rozmnozsie i skonczenie metody rozmnazanie w klasie Zwierze.h a na koncu dodanie tego do kalsy swiat