#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Swiat.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>

Swiat::Swiat(int m, int n) : m(m), n(n) {
    int pola = m * n;
    this->iloscOrganizmow = ((pola - pola % 100) / 100) * 10 + 1;
    this->organizmy = new Organizm * [iloscOrganizmow];
    this->czyZyje = new bool[iloscOrganizmow];
    czyZyje[0] = true;
    organizmy[0] = new Czlowiek(m/2, n/2, *this);
    for (int i = 1; i < iloscOrganizmow ; i++) {
        czyZyje[i] = true;
        int losx = rand() % m;
        int losy = rand() % n;
        while (!czyZajete(losx, losy, i)) {
            losx = rand() % m;
            losy = rand() % n;
        }
        if (i % 10 == 0) organizmy[i] = new Antylopa(losx, losy, *this);
        else if (i % 10 == 1) organizmy[i] = new BarszczSosnowskiego(losx, losy, *this);
        else if (i % 10 == 2) organizmy[i] = new Guarana(losx, losy, *this);
        else if (i % 10 == 3) organizmy[i] = new Lis(losx, losy, *this);
        else if (i % 10 == 4) organizmy[i] = new Mlecz(losx, losy, *this);
        else if (i % 10 == 5) organizmy[i] = new Owca(losx, losy, *this);
        else if (i % 10 == 6) organizmy[i] = new Trawa(losx, losy, *this);
        else if (i % 10 == 7) organizmy[i] = new WilczeJagody(losx, losy, *this);
        else if (i % 10 == 8) organizmy[i] = new Wilk(losx, losy, *this);
        else if (i % 10 == 9) organizmy[i] = new Zlow(losx, losy, *this);
    }
    std::vector<std::string> logi;
}

bool Swiat::czyZajete(int x, int y, int iterator) {
    for (int i = 0; i < iterator; i++) {
        if (organizmy[i] == nullptr)
            continue;
        if (organizmy[i]->isHere(x, y))
            return false;
    }
    return true;
}

bool Swiat::isTaken(int x, int y) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (organizmy[i] == nullptr)
            continue;
        if (organizmy[i]->isHere(x, y))
            return false;
    }
    return true;
}

Organizm& Swiat::getOkupant(int x, int y) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (organizmy[i] == nullptr)
            continue;
        if (organizmy[i]->isHere(x, y))
            return *organizmy[i];
    }
}

void Swiat::dodajLog(std::string str) {
    logi.push_back(str);
}

void Swiat::wykonajTure() {
    char c;
    bool wczytanoSwiat = false;
    while (true) {
        bool wyjdzZPetli = false;
        sortujOrganizmy();
        int iterations = iloscOrganizmow;
        for (int i = 0; i < iterations; i++) {
                Czlowiek* czl = dynamic_cast<Czlowiek*>(organizmy[i]);
                if (czl != nullptr) {//tura czowieka
                    if (wczytanoSwiat == true)
                        wczytanoSwiat = false;
                    system("cls");
                    this->rysujSwiat();
                    this->tarczaAlzuraCzlowieka = czl->getTarczaAlzura();
                    if (!czyZyje[i])
                        return;
                    else{
                        organizmy[i]->akcja();
                        c = _getch();
                        while ((!czl->ruchCzlowieka(c, m, n)) && (c != 'q') && (c != 'p') && (c != 'l')) {//czeka az gracz wykona legalny ruch lub bedzeie chcial wyjsc
                            if (c == 's')//zapisz do pliku
                                zapiszSwiat();
                            c = _getch();
                        }
                        if (c == 'q')//wyjdz
                            return;
                        else if (c == 'l') {//wczytaj gre z pliku
                            wczytajSwiat();
                            wczytanoSwiat = true;
                            wyjdzZPetli = true;
                        }
                        else if (c == 'p') {//aktywuj supermoc
                            if (czl->getTarczaAlzura() == -5)
                                czl->setTarczaAlzura(4);
                            else
                                this->dodajLog("Nie mozna narazie aktywowac super mocy!");
                        }
                        else {//ruch czlowieka
                            for (int k = 0; k < iterations; k++) {
                                if (czyZyje[k] && (k != i) && (organizmy[i]->getX() == organizmy[k]->getX()) && (organizmy[i]->getY() == organizmy[k]->getY())) {
                                    organizmy[k]->kolizja(*organizmy[i]);
                                }
                            }
                        }
                    }
                }
                else {//tura innego organizmu
                    if (!wczytanoSwiat) {
                        if (czyZyje[i]) {
                            organizmy[i]->akcja();
                            for (int k = 0; k < iterations; k++) {
                                if (czyZyje[k] && (k != i) && (organizmy[i]->getX() == organizmy[k]->getX()) && (organizmy[i]->getY() == organizmy[k]->getY())) {
                                    organizmy[k]->kolizja(*organizmy[i]);
                                }
                            }
                        }
                    }
                }
                if (wyjdzZPetli)
                    break;
        }
    }
}

