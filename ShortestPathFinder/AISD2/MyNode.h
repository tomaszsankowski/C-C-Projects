#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once

template <typename T>
class MyNode
{
public:
    T value;
    MyNode<T>* prev;
    MyNode<T>* next;
    MyNode(T value) {
        this->value = value;

    };
};