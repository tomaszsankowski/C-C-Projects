#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "MyString.h"
#include "MyList.h"

#pragma once
typedef struct Sasiad {
    MyString nazwa;
    int odleglosc;

    bool operator==(const Sasiad& other) const {
        return (nazwa == other.nazwa && odleglosc == other.odleglosc);

    }
};

typedef struct Miasto {
    MyString nazwa;
    MyList<Sasiad> sasiedzi{
    };
    int x, y;
    int odleglosc;
    Miasto* poprzednik = nullptr;
    ~Miasto() {
        sasiedzi.deleteList();
    };
};

typedef struct Node {
    int size = 0;
    int tableSize = 8;
    Miasto* tablica = new Miasto[8];
    ~Node() {
        delete[] tablica;

    }
};

class HashTable
{
public:
    int hashSize;
    Node* hashTable;

    Miasto* get(const MyString& nazwa) {
        unsigned int index = hash(nazwa);
        for (int i = 0; i <= hashTable[index].size; i++) {
            if (hashTable[index].tablica[i].nazwa == nazwa)
                return &hashTable[index].tablica[i];

        }
        return nullptr;

    }


    Miasto* get(const char* nazwa) {
        unsigned int index = hash(nazwa);
        for (int i = 0; i <= hashTable[index].size; i++) {
            if (hashTable[index].tablica[i].nazwa == nazwa)
                return &hashTable[index].tablica[i];

        }
        return nullptr;

    }

    unsigned int hash(const char* nazwa) {
        unsigned int x = 5381;
        for (int i = 0; i < strlen(nazwa); i++) {
            x = 17 + x * 17 + nazwa[i] * 11;

        }
        return x % hashSize;

    }

    unsigned int hash(const MyString& nazwa) {
        unsigned int x = 5381;
        for (int i = 0; i < strlen(nazwa.string); i++) {
            x = 17 + x * 17 + nazwa[i] * 11;

        }
        return x % hashSize;

    }


    HashTable(const int HASH_SIZE) {
        hashSize = HASH_SIZE;
        hashTable = new Node[HASH_SIZE];

    }


    void add(const Miasto& miasto) {
        unsigned int index = hash(miasto.nazwa);
        if ((hashTable[index].size) == hashTable[index].tableSize) {//zwiekszamy wielkosc tablicy kiedy ilosc kolizji jest wieksza od aktualnej wielkosci
            Miasto* newhashTable = new Miasto[int(hashTable[index].tableSize) * 2];
            for (int i = 0; i < hashTable[index].tableSize; i++) {
                newhashTable[i] = hashTable[index].tablica[i];

            }
            delete[] hashTable[index].tablica;
            hashTable[index].tablica = newhashTable;
            hashTable[index].tableSize = hashTable[index].tableSize * 2;
            hashTable[index].tablica[hashTable[index].size] = miasto;
            hashTable[index].size++;

        }
        else {
            hashTable[index].tablica[hashTable[index].size] = miasto;
            hashTable[index].size++;

        }

    }


    ~HashTable() {
        delete[] hashTable;
    };
};