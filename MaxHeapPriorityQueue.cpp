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