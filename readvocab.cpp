#include "readvocab.h"
#include "shared.h"
#include <fstream>

void* readvocab(void* arg) {
    SharedData* data = (SharedData*) arg;
    std::ifstream vocabFile(data->fileName[0]);
    std::string word;
    while (vocabFile >> word) {
        data->vocabulary.insert(word);
    }
    vocabFile.close();
    return nullptr;
}
