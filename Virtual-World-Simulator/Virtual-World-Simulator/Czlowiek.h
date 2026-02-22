#pragma once
#include "Organizm.h"
#include "Zwierze.h"
#include <string>
class Czlowiek : public Zwierze
{
private:
	int tarczaAlzura;
public:
	Czlowiek(int x, int y, Swiat& swiat);
	Czlowiek(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat) :
		Zwierze(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, swiat) {
		tarczaAlzura = -5; 
	};
	void akcja() override;
	int getTarczaAlzura() { return tarczaAlzura; };
	void setTarczaAlzura(int x) { this->tarczaAlzura = x; };
	void rysowanie() override;
	bool ruchCzlowieka(char c, int m, int n);
	bool czyOdbilAtak(Organizm& atakujacy) override;
	std::string getImie() override { return "Czlowiek"; };
	void rozmnozSie(int x, int y, Swiat& swiat) override;
	~Czlowiek() override;
};