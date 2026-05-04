#include <iostream>
#include <fstream>
#include "Research.h"

void Research::runAll() {
    std::ofstream file("results.csv");

    if (!file.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku results.csv" <<std::endl;
        return;
    }

    file << "structure,operation,size,series,seed,copies,total_time_ns,avg_time_ns\n";

    file.close();
    std::cout<<"Utworzono plik results.csv" <<std::endl;
}