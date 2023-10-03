// JEIKO SANTOS 824389729
// NATHNAEL ATLAW 822655984
#pragma once
#include <set>
#include <string>
#include <queue> 

extern std::queue<std::string> lineQueue;

struct SharedData {
    unsigned int numOfProgressMarks;
    unsigned int hashmarkInterval;
    unsigned int minNumOfVocabStringsContainedForPrinting;
    const char *fileName[2];
    unsigned long totalNumOfCharsInVocabFile;
    std::set<std::string> vocabulary;
};
