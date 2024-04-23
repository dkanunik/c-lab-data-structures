#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "test_data_utils.h"

int LAST_NUMBER = 0;
char NUM_SEPARATOR = ' ';
int MAX_DATA_SIZE = 100;

int generate_test_data(char *file_name, int count, int min, int max) {
    srand((unsigned int)time(NULL));

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        int random_number = rand() % (max - min + 1) + min;
        fprintf(file, "%d%c", random_number, NUM_SEPARATOR);
    }

    fprintf(file, "%d", LAST_NUMBER);

    fclose(file);

    printf("Random numbers saved to file '%s'.\n", file_name);

    return 0;
}

int *get_test_data(const char *file_name) {
    FILE *file = fopen(file_name, "r");
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
