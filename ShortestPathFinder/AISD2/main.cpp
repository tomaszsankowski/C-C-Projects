#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "MyString.h"
#include "MyList.h"
#include "HashTable.h"
#include "MinHeap.h"
#include "Queue.h"

using std::cout;
using std::cin;
using std::endl;

std::ostream& operator<< (std::ostream& os, Sasiad& sasiad) {
    os << " " << sasiad.nazwa << ": " << sasiad.odleglosc << " ";
    return os;
}

int readNumber() {
    int num = 0;
    char c = getchar();
    while (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
        c = getchar();

    }
    while (c >= '0' && c <= '9') {
        num = num * 10 + (c - '0');
        c = getchar();

    }
    return num;
}

void shortestPath(MyString skad, MyString dokad, bool czyWypisac, HashTable& tablicaMiast, Miasto* miasta, int iloscMiast) {
    Miasto* tmp;
    for (int i = 0; i < iloscMiast; i++) {
        tmp = tablicaMiast.get(miasta[i].nazwa);
        tmp->odleglosc = INT_MAX;
        tmp->poprzednik = nullptr;

    }

    MinHeap kopiec;
    HeapNode startNode;
    startNode.cityname = skad;
    startNode.distance = 0;
    kopiec.push(startNode);
    HeapNode node;
    Miasto* currentCity;
    MyNode<Sasiad>* current_node;
    Miasto* city;
    HeapNode heapNode;

    while (!kopiec.empty()) {
        node = kopiec.takeFirst();

        if (node.cityname == dokad) {
            cout << node.distance;
            if (czyWypisac) {
                cout << " ";
                MyString* path = new MyString[iloscMiast];
                int index = 0;
                Miasto* temp = tablicaMiast.get(node.cityname);
                temp = temp->poprzednik;
                while (temp != nullptr && temp->nazwa != skad) {
                    path[index] = temp->nazwa;
                    index++;
                    temp = temp->poprzednik;

                }
                for (int i = index - 1; i >= 0; i--) {
                    cout << path[i] << " ";

                }
                delete[] path;

            }
            cout << endl;
            return;

        }

        if (node.isUsed)
            continue;

        node.isUsed = true;

        currentCity = tablicaMiast.get(node.cityname);
        current_node = currentCity->sasiedzi.first;
        int iloscSasiadow = currentCity->sasiedzi.size();
        for (int i = 0; i < iloscSasiadow; i++) {
            city = tablicaMiast.get(current_node->value.nazwa);
            heapNode.cityname = city->nazwa;
            heapNode.distance = node.distance + current_node->value.odleglosc;
            if (heapNode.distance < city->odleglosc) {
                city->odleglosc = heapNode.distance;
                city->poprzednik = currentCity;
                kopiec.push(heapNode);

            }
            current_node = current_node->next;

        }

    }
    cout << 0 << endl;
}


void znajdzSasiadow(Miasto* current, MyString** mapaMiast, bool** visited, char** mapa, HashTable& tablicaMiast, Miasto* miasta, int kolumny, int wiersze) {
    Queue<QueueNode> kolejka;
    QueueNode firstNode;
    firstNode.x = current->x;
    firstNode.y = current->y;
    firstNode.distance = 0;
    kolejka.add(firstNode);
    while (!kolejka.isEmpty()) {
        QueueNode currentNode = kolejka.takeFirst();
        int x = currentNode.x;
        int y = currentNode.y;
        int distance = currentNode.distance;
        visited[y][x] = true;
        if (mapa[y][x] == '*' && (x != current->x || y != current->y)) {
            Sasiad sasiad;
            sasiad.nazwa = mapaMiast[y][x];
            sasiad.odleglosc = distance;
            current->sasiedzi.insert_last(sasiad);
            continue;

        }
        if (x > 0 && mapa[y][x - 1] != '.' && visited[y][x - 1] == false) {
            visited[y][x - 1] = true;
            QueueNode addNode;
            addNode.x = x - 1;
            addNode.y = y;
            addNode.distance = distance + 1;
            kolejka.add(addNode);

        }
        if (y > 0 && mapa[y - 1][x] != '.' && visited[y - 1][x] == false) {
            visited[y - 1][x] = true;
            QueueNode addNode;
            addNode.x = x;
            addNode.y = y - 1;
            addNode.distance = distance + 1;
            kolejka.add(addNode);

        }
        if (y < wiersze - 1 && mapa[y + 1][x] != '.' && visited[y + 1][x] == false) {
            visited[y + 1][x] = true;
            QueueNode addNode;
            addNode.x = x;
            addNode.y = y + 1;
            addNode.distance = distance + 1;
            kolejka.add(addNode);

        }
        if (x < kolumny - 1 && mapa[y][x + 1] != '.' && visited[y][x + 1] == false) {
            visited[y][x + 1] = true;
            QueueNode addNode;
            addNode.x = x + 1;
            addNode.y = y;
            addNode.distance = distance + 1;
            kolejka.add(addNode);

        }

    }
}

