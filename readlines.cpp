// JEIKO SANTOS 824389729
// NATHNAEL ATLAW 822655984
#include "readlines.h"
#include "shared.h"
#include <fstream>
#include <iostream>
#include <queue>

void* readlines(void* sharedData) {
    SharedData* data = static_cast<SharedData*>(sharedData);
    std::ifstream testFile(data->fileName[1]);
    if (!testFile.is_open()) {
        std::cerr << "Display Unable to open <<missing_file.txt>>" << std::endl;
        return nullptr;
    }
    std::string line;
    while (std::getline(testFile, line)) {
        lineQueue.push(line);
    }
    testFile.close();
    return nullptr;
}
