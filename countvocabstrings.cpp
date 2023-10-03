#include "countvocabstrings.h"
#include "shared.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <pthread.h>
#include <queue>

extern std::queue<std::string> lineQueue;
extern pthread_mutex_t mutex;

void* countvocabstrings(void* arg) {
    SharedData* data = (SharedData*) arg;
    std::ofstream outputFile("countNumOfContainedVocab.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return nullptr;
    }

    unsigned int lineNumber = 0;  

    while (true) {
        pthread_mutex_lock(&mutex);
        if (lineQueue.empty()) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        std::string line = lineQueue.front();
        lineQueue.pop();
        pthread_mutex_unlock(&mutex);

        std::istringstream iss(line);
        std::string word;
        unsigned int count = 0;  
        while (iss >> word) {
            if (data->vocabulary.find(word) != data->vocabulary.end()) {
                count++;
            }
        }
        lineNumber++;  
        if (count >= data->minNumOfVocabStringsContainedForPrinting) {
            outputFile << lineNumber << "\t" << count << std::endl;  
        }
    }
    outputFile.close();
    return nullptr;
}
