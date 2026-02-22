#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "MyString.h"
#include <iostream>
#include <string.h>
#include <math.h>

MyString::MyString() {
	string = new char[1];
	string[0] = '\0';
}

MyString::MyString(const char* other) {
	string = new char[strlen(other) + 1];
	strcpy(string, other);
	string[strlen(other)] = '\0';
}

MyString::MyString(char* other) {
	string = new char[strlen(other) + 1];
	strcpy(string, other);
	string[strlen(other)] = '\0';
}

MyString::MyString(const MyString& other) {
	string = new char[strlen(other.string) + 1];
	strcpy(string, other.string);
	string[strlen(other.string)] = '\0';
}

MyString::MyString(MyString&& other) {
	string = other.string;
	other.string = nullptr;
}

MyString::~MyString() {
	delete[] string;
}

int MyString::size() {
	return strlen(string);
}

char& MyString::operator[](std::size_t i) {
	return string[i];
}

const char& MyString::operator[](std::size_t i) const {
	return string[i];
}

MyString& MyString::operator=(const MyString& right) {
	delete[] string;
	string = new char[strlen(right.string) + 1];
	strcpy(string, right.string);
	string[strlen(right.string)] = '\0';
	return *this;
}

std::ostream& operator<< (std::ostream& os, const MyString& str) {
	os << str.string;
	return os;
}

std::istream& operator>> (std::istream& is, MyString& str) {
	char* ptr = new char[128];
	char c;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	is >> ptr;
	str = MyString(ptr);
	delete[] ptr;
	return is;
}

bool MyString::operator==(const MyString& other) {
	return !strcmp(string, other.string);
}

bool MyString::operator!=(const MyString& other) {
	return strcmp(string, other.string);
}

bool MyString::operator!=(const char* other) {
	return strcmp(string, other);
}

bool MyString::operator!=(char* other) {
	return strcmp(string, other);
}

bool MyString::contains(char c) {
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == c)
			return 1;
	}
	return 0;
}

void MyString::operator+=(MyString& other) {
	char* tmp = new char[strlen(string) + strlen(other.string) + 1];
	for (int i = 0; i < strlen(string); i++)
		tmp[i] = string[i];
	for (int i = 0; i < strlen(other.string); i++)
		tmp[strlen(string) + i] = other.string[i];

	tmp[strlen(string) + strlen(other.string)] = '\0';
	delete string;
	string = tmp;
}

void MyString::operator+=(const char* other) {
	char* tmp = new char[strlen(string) + strlen(other) + 1];
	for (int i = 0; i < strlen(string); i++)
		tmp[i] = string[i];
	for (int i = 0; i < strlen(other); i++)
		tmp[strlen(string) + i] = other[i];

	tmp[strlen(string) + strlen(other)] = '\0';
	delete string;
	string = tmp;
}

void MyString::operator+=(char c) {
	int size = strlen(string);
	char* tmp = new char[size + 2];
	for (int i = 0; i < size; i++)
		tmp[i] = string[i];
	tmp[size] = c;
	tmp[size + 1] = '\0';
	delete[] string;
	string = tmp;
}

void MyString::removeLast(char c) {
	if (string[strlen(string) - 1] == c)
		deleteLast(strlen(string) - 1);
}

void MyString::deleteLast(int index) {
	string[index] = '\0';
}

void MyString::removeFirst(char c) {
	char* tmp = new char[strlen(string)];
	for (int i = 1; i <= strlen(string); i++) {
		tmp[i - 1] = string[i];
	}
	tmp[strlen(string) - 1] = '\0';
	delete[] string;
	string = tmp;
}

bool MyString::doesEndWith(const char* other) {
	int i = (strlen(string) - strlen(other));
	int j = 0;
	for (i, j; i < strlen(string); i++, j++) {
		if (other[j] != string[i])
			return false;
	}
	return true;
}

bool MyString::isDigit() {
	for (int i = 0; i < strlen(string); i++) {
		if (!isdigit(string[i]))
			return false;
	}
	return true;
}

int MyString::strtoint() {
	return atoi(string);
}

MyString MyString::attributeName() {
	char* buffer = new char[strlen(string)];
	size_t i;
	for (i = 0; (i < strlen(string)) && (string[i] != ':'); ++i) {
		buffer[i] = string[i];
	}
	buffer[i] = '\0';
	MyString result(buffer);
	delete[] buffer;
	return result;
}

MyString MyString::attributeValue() {
	MyString buffor;
	int i = 0;
	while (string[i] != ':')
		i++;
	i++;
	if (string[i] == ' ')
		i++;
	for (int j = i; j < strlen(string); j++) {
		buffor += string[j];
	}
	return buffor;
}


void MyString::removeWhiteSpaces() {
	int counter = 0;
	for (int i = 0; i < strlen(string); i++) {
		if ((string[i] > ' ') && (string[i] != '\n') && (string[i] != '\t') && (string[i] != '\0')) {
			string[counter] = string[i];
			counter++;
		}
	}
	string[counter] = '\0';
}

int MyString::countChar(char c) {
	int counter = 0;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] == c)
			counter++;
	}
	return counter;
}