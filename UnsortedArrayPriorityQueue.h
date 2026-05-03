#ifndef UNSORTED_ARRAY_PRIORITY_QUEUE_H
#define UNSORTED_ARRAY_PRIORITY_QUEUE_H

#include "QueueElement.h"

class UnsortedArrayPriorityQueue {
    private:
        QueueElement* array; //dynamiczna tablica z elementami kolejki
        int size;
        int capacity;

        void resize();

    public:
        UnsortedArrayPriorityQueue();
        ~UnsortedArrayPriorityQueue();

        void print();

        int returnSize();
        void insert(int value, int priority); //dodaje element

        QueueElement peek(); //zwraca element o najwiekszym priorytecie
        QueueElement extractMax(); // usuwa elemnt o najwiekszym priorytecie i zwraca go
    
};

#endif