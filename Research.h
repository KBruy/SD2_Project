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
        void saveResult(std::ofstream& file, const char* structureName, const char* operationName, int size, int series, int seed, long long totalTime);

        void measureMaxHeapInsert(std::ofstream& file, int size, int series, int seed); //pomiar insert kopca
        void measureMaxHeapPeek(std::ofstream& file, int size, int series, int seed); // pomiar peek
        void measureMaxHeapExtractMax(std::ofstream& file, int size, int series, int seed); //pomiar extractMax
        void measureMaxHeapModifyKey(std::ofstream& file, int size, int series, int seed); //mierzy modifyKey
        void measureMaxHeapReturnSize(std::ofstream& file, int size, int series, int seed); //pomiar returnSize kopca

        UnsortedArrayPriorityQueue* prepareArrayCopies(QueueElement* data, int size); //przygotwanie danych
        void measureArrayInsert(std::ofstream& file, int size, int series, int seed); //pomiar insert dla tablic
        void measureArrayPeek(std::ofstream& file, int size, int series, int seed); //pomiar ppek
        void measureArrayExtractMax(std::ofstream& file, int size, int series, int seed);
        void measureArrayModifiKey(std::ofstream& file, int size, int series, int seed);
        void measureArrayReturnSize(std::ofstream& file, int size, int series, int seed);


    public:
        void runAll(); //uruchamia wszystkie badania i zapisuje wyniki do csv

};

#endif