// JEIKO SANTOS 824389729
// NATHNAEL ATLAW 822655984
#include "readvocab.h"
#include "shared.h"
#include <fstream>
#include <iostream>
#include <pthread.h>

extern pthread_mutex_t printMutex;  // Ensure printMutex is available

void* readvocab(void* arg) {
    SharedData* data = (SharedData*) arg;
    std::ifstream vocabFile(data->fileName[0]);
    if (!vocabFile.is_open()) {
        pthread_mutex_lock(&printMutex);
        std::cerr << "Error opening vocabulary file." << std::endl;
        pthread_mutex_unlock(&printMutex);
        return nullptr;
    }

    std::string word;
    unsigned int processedWords = 0;
    while (vocabFile >> word) {
        data->vocabulary.insert(word);
        processedWords++;

        // Update progress bar
        if (processedWords % data->hashmarkInterval == 0) {
            pthread_mutex_lock(&printMutex);
            std::cout << "#";
            std::cout.flush();
            pthread_mutex_unlock(&printMutex);
        }
    }
    vocabFile.close();

    // Print newline and total word count after progress bar
    pthread_mutex_lock(&printMutex);
    std::cout << std::endl << processedWords << std::endl;
    pthread_mutex_unlock(&printMutex);

    return nullptr;
}
