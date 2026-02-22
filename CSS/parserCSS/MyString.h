#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once
#include<iostream>

class MyString
{
	char* string;

public:

	MyString();
	MyString(const char* other);
	MyString(char* other);
	MyString(const MyString& other);
	MyString(MyString&& other);

	int size();
	bool contains(char c);
	void removeLast(char c);
	void deleteLast(int index);
	void removeFirst(char c);
	void removeWhiteSpaces();
	bool doesEndWith(const char* other);
	bool isDigit();
	int strtoint();
	MyString attributeValue();
	MyString attributeName();
	int countChar(char c);

	char& operator[](std::size_t i);
	const char& operator[](std::size_t i) const;
	MyString& operator=(const MyString& right);
	bool operator==(const MyString& other);
	bool operator!=(const MyString& other);
	bool operator!=(const char* other);
	bool operator!=(char* other);
	void operator+=(MyString& other);
	void operator+=(char c);
	void operator+=(const char* other);
	//void operator+=(char* other);
	friend std::ostream& operator<<(std::ostream&, const MyString&);
	friend std::istream& operator>>(std::istream&, MyString&);

	~MyString();

};

