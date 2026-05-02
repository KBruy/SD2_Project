#include <iostream>
#include "MaxHeapPriorityQueue.h"

int main() {
    MaxHeapPriorityQueue queue;

    queue.insert(100, 5);
    queue.insert(200, 10);
    queue.insert(300, 3);
    queue.insert(400, 20);
    queue.insert(500, 15);
    queue.insert(600, 30);

    queue.print();

    bool changed = queue.modifyKey(200, 50);

    if (changed) {
        std::cout << "Zmieniono priorytet elementu 200." << std::endl;
    } else {
        std::cout << "Nie znaleziono elementu." << std::endl;
    }

    queue.print();

    QueueElement maxElement = queue.peek();

    std::cout << "Najwiekszy element: "
              << maxElement.value
              << ", priorytet: "
              << maxElement.priority
              << std::endl;

    return 0;
}