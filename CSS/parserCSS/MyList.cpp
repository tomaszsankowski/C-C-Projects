#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "MyList.h"
#include "Node.h"
#include "Node.cpp"
#include <iostream>

template <class T>
Node<T>* MyList<T>::get(int index) const {

	if ((index < 0) || (index > counter))
		return nullptr;

	if (index == 0)
		return first;

	if (index == (counter - 1))
		return last;

	Node<T>* temp_node = first;
	for (int i = 0; i < index; ++i) {
		temp_node = temp_node->next;
	}
	return temp_node;
}

template <class T>
void MyList<T>::insert_first(const T& value) {
	Node<T>* node = new Node<T>{ value };
	node->next = first;

	if (first != nullptr) {
		first->prev = node;
	}

	first = node;

	if (counter == 0) {
		last = first;
	}

	// One element is added
	counter++;
}

template <class T>
void MyList<T>::insert_last(const T& node) {

	if (counter == 0) {
		insert_first(node);
		return;
	}

	Node<T>* buffor = new Node<T>{ node };

	last->next = buffor;
	buffor->next = nullptr;
	buffor->prev = last;
	last = buffor;
	counter++;
}

template <class T>
void MyList<T>::insert(int index, const T& value) {
	if ((index < 0) || (index > counter)) {
		return;
	}

	if (index == 0) {
		insert_first(value);
		return;
	}
	else if (index == counter) {
		insert_last(value);
		return;
	}

	Node<T>* prev_node = first;

	for (int i = 0; i < (index - 1); ++i) {
		prev_node = prev_node->next;
	}

	Node<T>* next_node = prev_node->next;

	Node<T>* node = new Node<T>{ value };

	node->next = next_node;
	node->prev = prev_node;
	prev_node->next = node;
	next_node->prev = node;
	counter++;
}

template <class T>
int MyList<T>::search(const T& node) const {
	if (counter <= 0) {
		return -1;
	}

	Node<T>* current = first;
	if (current->value == node)
		return 0;

	for (int i = 0; i < counter; i++) {
		if (current->value == node)
			return i;

		current = current->next;
	}
	return -1;
}

template <class T>
void MyList<T>::remove_first() {
	if (counter > 0) {
		if (counter == 1) {
			Node<T>* node = first;
			delete node;
			counter--;
			first = nullptr;
			last = nullptr;
		}
		else {
			Node<T>* node = first;
			first = first->next;
			delete node;
			first->prev = nullptr;
			counter--;
		}
	}
}

template <class T>
void MyList<T>::remove_last() {
	if (counter > 1) {
		Node<T>* node = last;
		last = last->prev;
		delete node;
		last->next = nullptr;
		counter--;
	}
	else if (counter == 1) {
		remove_first();
		return;
	}
}

template <class T>
void MyList<T>::remove(int index) {
	if ((index < 0) || (index >= counter) || (counter == 0))
		return;
	else if (index == 0)
		remove_first();
	else if (index == (counter - 1))
		remove_last();
	else {
		Node<T>* node = first;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
		Node<T>* prev_node = node->prev;
		Node<T>* next_node = node->next;
		prev_node->next = next_node;
		next_node->prev = prev_node;
		delete node;
		counter--;
	}
}

template <class T>
int MyList<T>::size() const {
	return counter;
}

template <class T>
void MyList<T>::writeList() {
	Node<T>* node = first;
	for (int i = 0; i < counter; i++) {
		std::cout << node->value << "\n";
		node = node->next;
	}
	std::cout << std::endl;
}

template <class T>
void MyList<T>::deleteList() {
	if (counter > 0) {
		Node<T>* temp = first;
		while (temp->next) {
			temp = first->next;
			delete first;
			first = temp;
		}
	}
}