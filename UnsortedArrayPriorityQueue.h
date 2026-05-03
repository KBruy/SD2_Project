#ifndef UNSORTED_ARRAY_PRIORITY_QUEUE_H
#define UNSORTED_ARRAY_PRIORITY_QUEUE_H

#include "QueueElement.h"

class UnsortedArrayPriorityQueue {
    private:
        QueueElement* array; //dynamiczna tablica z elementami kolejki
        int size;
        int capacity;

    public:
        UnsortedArrayPriorityQueue();
        ~UnsortedArrayPriorityQueue();

        int returnSize();
    
};

#endif