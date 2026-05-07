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
            measureMaxHeapPeek(file, currentSize, series, seed);
            measureMaxHeapExtractMax(file, currentSize, series, seed);
            measureMaxHeapModifyKey(file, currentSize, series, seed);
            measureMaxHeapReturnSize(file, currentSize, series, seed);

            measureArrayInsert(file, currentSize, series, seed);
            measureArrayPeek(file, currentSize, series, seed);
            measureArrayExtractMax(file, currentSize, series, seed);
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

MaxHeapPriorityQueue* Research::prepareMaxHeapCopies(QueueElement* data, int size) {
    MaxHeapPriorityQueue* copies = new MaxHeapPriorityQueue[COPIES_COUNT];

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        for (int i = 0; i < size; i++) {
            copies[copy].insert(data[i].value, data[i].priority);
        }
    }
    
    return copies;
}

void Research::saveResult(std::ofstream& file, const char* structureName, const char* operationName, int size, int series, int seed, long long totalTime){
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    file << structureName<<","<<operationName<<","<<size<<","<<series<<","<<seed<<","<<COPIES_COUNT<<","<<totalTime<<","<<avgTime<<"\n";
}

//==========================================================================

void Research::measureMaxHeapInsert(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    // generujemy dane przed pomiarem
    generateData(data, size, seed);

    // przygotowujemy kopie struktury przed pomiarem
    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    // przygotowujemy element dodawany w badanej operacji
    int newValue = generateRandomNumber(0, MAX_VALUE);
    int newPriority = generateRandomNumber(0, 10 * size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje insert na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        copies[copy].insert(newValue, newPriority);
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    saveResult(file, "MaxHeap", "insert", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}

void Research::measureMaxHeapPeek(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    // generujemy dane przed pomiarem
    generateData(data, size, seed);

    // przygotowujemy kopie struktury przed pomiarem
    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].peek();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result.priority == -2) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    saveResult(file, "MaxHeap", "peek", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}

void Research::measureMaxHeapExtractMax(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    //generujemy dane przed pomiarem
    generateData(data, size, seed);

    // przygotowywujmy kopie struktury przed pomiarem
    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].extractMax();

        //uzycie wyniku, zeby kompilator nie pominal operacji
        if (result.priority == -2) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    saveResult(file, "MaxHeap", "extractMax", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}

void Research::measureMaxHeapModifyKey(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);
    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    //wybieramy wartosc ktora na pewo jest w danych
    int valueToModify = data[size / 2].value;

    //losowanie nowego priorytetu
    int newPriority = generateRandomNumber(0, 10 * size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        bool changed = copies[copy].modifyKey(valueToModify, newPriority);

        if (!changed) {std::cout << "";}
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    saveResult(file, "MaxHeap", "modifyKey", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;

}

void Research::measureMaxHeapReturnSize(std::ofstream& file, int size, int series, int seed){
    QueueElement* data = new QueueElement[size];

    // generuemy dane przed pomiarem
    generateData(data, size, seed);

    // przygototwanie kopii strkutry przed pomiarem

    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje returnSize na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        int result = copies[copy].returnSize();

        // uzycie wyniku zeby kompilator nie pomial operacji
        if (result == -1) {
            std::cout<<"";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    saveResult(file, "MaxHeap", "returnSize", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}

UnsortedArrayPriorityQueue* Research::prepareArrayCopies(QueueElement* data, int size) {
    //tworzenie dynamicznej tablicy kopii kolejki na tablicy nieposrtowanej

    UnsortedArrayPriorityQueue* copies = new UnsortedArrayPriorityQueue[COPIES_COUNT];

    // kazda kopia dostaje ten sam zestaw danych
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        for (int i = 0; i < size; i++) {
            copies[copy].insert(data[i].value, data[i].priority);
        }
    }

    return copies;
}

void Research::measureArrayInsert(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    //generujemy dane przed pomiarem 
    generateData(data, size, seed);

    //przygotowanie kopii
    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    // przygotowujemy element dodawany w badanej operacji

    int newValue = generateRandomNumber(0, MAX_VALUE);
    int newPriority = generateRandomNumber(0, 10*size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        copies[copy].insert(newValue, newPriority);
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    saveResult(file, "UnsortedArray","insert",size, series, seed, totalTime);

    delete[] copies;
    delete[] data;

}

void Research::measureArrayPeek(std::ofstream& file, int size, int series, int seed){
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].peek();

        if (result.priority == -2) {
            std::cout<<"";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    saveResult(file, "UnsortedArray", "peek", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}

void Research::measureArrayExtractMax(std::ofstream& file, int size, int series, int seed) {

    QueueElement* data = new QueueElement[size];
    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].extractMax();

        if (result.priority == -2) {
            std::cout<<"";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    saveResult(file, "UnsortedArray", "extractMax", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}

void Research::measureArrayModifiKey(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    int valueToModify = data[size / 2].value;

    int newPriority = generateRandomNumber(0, 10 * size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        bool changed = copies[copy].modifyKey (valueToModify, newPriority);

        if (!changed) {
            std::cout<<"";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    saveResult(file, "UnsortedArray", "modifyKey", size, series, seed, totalTime);

    delete[] copies;
    delete[] data;
}