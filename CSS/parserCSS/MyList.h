#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Node.h"
#include "MyString.h"
#include <iostream>

#pragma once

template <typename T>
class MyList
{
private:
	int counter;
public:
	Node<T>* first;
	Node<T>* last;

	MyList() = default;

	Node<T>* get(int index) const;

	void insert_first(const T& node);
	void insert_last(const T& node);
	void insert(int index, const T& node);

	int search(const T& node) const;
	void deleteList();

	void remove_first();
	void remove_last();
	void remove(int index);

	void writeList();
	int size() const;
};

