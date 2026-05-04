#include <iostream>
#include "MaxHeapPriorityQueue.h"
#include "UnsortedArrayPriorityQueue.h"

int main() {
    MaxHeapPriorityQueue heapQueue;
    UnsortedArrayPriorityQueue arrayQueue;

    // te same dane dodajemy do obu implementacji
    heapQueue.insert(100, 5);
    heapQueue.insert(200, 30);
    heapQueue.insert(300, 10);
    heapQueue.insert(400, 1);
    heapQueue.insert(500, 20);

    arrayQueue.insert(100, 5);
    arrayQueue.insert(200, 30);
    arrayQueue.insert(300, 10);
    arrayQueue.insert(400, 1);
    arrayQueue.insert(500, 20);

    std::cout << "=== Kopiec MAX ===" << std::endl;
    heapQueue.print();

    std::cout << "=== Tablica nieposortowana ===" << std::endl;
    arrayQueue.print();

    QueueElement heapMax = heapQueue.peek();
    QueueElement arrayMax = arrayQueue.peek();

    std::cout << std::endl;
    std::cout << "Peek kopiec: "
              << heapMax.value
              << ", priorytet: "
              << heapMax.priority
              << std::endl;

    std::cout << "Peek tablica: "
              << arrayMax.value
              << ", priorytet: "
              << arrayMax.priority
              << std::endl;

    QueueElement heapRemoved = heapQueue.extractMax();
    QueueElement arrayRemoved = arrayQueue.extractMax();

    std::cout << std::endl;
    std::cout << "Extract kopiec: "
              << heapRemoved.value
              << ", priorytet: "
              << heapRemoved.priority
              << std::endl;

    std::cout << "Extract tablica: "
              << arrayRemoved.value
              << ", priorytet: "
              << arrayRemoved.priority
              << std::endl;

    std::cout << std::endl;
    std::cout << "Po usunieciu max:" << std::endl;

    std::cout << "Kopiec:" << std::endl;
    heapQueue.print();

    std::cout << "Tablica:" << std::endl;
    arrayQueue.print();

    return 0;
}