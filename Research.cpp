#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

#include "Research.h"
#include "MaxHeapPriorityQueue.h"
#include "UnsortedArrayPriorityQueue.h"

const int SERIES_COUNT = 10;
const int COPIES_COUNT = 100;
const int BASE_SEED = 12345;
const int MAX_VALUE = 16777215;

const int SIZES_COUNT = 8;
const int TEST_SIZES[SIZES_COUNT] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000};

int Research::generateRandomNumber(int minValue, int maxValue) {
    // losowanie z zakresu minValue - maxValue
    return minValue + rand() % (maxValue - minValue + 1);
}

void Research::runAll() {
    std::ofstream rawFile("results_raw.csv");
    std::ofstream summaryFile("results_summary.csv");

    if (!rawFile.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku results_raw.csv" << std::endl;
        return;
    }

    if (!summaryFile.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku results_summary.csv" << std::endl;
        rawFile.close();
        return;
    }

    rawFile << "structure,operation,size,series,seed,copies,total_time_ns,avg_time_ns\n";
    summaryFile << "structure,operation,size,series_count,copies,avg_time_ns\n";

    for (int i = 0; i < SIZES_COUNT; i++) {
        int currentSize = TEST_SIZES[i];

        double maxHeapInsertSum = 0.0;
        double maxHeapPeekSum = 0.0;
        double maxHeapExtractMaxSum = 0.0;
        double maxHeapModifyKeySum = 0.0;
        double maxHeapReturnSizeSum = 0.0;

        double arrayInsertSum = 0.0;
        double arrayPeekSum = 0.0;
        double arrayExtractMaxSum = 0.0;
        double arrayModifyKeySum = 0.0;
        double arrayReturnSizeSum = 0.0;

        for (int series = 0; series < SERIES_COUNT; series++) {
            int seed = BASE_SEED + series;

            maxHeapInsertSum += measureMaxHeapInsert(rawFile, currentSize, series, seed);
            maxHeapPeekSum += measureMaxHeapPeek(rawFile, currentSize, series, seed);
            maxHeapExtractMaxSum += measureMaxHeapExtractMax(rawFile, currentSize, series, seed);
            maxHeapModifyKeySum += measureMaxHeapModifyKey(rawFile, currentSize, series, seed);
            maxHeapReturnSizeSum += measureMaxHeapReturnSize(rawFile, currentSize, series, seed);

            arrayInsertSum += measureArrayInsert(rawFile, currentSize, series, seed);
            arrayPeekSum += measureArrayPeek(rawFile, currentSize, series, seed);
            arrayExtractMaxSum += measureArrayExtractMax(rawFile, currentSize, series, seed);
            arrayModifyKeySum += measureArrayModifiKey(rawFile, currentSize, series, seed);
            arrayReturnSizeSum += measureArrayReturnSize(rawFile, currentSize, series, seed);
        }

        saveSummaryResult(summaryFile, "MaxHeap", "insert", currentSize, maxHeapInsertSum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "MaxHeap", "peek", currentSize, maxHeapPeekSum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "MaxHeap", "extractMax", currentSize, maxHeapExtractMaxSum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "MaxHeap", "modifyKey", currentSize, maxHeapModifyKeySum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "MaxHeap", "returnSize", currentSize, maxHeapReturnSizeSum / SERIES_COUNT);

        saveSummaryResult(summaryFile, "UnsortedArray", "insert", currentSize, arrayInsertSum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "UnsortedArray", "peek", currentSize, arrayPeekSum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "UnsortedArray", "extractMax", currentSize, arrayExtractMaxSum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "UnsortedArray", "modifyKey", currentSize, arrayModifyKeySum / SERIES_COUNT);
        saveSummaryResult(summaryFile, "UnsortedArray", "returnSize", currentSize, arrayReturnSizeSum / SERIES_COUNT);
    }

    rawFile.close();
    summaryFile.close();

    std::cout << "Zakonczono badania." << std::endl;
    std::cout << "Wyniki szczegolowe zapisano do results_raw.csv" << std::endl;
    std::cout << "Srednie zapisano do results_summary.csv" << std::endl;
}

void Research::generateData(QueueElement* data, int size, int seed) {
    srand(seed);

    // zakres priorytetow jest kilkukrotnie wiekszy od rozmiaru struktury
    int maxPriority = 10 * size;

    for (int i = 0; i < size; i++) {
        data[i].value = generateRandomNumber(0, MAX_VALUE);
        data[i].priority = generateRandomNumber(0, maxPriority);
    }
}

