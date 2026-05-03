#include "UnsortedArrayPriorityQueue.h"
#include <iostream>

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

void UnsortedArrayPriorityQueue::resize() {
    int newCapacity = capacity * 2;

    // tworzenie nowej tablicy
    QueueElement* newArray = new QueueElement[newCapacity];

    //przepisujemy elementy 
    for (int i = 0; i < size; i++) {
        newArray[i] = array[i];
    }

    delete[] array;

    array = newArray;
    capacity = newCapacity;
}

void UnsortedArrayPriorityQueue::insert(int value, int priority) {
    if (size == capacity) {
        resize();

    }

    //dodajemy element na koniec bez sortowania
    array[size].value = value;
    array[size].priority = priority;

    size++;

}

void UnsortedArrayPriorityQueue::print() {
    if (size == 0) {
        std::cout << "Kolejka jest pusta" << std::endl;
        return;
    }

    std::cout << "Tablica nieposortowana:" <<std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << "(" << array[i].value <<", p= " << array[i].priority << ") ";
    }

    std::cout << std::endl;
}