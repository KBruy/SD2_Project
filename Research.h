#ifndef RESEARCH_H
#define RESEARCH_H

#include "QueueElement.h"
#include <fstream>
#include "MaxHeapPriorityQueue.h"
#include "UnsortedArrayPriorityQueue.h"

class Research {
    private:
        int generateRandomNumber(int minValue, int maxValue);
        
        void generateData(QueueElement* data, int size, int seed); //przygotowywuje dane do badan
        MaxHeapPriorityQueue* prepareMaxHeapCopies(QueueElement* data, int size); //tworzy kopie kopca do pomiarow
        void saveRawResult(std::ofstream& file, const char* structureName, const char* operationName, int size, int series, int seed, long long totalTime, double avgTime);
        void saveSummaryResult(std::ofstream& file, const char* structureName, const char* operationName, int size, double avgTime);

        double measureMaxHeapInsert(std::ofstream& file, int size, int series, int seed); //pomiar insert kopca
        double measureMaxHeapPeek(std::ofstream& file, int size, int series, int seed); // pomiar peek
        double measureMaxHeapExtractMax(std::ofstream& file, int size, int series, int seed); //pomiar extractMax
        double measureMaxHeapModifyKey(std::ofstream& file, int size, int series, int seed); //mierzy modifyKey
        double measureMaxHeapReturnSize(std::ofstream& file, int size, int series, int seed); //pomiar returnSize kopca

        UnsortedArrayPriorityQueue* prepareArrayCopies(QueueElement* data, int size); //przygotwanie danych
        double measureArrayInsert(std::ofstream& file, int size, int series, int seed); //pomiar insert dla tablic
        double measureArrayPeek(std::ofstream& file, int size, int series, int seed); //pomiar ppek
        double measureArrayExtractMax(std::ofstream& file, int size, int series, int seed);
        double measureArrayModifiKey(std::ofstream& file, int size, int series, int seed);
        double measureArrayReturnSize(std::ofstream& file, int size, int series, int seed);


    public:
        void runAll(); //uruchamia wszystkie badania i zapisuje wyniki do csv

};

#endif