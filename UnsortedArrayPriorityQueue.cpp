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

QueueElement UnsortedArrayPriorityQueue::peek() {
    // jezeli kolejka jest pusta to zwracamy -1

    if (size == 0) {
        QueueElement emptyElemnt;
        emptyElemnt.value = -1;
        emptyElemnt.priority = -1;
        return emptyElemnt;
    }

    int maxIndex = 0;

    //szukanie elementu z najwiszkym priorytetem, zwraca index
    for (int i = 1; i < size; i++){
        if (array[i].priority > array[maxIndex].priority) {
            maxIndex = i;
        }
    }

    return array[maxIndex];
}

QueueElement UnsortedArrayPriorityQueue::extractMax() {
    //jezeli kolejka jest pusta, zwracamy -1
    if (size == 0) {
        QueueElement emptyElement;
        emptyElement.value = -1;
        emptyElement.priority = -1;
        return emptyElement;

    }

    int maxIndex = 0;

    //szukamy indeksu elementu o najwszykim priorytecie
    for (int i = 1; i < size; i++) {
        if (array[i].priority > array[maxIndex].priority) {
            maxIndex = i;
        }
    }

    //zapamietujemy element, ktory zostanie usuniety
    QueueElement maxElement = array[maxIndex];

    //przesuwamy elementy w lewo, aby usunac znaleziony element
    for (int i = maxIndex; i < size - 1; i++) {
        array[i] = array[i+1];
    }

    size--;

    return maxElement;
}