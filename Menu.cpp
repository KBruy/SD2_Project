#include <iostream>
#include "Menu.h"

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
                std::cout << "Wybrano kopiec binarny MAX" << std::endl;
                break;
            case 2:
                std::cout << "Wybrano tablice nieposortowana" << std::endl;
                break;
            case 3:
                std::cout << "Badania" << std::endl;
                break;
            case 0:
                std::cout << "Koniec programu" << std::endl;
                break;

            default:
                std::cout<< "Niepoprawny wybor" << std::endl;

        }
    }
}