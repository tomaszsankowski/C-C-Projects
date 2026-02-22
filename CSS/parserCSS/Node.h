#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once

template <typename T>
class Node
{
public:
	T value;
	Node<T>* prev;
	Node<T>* next;
	Node(T value) {
		this->value = value;
	};
};