int main() {
    //tworzenie mapy
    int kolumny, wiersze;
    std::cin >> kolumny >> wiersze;
    char** mapa = new char* [wiersze];
    MyString** mapaMiast = new MyString * [wiersze];
    for (int i = 0; i < wiersze; i++) {
        mapa[i] = new char[kolumny];
        mapaMiast[i] = new MyString[kolumny];

    }
    int iloscMiast = 0;
    char c;

    //wczytywanie mapy do tablicy dwuwymiarowej char
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            while (c = getchar()) {
                if (c != '\n' && c != ' ') {
                    if (c == '*')
                        iloscMiast++;
                    mapa[i][j] = c;
                    break;

                }

            }

        }

    }
    const int HASH_SIZE = 5 * iloscMiast;

    //wczytywanie nazw miast
    Miasto* miasta = new Miasto[iloscMiast];
    HashTable tablicaMiast(HASH_SIZE);
    int indeksMiasta = 0;

    Miasto buffor;
    bool znalezionoNazwe;
    int m, n, iterator;
    char nazwa[20];
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            if (mapa[i][j] == '*') {
                znalezionoNazwe = false;
                for (int ii = -1; ii <= 1; ii++) {
                    if (!znalezionoNazwe) {
                        for (int jj = -1; jj <= 1; jj++) {
                            m = i + ii;
                            n = j + jj;
                            if (m >= 0 && m < wiersze && n >= 0 && n < kolumny && !(n == j && m == i)) {
                                if (mapa[m][n] != '.' && mapa[m][n] != '#' && mapa[m][n] != '*') {
                                    if ((n - 1) > 0) {//cofamy sie na ostatni z lewej znak nazwy miasta
                                        while (mapa[m][n - 1] != '.' && mapa[m][n - 1] != '#' && mapa[m][n - 1] != '*')
                                            n--;

                                    }
                                    iterator = 0;
                                    while (n < kolumny && mapa[m][n] != '.' && mapa[m][n] != '#' && mapa[m][n] != '*') {
                                        nazwa[iterator] = mapa[m][n];
                                        mapa[m][n] = '.';
                                        n++;
                                        iterator++;

                                    }
                                    nazwa[iterator] = '\0';
                                    buffor.nazwa = nazwa;
                                    mapaMiast[i][j] = nazwa;
                                    buffor.x = j;
                                    buffor.y = i;
                                    miasta[indeksMiasta].nazwa = nazwa;
                                    miasta[indeksMiasta].x = j;
                                    miasta[indeksMiasta].y = i;
                                    tablicaMiast.add(buffor);
                                    indeksMiasta++;
                                    znalezionoNazwe = true;
                                    break;

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    //szukanie sasiadow
    bool** visited = new bool* [wiersze];
    for (int j = 0; j < wiersze; j++)
        visited[j] = new bool[kolumny];


    Miasto* current;
    int currentX, currentY;
    for (int i = 0; i < iloscMiast; i++) {
        current = tablicaMiast.get(miasta[i].nazwa);
        //sprawdzamy czy jest mozliwosc ruchu dookola
        currentX = current->x;
        currentY = current->y;
        if (currentX > 0 && mapa[currentY][currentX - 1] == '.' && currentY > 0 && mapa[currentY - 1][currentX] == '.' && currentY < wiersze - 1 && mapa[currentY + 1][currentX] == '.' && currentX < kolumny - 1 && mapa[currentY][currentX + 1] == '.')
            continue;
        for (int j = 0; j < wiersze; j++) {
            for (int k = 0; k < kolumny; k++)
                visited[j][k] = false;

        }
        znajdzSasiadow(current, mapaMiast, visited, mapa, tablicaMiast, miasta, kolumny, wiersze);

    }

    for (int j = 0; j < wiersze; j++)
        delete[] visited[j];
    delete[] visited;


    //wczytywanie lotow
    int iloscLotow = readNumber();
    char miasto1[16];
    char miasto2[16];
    int czasLotu;
    MyNode<Sasiad>* node;
    bool connectionFound;
    Sasiad sasiad;
    for (int i = 0; i < iloscLotow; i++) {
        iterator = 0;
        while ((c = getchar()) && c != '\n' && c != ' ') {
            miasto1[iterator] = c;
            iterator++;

        }
        miasto1[iterator] = '\0';
        iterator = 0;
        while ((c = getchar()) && c != '\n' && c != ' ') {
            miasto2[iterator] = c;
            iterator++;

        }
        miasto2[iterator] = '\0';
        czasLotu = readNumber();
        current = tablicaMiast.get(miasto1);
        sasiad.nazwa = miasto2;
        sasiad.odleglosc = czasLotu;
        current->sasiedzi.insert_last(sasiad);
    }

    //wczytywanie polaczen
    int iloscPolaczen = readNumber();
    bool tryb;
    for (int i = 0; i < iloscPolaczen; i++) {
        iterator = 0;
        while ((c = getchar()) && c != '\n' && c != ' ') {
            miasto1[iterator] = c;
            iterator++;

        }
        miasto1[iterator] = '\0';
        iterator = 0;
        while ((c = getchar()) && c != '\n' && c != ' ') {
            miasto2[iterator] = c;
            iterator++;

        }
        miasto2[iterator] = '\0';
        while ((c = getchar()) && c != '\n' && c != ' ') {
            tryb = c - '0';

        }
        shortestPath(miasto1, miasto2, tryb, tablicaMiast, miasta, iloscMiast);

    }




    //dealokacja pamieci
    for (int i = 0; i < wiersze; i++) {
        delete[] mapa[i];
        delete[] mapaMiast[i];

    }
    delete[] mapaMiast;
    delete[] miasta;
    delete[] mapa;
}