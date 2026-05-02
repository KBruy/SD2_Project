#ifndef MAX_HEAP_PRIORITY_QUEUE_H
#define MAX_HEAP_PRIORITY_QUEUE_H


#include "QueueElement.h"

class MaxHeapPriorityQueue {
    private:
        QueueElement* heap;
        int size;
        int capacity;

        void heapifyUp(int index);
        void resize();

    public:
        MaxHeapPriorityQueue();
        ~MaxHeapPriorityQueue();

        void print();

        int returnSize();
        void insert(int value, int priority);

        QueueElement peek();
        
};

#endif