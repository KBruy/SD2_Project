#ifndef MAX_HEAP_PRIORITY_QUEUE_H
#define MAX_HEAP_PRIORITY_QUEUE_H


#include "QueueElement.h"

class MaxHeapPriorityQueue {
    private:
        QueueElement* heap;
        int size;
        int capacity;

    public:
        MaxHeapPriorityQueue();
        ~MaxHeapPriorityQueue();

        int returnSize();
};

#endif