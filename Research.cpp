#include <iostream>
#include <fstream>
#include "Research.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include "MaxHeapPriorityQueue.h"

const int SERIES_COUNT = 10;
const int COPIES_COUNT = 10;
const int BASE_SEED = 12345;
const int MAX_VALUE = 16777215;

const int SIZES_COUNT = 7;
const int TEST_SIZES[SIZES_COUNT] = {5000, 10000, 25000, 50000, 100000, 250000, 500000};

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

    for (int i = 0; i < SIZES_COUNT; i++){
        int currentSize = TEST_SIZES[i];

        for (int series = 0; series < SERIES_COUNT; series++) {
            int seed = BASE_SEED + series;

            measureMaxHeapInsert(file, currentSize, series, seed);
        }
    }

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

void Research::measureMaxHeapInsert(std::ofstream& file, int size, int series, int seed){
    QueueElement* data = new QueueElement[size];

    //generujemy dane przed pomiarem
    generateData(data, size, seed);

    //tworzymy kopie struktury przed pomiarem
    MaxHeapPriorityQueue* copies = new MaxHeapPriorityQueue[COPIES_COUNT];

    for (int copy = 0;copy < COPIES_COUNT; copy++) {
        for (int i = 0; i < size; i++) {
            copies[copy].insert(data[i].value, data[i].priority);
        }
    }

    //przygotowanie elementu dodawanaego
    int newValue = generateRandomNumber(0, MAX_VALUE);
    int newPriority = generateRandomNumber(0, 10 * size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        copies[copy].insert(newValue, newPriority);

    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    file << "MaxHeap,insert,"<<size<<","<<series<<","<<seed<<","<<COPIES_COUNT<<","<<totalTime<<","<<avgTime<<"\n";

    delete[] copies;
    delete[] data;
}