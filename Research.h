#ifndef RESEARCH_H
#define RESEARCH_H

#include "QueueElement.h"

class Research {
    private:
        int generateRandomNumber(int minValue, int maxValue);
        
        void generateData(QueueElement* data, int size, int seed); //przygotowywuje dane do badan
    public:
        void runAll(); //uruchamia wszystkie badania i zapisuje wyniki do csv

};

#endif