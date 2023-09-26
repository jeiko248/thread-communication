#include "countvocabstrings.h"
#include "shared.h"
#include <sstream>

void* countvocabstrings(void* arg) {
    SharedData* data = (SharedData*) arg;
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
        int count = 0;
        while (iss >> word) {
            if (data->vocabulary.find(word) != data->vocabulary.end()) {
                count++;
            }
        }
        if (count >= data->minNumOfVocabStringsContainedForPrinting) {
            std::cout << line << std::endl;
        }
    }
    return nullptr;
}
