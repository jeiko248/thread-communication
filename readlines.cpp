#include "readlines.h"
#include "shared.h"
#include <fstream>

void* readlines(void* arg) {
    SharedData* data = (SharedData*) arg;
    std::ifstream testFile(data->fileName[1]);
    std::string line;
    while (std::getline(testFile, line)) {
        pthread_mutex_lock(&mutex);
        lineQueue.push(line);
        pthread_mutex_unlock(&mutex);
    }
    testFile.close();
    return nullptr;
}
