#include "readlines.h"
#include "shared.h"
#include <fstream>
#include <iostream>
#include <queue>

std::queue<std::string> lineQueue;

void* readlines(void* sharedData) {
    SharedData* data = static_cast<SharedData*>(sharedData);
    std::ifstream testFile(data->fileName[1]);
    if (!testFile.is_open()) {
        std::cerr << "Error opening test file." << std::endl;
        return nullptr;
    }
    std::string line;
    while (std::getline(testFile, line)) {
        lineQueue.push(line);
    }
    testFile.close();
    return nullptr;
}
