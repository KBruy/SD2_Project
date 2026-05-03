#include <iostream>
#include "UnsortedArrayPriorityQueue.h"

int main() {
    UnsortedArrayPriorityQueue queue;

    queue.insert(100, 5);
    queue.insert(200, 30);
    queue.insert(300, 10);
    queue.insert(400, 1);
    queue.insert(500, 20);

    queue.print();

    QueueElement maxElement = queue.peek();
    std::cout << "Najwiekszy element: " <<maxElement.value << ", priorytet: " << maxElement.priority << std::endl;
    std::cout << "Rozmiar: " << queue.returnSize() << std::endl;

    return 0;
}