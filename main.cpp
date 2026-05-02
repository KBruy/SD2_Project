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

    QueueElement removed = queue.extractMax();

    std::cout << "Usunieto max: "
              << removed.value
              << ", priorytet: "
              << removed.priority
              << std::endl;

    queue.print();

    std::cout << "Rozmiar: " << queue.returnSize() << std::endl;

    return 0;
}