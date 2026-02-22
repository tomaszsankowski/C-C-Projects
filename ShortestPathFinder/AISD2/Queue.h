#include <iostream>

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {
        }

    };
    Node* head;
    Node* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {
    }

    bool isEmpty() const {
        return head == nullptr;

    }

    void add(const T& data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = tail = newNode;

        }
        else {
            tail->next = newNode;
            tail = newNode;

        }

    }

    T takeFirst() {
        T data = head->data;
        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;

        }
        delete temp;
        return data;

    }

    ~Queue() {
        while (!isEmpty()) {
            takeFirst();

        }

    }
};

struct QueueNode {
    int x;
    int y;
    int distance;
};