#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once
#include<iostream>

class MyString
{

public:
    char* string;

    MyString() {
        string = new char[1];
        string[0] = '\0';

    }

    MyString(const char* other) {
        string = new char[strlen(other) + 1];
        strcpy(string, other);
        string[strlen(other)] = '\0';

    }

    MyString(char* other) {
        string = new char[strlen(other) + 1];
        strcpy(string, other);
        string[strlen(other)] = '\0';

    }

    MyString(const MyString& other) {
        string = new char[strlen(other.string) + 1];
        strcpy(string, other.string);
        string[strlen(other.string)] = '\0';

    }

    MyString(MyString&& other) {
        string = other.string;
        other.string = nullptr;

    }

    ~MyString() {
        delete[] string;

    }

    int size() {
        return strlen(string);

    }

    char& operator[](std::size_t i) {
        return string[i];

    }

    const char& operator[](std::size_t i) const {
        return string[i];

    }

    MyString& operator=(const MyString& right) {
        if (this != &right) {
            char* temp = new char[strlen(right.string) + 1];
            strcpy(temp, right.string);
            delete[] string;
            string = temp;

        }
        return *this;

    }

    bool operator==(const MyString& other) {
        return !strcmp(string, other.string);

    }

    bool operator==(const char* other) {
        return !strcmp(string, other);

    }

    bool operator==(const MyString& other) const {
        return !strcmp(string, other.string);

    }

    bool operator!=(const MyString& other) {
        return strcmp(string, other.string);

    }

    bool operator!=(const char* other) {
        return strcmp(string, other);

    }

    bool operator!=(char* other) {
        return strcmp(string, other);

    }

    bool contains(char c) {
        for (int i = 0; i < strlen(string); i++) {
            if (string[i] == c)
                return 1;

        }
        return 0;

    }

    void operator+=(MyString& other) {
        char* tmp = new char[strlen(string) + strlen(other.string) + 1];
        for (int i = 0; i < strlen(string); i++)
            tmp[i] = string[i];
        for (int i = 0; i < strlen(other.string); i++)
            tmp[strlen(string) + i] = other.string[i];

        tmp[strlen(string) + strlen(other.string)] = '\0';
        delete string;
        string = tmp;

    }

    void operator+=(const char* other) {
        char* tmp = new char[strlen(string) + strlen(other) + 1];
        for (int i = 0; i < strlen(string); i++)
            tmp[i] = string[i];
        for (int i = 0; i < strlen(other); i++)
            tmp[strlen(string) + i] = other[i];

        tmp[strlen(string) + strlen(other)] = '\0';
        delete string;
        string = tmp;

    }

    void operator+=(char c) {
        int size = strlen(string);
        char* tmp = new char[size + 2];
        for (int i = 0; i < size; i++)
            tmp[i] = string[i];
        tmp[size] = c;
        tmp[size + 1] = '\0';
        delete[] string;
        string = tmp;

    }

    friend std::ostream& operator<<(std::ostream&, const MyString&);
    friend std::istream& operator>>(std::istream&, MyString&);
};

std::ostream& operator<< (std::ostream& os, const MyString& str) {
    os << str.string;
    return os;
}

std::istream& operator>> (std::istream& is, MyString& str) {
    char* ptr = new char[128];
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    is >> ptr;
    str = MyString(ptr);
    delete[] ptr;
    return is;
}