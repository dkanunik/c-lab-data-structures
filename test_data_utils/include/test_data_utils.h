#ifndef TEST_DATA_UTILS_H
#define TEST_DATA_UTILS_H

#define LAST_NUMBER         -1
#define NUM_SEPARATOR       ' '
#define MAX_DATA_SIZE       100

int generate_test_data(char *file_name, int count, int min, int max);

int *get_test_data(const char *file_name);

#endif //TEST_DATA_UTILS_H
