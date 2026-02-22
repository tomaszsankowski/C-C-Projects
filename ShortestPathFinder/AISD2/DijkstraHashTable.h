#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once

#include <iostream>
#include "MyString.h"
#include "MyList.h"

typedef struct DijMiasto {
	MyString nazwa;
	int odleglosc;
	DijMiasto* poprzednik = nullptr;
};

typedef struct DijNode {
	int size = 0;
	int tableSize = 8;
	DijMiasto* tablica = new DijMiasto[8];
	~DijNode() {
		delete[] tablica;
	}
};

class DijkstraHashTable
{
public:
	int hashSize;
	DijNode* hashTable;

	DijMiasto* get(MyString nazwa) {
		unsigned int index = hash(nazwa);
		for (int i = 0; i <= hashTable[index].size; i++) {
			if (hashTable[index].tablica[i].nazwa == nazwa)
				return &hashTable[index].tablica[i];
		}
		return nullptr;
	}

	DijMiasto* get(const char* nazwa) {
		unsigned int index = hash(nazwa);
		for (int i = 0; i <= hashTable[index].size; i++) {
			if (hashTable[index].tablica[i].nazwa == nazwa)
				return &hashTable[index].tablica[i];
		}
		return nullptr;
	}

	unsigned int hash(MyString nazwa) {
		unsigned int x = 5381;
		for (int i = 0; i < nazwa.size(); i++) {
			x = 17 + x + nazwa[i];
		}
		return x % hashSize;
	}

	DijkstraHashTable(const int HASH_SIZE) {
		hashSize = HASH_SIZE;
		hashTable = new DijNode[HASH_SIZE];
	}

	void add(DijMiasto dijmiasto) {
		unsigned int index = hash(dijmiasto.nazwa);
		if ((hashTable[index].size) == hashTable[index].tableSize) {//zwiekszamy wielkosc tablicy kiedy ilosc kolizji jest wieksza od aktualnej wielkosci
			DijMiasto* newhashTable = new DijMiasto[int(hashTable[index].tableSize) * 2];
			for (int i = 0; i < hashTable[index].tableSize; i++) {
				newhashTable[i] = hashTable[index].tablica[i];
			}
			delete[] hashTable[index].tablica;
			hashTable[index].tablica = newhashTable;
			hashTable[index].tableSize = hashTable[index].tableSize * 2;
			hashTable[index].tablica[hashTable[index].size] = dijmiasto;
			hashTable[index].size++;
		}
		else {
			hashTable[index].tablica[hashTable[index].size] = dijmiasto;
			hashTable[index].size++;
		}
	}

	~DijkstraHashTable() { delete[] hashTable; };
};