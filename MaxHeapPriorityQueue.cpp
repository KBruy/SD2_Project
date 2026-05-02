#include "MaxHeapPriorityQueue.h"

MaxHeapPriorityQueue::MaxHeapPriorityQueue() {
    size = 0;
    capacity = 4;
    heap = new QueueElement[capacity];
}

MaxHeapPriorityQueue::~MaxHeapPriorityQueue() {
    delete[] heap;
}

int MaxHeapPriorityQueue::returnSize() {
    return size;
}

void MaxHeapPriorityQueue::insert(int value, int priority) {
    if (size == capacity) {
        return;
    }

    heap[size].value = value;
    heap[size].priority = priority;
    size ++;
}