void Swiat::dodajOrganizm(Organizm& organizm) {
    if (isTaken(organizm.getX(), organizm.getY())) {
        Organizm** nowaTablica = new Organizm * [iloscOrganizmow + 1];
        bool* noweCzyZyje = new bool[iloscOrganizmow + 1];
        for (int i = 0; i < iloscOrganizmow; i++) {
            nowaTablica[i] = organizmy[i];
            if (czyZyje[i] == true)
                noweCzyZyje[i] = true;
            else
                noweCzyZyje[i] = false;
        }
        nowaTablica[iloscOrganizmow] = &organizm;
        noweCzyZyje[iloscOrganizmow] = true;
        iloscOrganizmow++;
        delete[] organizmy;
        organizmy = nowaTablica;
        delete[] czyZyje;
        czyZyje = noweCzyZyje;
    }
    else
        delete &organizm;
}

void Swiat::zabijZwierze(int x, int y) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (dynamic_cast<Zwierze*>(organizmy[i]) && czyZyje[i]) {
            if (organizmy[i]->isHere(x, y)){
                czyZyje[i] = false;
                logi.push_back(organizmy[i]->getImie() + " za bardzo zblizyl sie do barszczu sosnowskiego");
            }
        }

    }
}

bool Swiat::sprawdzCzyZyje(int x, int y) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (organizmy[i]->isHere(x,y)) {
            return czyZyje[i];
        }
    }
}

bool Swiat::sprawdzCzyZyje(Organizm& org) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (organizmy[i]->isHere(org.getX(), org.getY())) {
            return czyZyje[i];
        }
    }
}

void Swiat::zabijOrganizm(int x, int y) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (organizmy[i]->isHere(x, y)) {
            czyZyje[i] = false;
        }
    }
}

void Swiat::zabijOrganizm(Organizm& biedak) {
    for (int i = 0; i < iloscOrganizmow; i++) {
        if (organizmy[i]->isHere(biedak.getX(), biedak.getY())&&organizmy[i]->getImie()==biedak.getImie()) {
            czyZyje[i] = false;
            break;
        }
    }
}

void Swiat::sortujOrganizmy() {//sortuje organizmy po inicjatywie i wieku
    for (int i = 0; i < iloscOrganizmow; i++) {
        for (int j = 1; j < iloscOrganizmow-i; j++) {
            if (organizmy[j - 1]->getInicjatywa() < organizmy[j]->getInicjatywa()) {
                Organizm* buffor = organizmy[j];
                organizmy[j] = organizmy[j - 1];
                organizmy[j - 1] = buffor;
                bool buffer = czyZyje[j];
                czyZyje[j] = czyZyje[j - 1];
                czyZyje[j - 1] = buffer;
            }
            else if (organizmy[j - 1]->getInicjatywa() == organizmy[j]->getInicjatywa()) {
                if (organizmy[j - 1]->getWiek() < organizmy[j]->getWiek()) {
                    Organizm* buffor = organizmy[j];
                    organizmy[j] = organizmy[j - 1];
                    organizmy[j - 1] = buffor;
                    bool buffer = czyZyje[j];
                    czyZyje[j] = czyZyje[j - 1];
                    czyZyje[j - 1] = buffer;
                }
            }
        }
    }
}

