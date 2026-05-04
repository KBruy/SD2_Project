#include <iostream>
#include "Menu.h"
#include "MaxHeapPriorityQueue.h"
#include "UnsortedArrayPriorityQueue.h"
#include "Research.h"

void Menu::run() {
    int choice = -1;

    while (choice != 0) {
        std::cout << std::endl;
        std::cout << "=== Projekt 2 ===" <<std::endl;
        std::cout << "1. Kopiec binarny MAX" << std::endl;
        std::cout << "2. Tablica nieposortowana" << std::endl;
        std::cout << "3. Badania" << std::endl;
        std::cout << "0. Zakoncz" << std::endl;
        std::cout << "Wybor: ";

        std::cin >> choice;

        switch (choice) {
            case 1:
                heapMenu();
                break;
            case 2:
                arrayMenu();
                break;
            case 3:
                Research research;
                research.runAll();
                break;
            case 0:
                std::cout << "Koniec programu" << std::endl;
                break;

            default:
                std::cout<< "Niepoprawny wybor" << std::endl;

        }
    }
}

void Menu::heapMenu() {
    MaxHeapPriorityQueue queue;
    int choice = -1;

    while (choice != 0) {
        std::cout << std::endl;
        std::cout << "=== Kopiec binarny MAX ===" << std::endl; 
        std::cout << "1. Dodaj element" << std::endl;
        std::cout << "2. Podejrzyj max" << std::endl;
        std:: cout << "3. Usun max" << std::endl;
        std:: cout << "4. Zmien priorytet" << std::endl;
        std::cout << "5. Pokaz rozmiar" << std::endl;
        std::cout << "6. Wyswietl kopiec" << std::endl;
        std::cout << "0. Powrot" << std::endl;
        std::cout << "Wybor: ";

        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                int priority;

                std::cout << "Podaj wartosc: ";
                std::cin >> value;
                std::cout << "Podaj priorytet: ";
                std::cin >> priority;

                queue.insert(value, priority);
                std::cout << "Dodano element" << std::endl;
                break;

            }

            case 2: {
                QueueElement maxElement = queue.peek();
                if (maxElement.priority == -1) {
                    std::cout << "Kolejka jest pusta" << std::endl;

                } else {
                    std::cout << "Max: " << maxElement.value << ", priorytet: " << maxElement.priority << std::endl;
                }
                break;
            }

            case 3: {
                QueueElement removed = queue.extractMax();
                if (removed.priority == -1) {
                    std::cout << "Kolejka jest pusta" << std::endl;

                }else{
                    std::cout<<"Usunieto: "<< removed.value << ", priorytet: "<< removed.priority << std::endl;

                }
                break;
            }

            case 4: {
                int value;
                int newPriority;

                std::cout << "Podaj wartosc elementu: ";
                std::cin >> value;

                std::cout << "Podaj nowy priorytet: ";
                std::cin >> newPriority;

                if (queue.modifyKey(value, newPriority)) {
                    std::cout << "Zmieniono priorytet" << std::endl;
                }
                break;
            }

            case 5:
            std::cout<<"Rozmiar: " << queue.returnSize() << std::endl;
            break;
            
            case 6:
            queue.print();
            break;

            case 0:
                std::cout << "Powrot do menu glownego" << std::endl;
                break;

            default:
            std::cout <<"Niepoprawny wybor" << std::endl;
            break;
        }
    } 
}

void Menu::arrayMenu() {
    UnsortedArrayPriorityQueue queue;
    int choice = -1;

    while (choice != 0)
    {
        std::cout << std::endl;
        std::cout << "=== Tablica nieposortowana ===" << std::endl;
        std::cout << "1. Dodaj element" << std::endl;
        std::cout << "2. Podejrzyj max" << std::endl;
        std::cout << "3. Usun max" << std::endl;
        std::cout << "4. Zmien priorytet" << std::endl;
        std::cout << "5. Pokaz rozmiar" << std::endl;
        std::cout << "6. Wyswietl tablice" << std::endl;
        std::cout << "0. Powrot" << std::endl;
        std::cout << "Wybor: ";

        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                int priority;

                std::cout << "Podaj wartosc: ";
                std::cin >> value;

                std::cout << "Podaj priorytet: ";
                std::cin >> priority;

                queue.insert(value, priority);
                std::cout << "Dodano element" << std::endl;
                break;
            }

            case 2: {
                QueueElement maxElement = queue.peek();

                if (maxElement.priority == -1) {
                    std::cout << "Kolejka jest pusta" << std::endl;
                }
                else{
                    std::cout <<"Max: " <<maxElement.value << ", priorytet: "<< maxElement.priority <<std::endl;
                }
                break;
            }

            case 3: {
                QueueElement removed = queue.extractMax();

                if (removed.priority == -1) {
                    std::cout << "Kolejka jest pusta" << std::endl;
                } else {
                    std::cout << "Usunieto: "<< removed.value << ", priorytet: "<< removed.priority<<std::endl;
                }
                break;
            }

            case 4: {
                int value;
                int newPriority;

                std::cout << "Podaj wartosc elementu: ";
                std::cin >> value;

                std::cout << "Podaj nowy priorytet: ";
                std::cin >> newPriority;

                if (queue.modifyKey(value, newPriority)) {
                    std::cout << "Zmieniono priorytet" << std::endl;
                } else {
                    std::cout << "Nie znaleziono elementu " << std::endl;
                }
                break;
            }

            case 5:
            std::cout<<"Rozmiar" << queue.returnSize() << std::endl;
            break;

            case 6:
            queue.print();
            break;

            case 0:
            std::cout << "Powrot do menu glownego" << std::endl;
            break;

            default:
            std::cout << "Niepoprawny wybor" << std::endl;
            break;
        }
    }    
}