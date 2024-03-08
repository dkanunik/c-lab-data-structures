#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"
#include "unity.h"

Heap *heap = NULL;
int MAX_DATA_SIZE = 100;
int MAX_HEAP_SIZE = 100;
int LAST_NUMBER = 0;
char NUM_SEPARATOR = ' ';

int generate_test_data(char *file_name, int count, int min, int max) {
    srand(time(NULL));

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

void heap_print(int *arr, int n, int i, int space) {
    if (i >= n)
        return;

    space += 10;

    heap_print(arr, n, 2 * i + 2, space);

    for (int j = 5; j < space; j++)
        printf(" ");

    printf("%d\n", arr[i]);

    heap_print(arr, n, 2 * i + 1, space);
}

void heap_to_array() {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
}

void setUp() {
    heap = heap_create(MAX_HEAP_SIZE);

    //generate_test_data("test1.txt", 50, 1, 100);

    int *data = get_test_data("test1.txt");

    while (*data != 0) {
        int element = *(data++);
        printf("\n----------------------------------------------------\n");
        printf("[%d] --> ", element);
        heap_to_array();
        printf("\n----------------------------------------------------\n");
        heap_insert(heap, element);
        getchar();
        heap_print(heap->array, heap->size, 0, 0);
    }

}

void tearDown() {
    heap_free(heap);
}

void test_heap_create(void) {
    //heap_print(heap->array, heap->size, 0, 0);
    //heap_to_array();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_heap_create);
    return UNITY_END();
}
