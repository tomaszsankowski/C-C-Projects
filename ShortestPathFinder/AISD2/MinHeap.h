#pragma once

#include <iostream>
#include "MyString.h"

typedef struct HeapNode {
    MyString cityname;
    int distance = INT_MAX;
    bool isUsed = false;
};

class MinHeap {
private:
    HeapNode* heap;
    int capacity;
    int size;

public:
    MinHeap() {
        capacity = 1024;
        heap = new HeapNode[capacity];
        size = 0;

    }

    ~MinHeap() {
        delete[] heap;

    }

    void push(const HeapNode& node) {
        if (size == capacity) {
            capacity *= 16;
            HeapNode* newHeap = new HeapNode[capacity];
            for (int i = 0; i < size; i++) {
                newHeap[i] = heap[i];

            }
            delete[] heap;
            heap = newHeap;

        }
        heap[size] = node;
        int i = size;
        while (i > 0 && heap[(i - 1) / 2].distance > heap[i].distance) {
            HeapNode tmp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = tmp;
            i = (i - 1) / 2;

        }
        size++;

    }

    void pop() {
        if (size == 0) {
            return;

        }
        heap[0] = heap[size - 1];
        size--;
        int i = 0;
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < size && heap[left].distance < heap[smallest].distance) {
                smallest = left;

            }
            if (right < size && heap[right].distance < heap[smallest].distance) {
                smallest = right;

            }
            if (smallest != i) {
                HeapNode tmp = heap[i];
                heap[i] = heap[smallest];
                heap[smallest] = tmp;
                i = smallest;

            }
            else {
                break;

            }

        }

    }

    HeapNode top() {
        if (size > 0) {
            return heap[0];

        }
        return HeapNode();

    }

    HeapNode takeFirst() {
        HeapNode topNode = top();
        pop();
        return topNode;

    }

    int heapsize() {
        return size;

    }

    bool empty() {
        return size == 0;

    }
};