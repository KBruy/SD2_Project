#include "MaxHeapPriorityQueue.h"
#include <iostream>

MaxHeapPriorityQueue::MaxHeapPriorityQueue() {
    size = 0;
    capacity = 4;
    heap = new QueueElement[capacity];
}

MaxHeapPriorityQueue::~MaxHeapPriorityQueue() {
    delete[] heap; //zwolnienie pamieci
}

int MaxHeapPriorityQueue::returnSize() {
    return size;
}

void MaxHeapPriorityQueue::insert(int value, int priority) {
    // jezeli tablica jest pelna, zwiekszamy jej pojemnosc
    if (size == capacity) { 
        resize();
    }

    //dodajemy nowy element na koniec kopca
    heap[size].value = value;
    heap[size].priority = priority;

    //naprawamiay kopiec po dodaniu
    heapifyUp(size);

    size ++;
}

void MaxHeapPriorityQueue::heapifyUp(int index) {
    //przesuwamy element w gore dopki ma wikeszy priorytet niz rodzic
    while (index > 0) {
        int parentIndex = (index - 1) / 2;

        if (heap[parentIndex].priority >= heap[index].priority) {
            break;
        }

        QueueElement temp = heap[parentIndex];
        heap[parentIndex] = heap[index];
        heap[index] = temp;

        index = parentIndex;
    }
    
}

void MaxHeapPriorityQueue::print() {
    if (size == 0) {
        std::cout << "Kolejka jest pusta" << std::endl;
        return;
    }

    std::cout << "Kopiec: " << std::endl;
    
    for (int i = 0; i < size; i++) {
        std::cout << "("<<heap[i].value << ", p= " << heap[i].priority << ") ";
    }

    std::cout << std::endl;
}

void MaxHeapPriorityQueue::resize() {
    //tworzymy nowa wieksz tablice
    int newCapacity = capacity * 2;
    QueueElement* newHeap = new QueueElement[newCapacity];

    //przepisanie starych elemntow do nowej tablicy
    for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
    }

    delete[] heap;

    heap = newHeap;
    capacity = newCapacity;
}

QueueElement MaxHeapPriorityQueue::peek() {
    // dla pustej kolejki zwracamy wartosci "umowne" 
    if (size == 0) {
        QueueElement emptyElement;
        emptyElement.value = -1;
        emptyElement.priority = -1;
        return emptyElement;
        // -1 -> kolejka byla pusta
    }
    // w kopcu max najwiekszy priorytet jest zawsze w korzeniu
    return heap[0];
}