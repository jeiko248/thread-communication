#pragma once
#include <set>
#include <string>

struct SharedData {
    unsigned int numOfProgressMarks;
    unsigned int hashmarkInterval;
    unsigned int minNumOfVocabStringsContainedForPrinting;
    const char *fileName[2];
    unsigned long totalNumOfCharsInVocabFile;
    std::set<std::string> vocabulary;
};