MaxHeapPriorityQueue* Research::prepareMaxHeapCopies(QueueElement* data, int size) {
    MaxHeapPriorityQueue* copies = new MaxHeapPriorityQueue[COPIES_COUNT];

    // kazda kopia dostaje ten sam zestaw danych
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        for (int i = 0; i < size; i++) {
            copies[copy].insert(data[i].value, data[i].priority);
        }
    }

    return copies;
}

UnsortedArrayPriorityQueue* Research::prepareArrayCopies(QueueElement* data, int size) {
    UnsortedArrayPriorityQueue* copies = new UnsortedArrayPriorityQueue[COPIES_COUNT];

    // kazda kopia dostaje ten sam zestaw danych
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        for (int i = 0; i < size; i++) {
            copies[copy].insert(data[i].value, data[i].priority);
        }
    }

    return copies;
}

void Research::saveRawResult(std::ofstream& file, const char* structureName, const char* operationName,
                             int size, int series, int seed, long long totalTime, double avgTime) {
    file << structureName << ","
         << operationName << ","
         << size << ","
         << series << ","
         << seed << ","
         << COPIES_COUNT << ","
         << totalTime << ","
         << avgTime
         << "\n";
}

void Research::saveSummaryResult(std::ofstream& file, const char* structureName, const char* operationName,
                                 int size, double avgTime) {
    file << structureName << ","
         << operationName << ","
         << size << ","
         << SERIES_COUNT << ","
         << COPIES_COUNT << ","
         << avgTime
         << "\n";
}

// ==========================================================================
// POMIARY - KOPIEC MAX
// ==========================================================================

double Research::measureMaxHeapInsert(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

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
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "MaxHeap", "insert", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureMaxHeapPeek(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje peek na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].peek();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result.priority == -2) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "MaxHeap", "peek", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureMaxHeapExtractMax(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje extractMax na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].extractMax();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result.priority == -2) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "MaxHeap", "extractMax", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureMaxHeapModifyKey(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    // wybieramy wartosc, ktora na pewno jest w danych
    int valueToModify = data[size / 2].value;

    // nowy priorytet zgodny z zalozeniami projektu
    int newPriority = generateRandomNumber(0, 10 * size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje modifyKey na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        bool changed = copies[copy].modifyKey(valueToModify, newPriority);

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (!changed) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "MaxHeap", "modifyKey", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureMaxHeapReturnSize(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    MaxHeapPriorityQueue* copies = prepareMaxHeapCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje returnSize na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        int result = copies[copy].returnSize();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result == -1) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "MaxHeap", "returnSize", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

// ==========================================================================
// POMIARY - TABLICA NIEPOSORTOWANA
// ==========================================================================

double Research::measureArrayInsert(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

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
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "UnsortedArray", "insert", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureArrayPeek(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje peek na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].peek();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result.priority == -2) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "UnsortedArray", "peek", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureArrayExtractMax(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje extractMax na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        QueueElement result = copies[copy].extractMax();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result.priority == -2) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "UnsortedArray", "extractMax", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureArrayModifiKey(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    // wybieramy wartosc, ktora na pewno jest w danych
    int valueToModify = data[size / 2].value;

    // nowy priorytet zgodny z zalozeniami projektu
    int newPriority = generateRandomNumber(0, 10 * size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje modifyKey na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        bool changed = copies[copy].modifyKey(valueToModify, newPriority);

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (!changed) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "UnsortedArray", "modifyKey", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}

double Research::measureArrayReturnSize(std::ofstream& file, int size, int series, int seed) {
    QueueElement* data = new QueueElement[size];

    generateData(data, size, seed);

    UnsortedArrayPriorityQueue* copies = prepareArrayCopies(data, size);

    auto start = std::chrono::high_resolution_clock::now();

    // mierzymy tylko sama operacje returnSize na gotowych kopiach
    for (int copy = 0; copy < COPIES_COUNT; copy++) {
        int result = copies[copy].returnSize();

        // uzycie wyniku, zeby kompilator nie pominal operacji
        if (result == -1) {
            std::cout << "";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    long long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avgTime = static_cast<double>(totalTime) / COPIES_COUNT;

    saveRawResult(file, "UnsortedArray", "returnSize", size, series, seed, totalTime, avgTime);

    delete[] copies;
    delete[] data;

    return avgTime;
}