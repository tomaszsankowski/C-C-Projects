#pragma once
#include <string>

class Swiat;

class Organizm
{
protected:
	int sila;
	int inicjatywa;
	int x;
	int y;
	int poprzednieX;
	int poprzednieY;
	int wiek;
	Swiat& swiat;
	//GET i SET
	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; };
	void ustawPoprzednie() { this->poprzednieX = this->x; this->poprzednieY = this->y; };
	void setInicjatywa(int i) { this->inicjatywa = i; };
	//
public:
	void cofnijRuch() { this->x = this->poprzednieX; this->y = this->poprzednieY; };
	void setSila(int s) { this->sila = s; };
	int getX() const { return x; };
	int getY() const { return y; };
	int getInicjatywa() const { return inicjatywa; };
	int getSila() const { return sila; };
	int getWiek() const { return wiek; };
	bool isHere(int x, int y);
	virtual std::string organizmToString();
	virtual std::string getImie() = 0;
	virtual void akcja() = 0;
	virtual void kolizja(Organizm& atakujacy) = 0;
	virtual void rysowanie() = 0;
	virtual bool czyOdbilAtak(Organizm& atakujacy);
	virtual void rozmnozSie(int x, int y, Swiat& swiat) = 0;
	Organizm(int sila, int inicjatywa, int x, int y, Swiat& swiat);
	Organizm(int sila, int inicjatywa, int x, int y, int poprzednieX, int poprzednieY, int wiek, Swiat& swiat);
	virtual ~Organizm() = 0;
};