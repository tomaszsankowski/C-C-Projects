#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "MyNode.h"
#include "MyString.h"
#include <iostream>

#pragma once

template <typename T>
class MyList
{
private:
    int counter;
public:
    MyNode<T>* first = nullptr;
    MyNode<T>* last = nullptr;

    MyList() = default;

    MyNode<T>* get(int index) const {

        if ((index < 0) || (index > counter))
            return nullptr;

        if (index == 0)
            return first;

        if (index == (counter - 1))
            return last;

        MyNode<T>* temp_MyNode = first;
        for (int i = 0; i < index; ++i) {
            temp_MyNode = temp_MyNode->next;

        }
        return temp_MyNode;

    }


    void insert_first(const T& value) {
        MyNode<T>* node = new MyNode<T>{ value
        };
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


    void insert_last(const T& node) {

        if (counter == 0) {
            insert_first(node);
            return;

        }

        MyNode<T>* buffor = new MyNode<T>{ node
        };

        last->next = buffor;
        buffor->next = nullptr;
        buffor->prev = last;
        last = buffor;
        counter++;

    }


    void insert(int index, const T& value) {
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

        MyNode<T>* prev_node = first;

        for (int i = 0; i < (index - 1); ++i) {
            prev_node = prev_node->next;

        }

        MyNode<T>* next_node = prev_node->next;

        MyNode<T>* node = new MyNode<T>{ value
        };

        node->next = next_node;
        node->prev = prev_node;
        next_node->next = node;
        prev_node->prev = node;
        counter++;

    }


    int search(const T& node) const {
        if (counter <= 0) {
            return -1;

        }

        MyNode<T>* current = first;
        if (current->value == node)
            return 0;

        for (int i = 0; i < counter; i++) {
            if (current->value == node)
                return i;

            current = current->next;

        }
        return -1;

    }


    void remove_first() {
        if (counter > 0) {
            if (counter == 1) {
                MyNode<T>* MyNode = first;
                delete MyNode;
                counter--;
                first = nullptr;
                last = nullptr;

            }
            else {
                MyNode<T>* MyNode = first;
                first = first->next;
                delete MyNode;
                first->prev = nullptr;
                counter--;

            }

        }

    }


    void remove_last() {
        if (counter > 1) {
            MyNode<T>* MyNode = last;
            last = last->prev;
            delete MyNode;
            last->next = nullptr;
            counter--;

        }
        else if (counter == 1) {
            remove_first();
            return;

        }

    }


    void remove(int index) {
        if ((index < 0) || (index >= counter) || (counter == 0))
            return;
        else if (index == 0)
            remove_first();
        else if (index == (counter - 1))
            remove_last();
        else {
            MyNode<T>* node = first;
            for (int i = 0; i < index; i++) {
                node = node->next;

            }
            MyNode<T>* prev_node = node->prev;
            MyNode<T>* next_node = node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete node;
            counter--;

        }

    }


    int size() const {
        return counter;

    }


    void writeList() {
        MyNode<T>* MyNode = first;
        for (int i = 0; i < counter; i++) {
            std::cout << MyNode->value << " ";
            MyNode = MyNode->next;

        }

    }


    void deleteList() {
        if (counter > 0) {
            MyNode<T>* temp = first;
            while (temp->next) {
                temp = first->next;
                delete first;
                first = temp;

            }

        }

    }
};