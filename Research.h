#ifndef RESEARCH_H
#define RESEARCH_H

#include "QueueElement.h"

class Research {
    private:
        int generateRandomNumber(int minValue, int maxValue);
        
        void generateData(QueueElement* data, int size, int seed); //przygotowywuje dane do badan

        void measureMaxHeapInsert(std::ofstream& file, int size, int series, int seed); //pomiar insert kopca
    public:
        void runAll(); //uruchamia wszystkie badania i zapisuje wyniki do csv

};

#endif