void Swiat::rysujSwiat() {
    std::cout << "[ Tomasz Sankowski, s193363 ]\n";
    bool isSet = false;
    for (int i = 0; i < m+2; i++) {
        for (int j = 0; j < n + 2; j++) {
            if (i > 0 && i < m + 1 && j>0 && j < n + 1) {
                for (int k = iloscOrganizmow-1; k >=0; k--) {
                    if ( (organizmy[k]->isHere(i - 1, j - 1)) && czyZyje[k]) {
                        organizmy[k]->rysowanie();
                        std::cout << " ";
                        isSet = true;
                        break;
                    }
                }
                if (!isSet)
                    std::cout << ". ";
                else
                    isSet = false;
            }
            else
                std::cout << "# ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < logi.size(); i++) {
        std::cout << logi[i] << std::endl;
    }
    logi.clear();
    
    COORD pos = { static_cast<SHORT>(2*m + 5), static_cast<SHORT>(2) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "Legenda:\n";

    COORD pos1 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(3) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos1);
    std::cout << "Strzalki: poruszanie sie czlowiekiem\n";

    COORD pos2 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(4) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos2);
    std::cout << "q: wyjscie  p: super moc czlowieka" << std::endl;

    COORD pos3{ static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(5) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos3);
    std::cout << "s: zapis do pliku  l: wczytaj z pliku" << std::endl;

    COORD pos4 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(6) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos4);
    std::cout << "OZNACZENIA:\n";
    /*
    COORD pos4 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(6) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos4);
    std::cout << "A - antylopa" << std::endl;

    COORD pos5 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(7) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos5);
    std::cout << "% - barszcz sosnowskiego" << std::endl;

    COORD pos6 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(8) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos6);
    std::cout << "+ - guarana" << std::endl;

    COORD pos7 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(9) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos7);
    std::cout << "L - lis" << std::endl;

    COORD pos8 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(10) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos8);
    std::cout << "Y - mlecz" << std::endl;

    COORD pos9 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(11) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos9);
    std::cout << "O - owca" << std::endl;

    COORD pos10 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(12) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos10);
    std::cout << "* - trawa" << std::endl;

    COORD pos11 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(13) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos11);
    std::cout << "& - wilcze jagody" << std::endl;

    COORD pos12 = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(14) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos12);
    std::cout << "W - wilk" << std::endl; 
    pos = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(15) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "Z - zlow" << std::endl;*/
    pos = { static_cast<SHORT>(2 * m + 5), static_cast<SHORT>(6) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "C - czlowiek [TY]" << std::endl;
    pos = { static_cast<SHORT>(0), static_cast<SHORT>(0) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Swiat::wczytajSwiat() {
    system("cls");
    std::cout << "Wpisz nazwe pliku, z ktorego chcesz wczytac stan gry...";
    std::string nazwa;
    std::cin >> nazwa;
    nazwa += ".txt";
    FILE* plik = fopen(nazwa.c_str(), "r");
    if (plik == NULL) {
        std::cout << "BLAD\n";
        return;
    }
    else {
        int m, n, iloscOrganizmow, tarczaAlzura;
        fscanf_s(plik, "%d %d %d %d\n", &m, &n, &iloscOrganizmow, &tarczaAlzura);
        //std::cout << m << " " << n << " " << iloscOrganizmow;
        for (int i = 0; i < this->iloscOrganizmow; i++) {
            delete this->organizmy[i];
        }
        delete[] this->organizmy;
        delete[] this->czyZyje;
        this->organizmy = new Organizm * [iloscOrganizmow];
        this->czyZyje = new bool[iloscOrganizmow];

        char bufor[1024];
        for (int i = 0; i < iloscOrganizmow; i++) {
            int czyZyjeInt, sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek;
            char orgNamex[50];
            if (fgets(bufor, 1024, plik) != NULL) {
                if (sscanf(bufor, "%d %49s %d %d %d %d %d %d %d\n", &czyZyjeInt, orgNamex, &sila, &inicjatywa, &x, &y, &poprzednieX, &poprzednieY, &wiek) == 9) {
                    czyZyje[i] = czyZyjeInt;
                    std::string orgName(orgNamex);
                    //std::cout << orgName << " " << sila << " " << inicjatywa << " " << x << " " << y << " " << poprzednieX << " " << poprzednieY << " " << wiek << std::endl;
                    if (orgName == "Antylopa") this->organizmy[i] = new Antylopa(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "BarszczSosnowskiego")  this->organizmy[i] = new BarszczSosnowskiego(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Guarana") this->organizmy[i] = new Guarana(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Lis") this->organizmy[i] = new Lis(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Mlecz") this->organizmy[i] = new Mlecz(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Owca") this->organizmy[i] = new Owca(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Trawa") this->organizmy[i] = new Trawa(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "WilczeJagody") this->organizmy[i] = new WilczeJagody(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Wilk") this->organizmy[i] = new Wilk(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Zlow") this->organizmy[i] = new Zlow(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                    else if (orgName == "Czlowiek") {
                        this->organizmy[i] = new Czlowiek(sila, inicjatywa, x, y, poprzednieX, poprzednieY, wiek, *this);
                        Czlowiek* czl = dynamic_cast<Czlowiek*>(organizmy[i]);
                        czl->setTarczaAlzura(tarczaAlzura);
                    }
                }
            }
        }
        this->m = m;
        this->n = n;
        this->iloscOrganizmow = iloscOrganizmow;
        std::cout << "Wczytano stan gry pomyslnie! [wcisnij dowolny klawisz]\n";
        char c = _getch();
        fclose(plik);
        system("cls");
        rysujSwiat();
        return;
    }
}

void Swiat::zapiszSwiat() {
    system("cls");
    std::cout << "Wpisz nazwe pliku, do ktorego chcesz zapisac stan gry...";
    std::string nazwa;
    std::cin >> nazwa;
    nazwa += ".txt";
    FILE* plik = fopen(nazwa.c_str(), "w");
    if (plik == NULL) {
        std::cout << "BLAD\n";
        return;
    }
    else {
        fprintf(plik, "%d %d %d %d\n", m, n, iloscOrganizmow, tarczaAlzuraCzlowieka);
        for (int i = 0; i < iloscOrganizmow; i++)
            fprintf(plik, "%d %s\n", czyZyje[i], (organizmy[i]->organizmToString()).c_str());
        std::cout << "Zapisano pomyslnie! [wcisnij dowolny klawisz]\n";
        char c = _getch();
        fclose(plik);
        system("cls");
        rysujSwiat();
        return;
    }
}

Swiat::~Swiat() {
	for (int i = 0; i < iloscOrganizmow; i++) {
		delete organizmy[i];
	}
	delete[] organizmy;
    delete[] czyZyje;
}