#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <set>

#include "shared.h"
#include "readvocab.h"
#include "readlines.h"
#include "countvocabstrings.h"

#define MIN_NUMOF_MARKS 10
#define DEFAULT_HASHMARKINTERVAL 10
#define DEFAULT_MINNUM_OFVOCABSTRINGS_CONTAINED 0
#define NUMOFFILES 2

typedef struct {
    unsigned int numOfProgressMarks;
    unsigned int hashmarkInterval;
    unsigned int minNumOfVocabStringsContainedForPrinting;
    const char *fileName[NUMOFFILES];
    unsigned long totalNumOfCharsInVocabFile;
    std::set<std::string> vocabulary;
} SharedData;

std::queue<std::string> lineQueue;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[]) {
    SharedData data;
    int opt;

    while ((opt = getopt(argc, argv, "p:m:v:")) != -1) {
        switch (opt) {
            case 'p':
                data.numOfProgressMarks = atoi(optarg);
                break;
            case 'm':
                data.hashmarkInterval = atoi(optarg);
                break;
            case 'v':
                data.minNumOfVocabStringsContainedForPrinting = atoi(optarg);
                break;
            default:
                std::cerr << "Invalid arguments provided." << std::endl;
                return 1;
        }
    }

    if (argc - optind != 2) {
        std::cerr << "Please provide the paths for vocabulary and test files." << std::endl;
        return 1;
    }
    data.fileName[0] = argv[optind];
    data.fileName[1] = argv[optind + 1];

    pthread_t readvocabThread, readlinesThread, countvocabstringsThread;

    pthread_create(&readvocabThread, nullptr, readvocab, &data);
    pthread_create(&readlinesThread, nullptr, readlines, &data);
    pthread_create(&countvocabstringsThread, nullptr, countvocabstrings, &data);

    pthread_join(readvocabThread, nullptr);
    pthread_join(readlinesThread, nullptr);
    pthread_join(countvocabstringsThread, nullptr);

    return 0;
}
