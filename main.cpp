#include <iostream>
#include "UnsortedArrayPriorityQueue.h"

int main() {
    UnsortedArrayPriorityQueue queue;

    std::cout << "Kolejka priorytetowa MAX - tablica nieposortowana" << std::endl;
    std::cout << "Rozmiar kolejki: " << queue.returnSize() << std::endl;

    return 0;
}