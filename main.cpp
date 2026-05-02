#include <iostream>
#include "MaxHeapPriorityQueue.h"

int main() {
    MaxHeapPriorityQueue queue;

    std::cout << "Projekt 2 - Kolejka priorytetowa MAX" << std::endl;
    std::cout << "Rozmiar kolejki: " << queue.returnSize() << std::endl;

    queue.insert(100, 5);
    queue.insert(200, 10);
    queue.insert(300, 3);
    queue.insert(400, 20);
    queue.insert(500,15);
    queue.insert(600, 30);

    queue.print();

    std::cout << "Rozmiar: " << queue.returnSize() << std::endl;

    return 0;
}
