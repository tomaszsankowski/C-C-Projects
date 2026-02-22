#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Organizm.h"
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"
#include "Guarana.h"
#include "Lis.h"
#include "Mlecz.h"
#include "Owca.h"
#include "Roslina.h"
#include "Trawa.h"
#include "WilczeJagody.h"
#include "Wilk.h"
#include "Zlow.h"
#include "Zwierze.h"
#include <string>
#include <vector>

class Swiat
{
private:
	Organizm** organizmy;
	bool* czyZyje;
	int iloscOrganizmow;
	int m, n;//wymiary swiata
	std::vector<std::string> logi;
	int tarczaAlzuraCzlowieka;
	void zapiszSwiat();
	void wczytajSwiat();
	void rysujSwiat();
	void sortujOrganizmy();
public:
	int getM() const { return m; };
	int getN() const { return n; };
	bool czyZajete(int x, int y, int iterator);
	bool isTaken(int x, int y);
	Organizm& getOkupant(int x, int y);
	void zabijOrganizm(int x, int y);
	void zabijOrganizm(Organizm& biedak);
	bool sprawdzCzyZyje(Organizm& org);
	bool sprawdzCzyZyje(int x, int y);
	void zabijZwierze(int x, int y);
	void dodajLog(std::string str);
	Swiat(int m, int n);
	void dodajOrganizm(Organizm& organizm);
	void wykonajTure();
	~Swiat();
};