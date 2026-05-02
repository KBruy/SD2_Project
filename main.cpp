#include <iostream>
#include "MaxHeapPriorityQueue.h"

int main() {
    MaxHeapPriorityQueue queue;

    std::cout << "Projekt 2 - Kolejka priorytetowa MAX" << std::endl;
    std::cout << "Rozmiar kolejki: " << queue.returnSize() << std::endl;

    queue.insert(100, 5);
    queue.insert(200, 10);

    std::cout << "Rozmiar po dodaniu: " << queue.returnSize() << std::endl;

    return 0;
}
