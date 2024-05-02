#ifndef TEST_DATA_UTILS_H
#define TEST_DATA_UTILS_H

#include <stdbool.h>

#define LAST_NUMBER             -1
#define NUM_SEPARATOR           ' '
#define MAX_DATA_SIZE           100
#define DEBUG                   false
#define TEST_DATA_FILE_PATH     "/tmp/"

int generateTestData(char *fileName, int min, int max);

int *getTestData(const char *fileName);

char* generateRandomString(size_t strLength);

void removeTestDataFile(char *fileName);

void printSortData(const int *testData, char *message);

#endif //TEST_DATA_UTILS_H
