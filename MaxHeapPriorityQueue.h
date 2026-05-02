#ifndef MAX_HEAP_PRIORITY_QUEUE_H
#define MAX_HEAP_PRIORITY_QUEUE_H


#include "QueueElement.h"

class MaxHeapPriorityQueue {
    private:
        QueueElement* heap; //dynamiczna tablica przechowujaca kopiec
        int size; // aktualna liczba elementow
        int capacity; // pojemnosc tablicy

        void heapifyUp(int index); //naprawaia kopiec po dodaniu elementu
        void resize(); //podwaja pojemnosc tablicy

        void heapifyDown(int index); //naprawia kopiec po usunieciu elementu

    public:
        MaxHeapPriorityQueue();
        ~MaxHeapPriorityQueue();

        void print();

        int returnSize(); // zwraca liczbe elemntow
        void insert(int value, int priority); // dodaje eleemnt do kolejki

        QueueElement peek(); //zwraca element o najwiekszym priorytecie

        QueueElement extractMax(); // usuwa i zwraca element o najwiekszym priorytecie
        
};

#endif