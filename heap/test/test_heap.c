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
int HEAP_DEBUG = 3;
char HEAP_TEST_DATA_FILE[] = "test1.txt";

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

void tearDown() {
    heap_free(heap);
}

void setUp() {
    heap = heap_create(MAX_HEAP_SIZE);

    int *data = get_test_data(HEAP_TEST_DATA_FILE);

    while (*data != 0) {
        int element = *(data++);

        if (HEAP_DEBUG == 1) {
            printf("\n----------------------------------------------------\n");
            printf("[%d] --> ", element);
            heap_print_as_row(heap);
            printf("\n----------------------------------------------------\n");
        }

        heap_insert(heap, element);

        if (HEAP_DEBUG == 1) {
            getchar();
            heap_print_as_tree(heap, 0, 0);
        }
    }
}

void test_heap_peek(void) {
    int result = heap_peek(heap);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_heap_extract_by_index(void) {
    int before_size = heap->size;

    int result = heap_extract_by_index(heap, 2);

    TEST_ASSERT_EQUAL_INT(6, result);
    TEST_ASSERT_EQUAL_INT(before_size - 1, heap->size);
    if (HEAP_DEBUG == 3) {
        heap_print_as_tree(heap, 0, 0);
    }
}


void test_heap_extract_min(void) {
    int before_size = heap->size;
    int result = heap_extract_min(heap);
    TEST_ASSERT_EQUAL_INT(1, result);
    TEST_ASSERT_EQUAL_INT(before_size - 1, heap->size);
    TEST_ASSERT_EQUAL_INT(2, heap_peek(heap));
    if (HEAP_DEBUG == 2) {
        heap_print_as_tree(heap, 0, 0);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_heap_peek);
    RUN_TEST(test_heap_extract_min);
    RUN_TEST(test_heap_extract_by_index);
    return UNITY_END();
}
