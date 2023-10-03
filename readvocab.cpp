#include "readvocab.h"
#include "shared.h"
#include <fstream>
#include <iostream>

void* readvocab(void* sharedData) {
    SharedData* data = static_cast<SharedData*>(sharedData);
    std::ifstream vocabFile(data->fileName[0]);
    if (!vocabFile.is_open()) {
        std::cerr << "Error opening vocabulary file." << std::endl;
        return nullptr;
    }
    std::string word;
    while (vocabFile >> word) {
        data->vocabulary.insert(word);
    }
    vocabFile.close();
    return nullptr;
}
