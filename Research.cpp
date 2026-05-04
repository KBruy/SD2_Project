#include <iostream>
#include <fstream>
#include "Research.h"
#include <cstdlib>
#include <ctime>

// const int SERIES_COUNT = 10;
// const int COPIES_COUNT = 10;
const int BASE_SEED = 12345;
const int MAX_VALUE = 16777215;

//const int SIZES_COUNT = 7;
//const int TEST_SIZES[SIZES_COUNT] = {5000, 10000, 25000, 50000, 100000, 250000, 500000};

int Research::generateRandomNumber(int minValue, int maxValue) {
    return minValue + rand() % (maxValue - minValue + 1); //zakres losowania 0 - 16777215
}

void Research::runAll() {
    std::ofstream file("results.csv");

    if (!file.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku results.csv" <<std::endl;
        return;
    }

    file << "structure,operation,size,series,seed,copies,total_time_ns,avg_time_ns\n";


    int testSize = 10;
int testSeed = BASE_SEED;

QueueElement* data = new QueueElement[testSize];

generateData(data, testSize, testSeed);

// tymczasowy test - zapisujemy kilka danych do pliku
for (int i = 0; i < testSize; i++) {
    file << "TEST,generated,"
         << testSize << ","
         << 0 << ","
         << testSeed << ","
         << 0 << ","
         << data[i].value << ","
         << data[i].priority
         << "\n";
}

delete[] data;

file.close();
    std::cout<<"Utworzono plik results.csv" <<std::endl;
}

void Research::generateData(QueueElement* data, int size, int seed){
    srand(seed);

    int maxPriority = 10 * size; //zakres kilkukrotnie wiekszy od rozmiaru struktury

    for (int i = 0; i < size; i++) {
        data[i].value = generateRandomNumber(0, MAX_VALUE);
        data[i].priority = generateRandomNumber(0, maxPriority);
    }
}