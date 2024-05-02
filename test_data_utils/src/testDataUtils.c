#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "testDataUtils.h"

char *generateRandomString(size_t strLength) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand((unsigned int) time(NULL));

    char *string = malloc(strLength + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (size_t i = 0; i < strLength; i++) {
        string[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    return string;
}

void removeTestDataFile(char *fileName) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", TEST_DATA_FILE_PATH, fileName);
    remove(fullPath);
    if (DEBUG) {
        printf("\nDelete file '%s'\n", fullPath);
    }
}

int generateTestData(char *fileName, int min, int max) {
    srand((unsigned int) time(NULL));

    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", TEST_DATA_FILE_PATH, fileName);

    FILE *file = fopen(fullPath, "w");
    if (file == NULL) {
        fprintf(stderr, "Test Data Utils: Error opening file\n");
        return 1;
    }

    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        int randomNumber = rand() % (max - min + 1) + min;
        fprintf(file, "%d%c", randomNumber, NUM_SEPARATOR);
    }

    fprintf(file, "%d", LAST_NUMBER);

    fclose(file);

    if (DEBUG) {
        printf("\nRandom numbers saved to file '%s'\n", fullPath);
    }

    return 0;
}

int *getTestData(const char *fileName) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", TEST_DATA_FILE_PATH, fileName);
    FILE *file = fopen(fullPath, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int *data = (int *) malloc(MAX_DATA_SIZE
                               * (sizeof(int) + sizeof(NUM_SEPARATOR))
                               + sizeof(LAST_NUMBER));

    int count = 0;
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        data[count++] = num;
    }

    fclose(file);

    return data;
}

void printSortData(const int *testData, char *message) {
    printf("\n %s ", message);
    for (int i = 0; testData[i] != LAST_NUMBER; i++) {
        printf("%d ", testData[i]);
    }
    printf("\n");
}

void test() {
    char *testDataFileName = generateRandomString(5);
    generateTestData(testDataFileName, 1, 500);
    int *testData = getTestData(testDataFileName);
    printSortData(testData, ">>>");
    removeTestDataFile(testDataFileName);
}
