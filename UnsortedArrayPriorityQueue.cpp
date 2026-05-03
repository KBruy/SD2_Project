#include "UnsortedArrayPriorityQueue.h"

UnsortedArrayPriorityQueue::UnsortedArrayPriorityQueue() {
    size = 0;
    capacity = 4;

    //początkowa tablica dynamiczna
    array = new QueueElement[capacity];
}

UnsortedArrayPriorityQueue::~UnsortedArrayPriorityQueue(){
    delete[] array;
}

int UnsortedArrayPriorityQueue::returnSize() {
    return size;
}