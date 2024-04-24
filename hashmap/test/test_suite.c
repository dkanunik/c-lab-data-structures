#include <string.h>
#include "hashmap.h"
#include "unity/unity.h"

HashMap *map = NULL;

void prefill_data() {
    hashmap_put(map, "test1", 111);
    hashmap_put(map, "test2", 222);
    hashmap_put(map, "test3", 333);
    hashmap_put(map, "test4", 444);
    hashmap_put(map, "test5", 555);
    hashmap_put(map, "test6", 666);
    hashmap_put(map, "test7", 777);
}

void setUp() {
    map = hashmap_create();
}

void tearDown() {
    hashmap_free(map);
}

void test_hashmap_create(void) {
    prefill_data();
    TEST_ASSERT_EQUAL_INT(7, map->nodes_count);
    TEST_ASSERT_EQUAL_INT(50, map->index_count);
}

void test_hashmap_put(void) {
    prefill_data();

    int *result1 = hashmap_get(map, "test1");
    TEST_ASSERT_EQUAL_INT(1, result1[0]);
    TEST_ASSERT_EQUAL_INT(111, result1[1]);

    int *result2 = hashmap_get(map, "test7");
    TEST_ASSERT_EQUAL_INT(1, result2[0]);
    TEST_ASSERT_EQUAL_INT(777, result2[1]);

    int *result3 = hashmap_get(map, "test-1");
    TEST_ASSERT_EQUAL_INT(0, result3[0]);
    TEST_ASSERT_EQUAL_INT(0, result3[1]);
}

void test_hashmap_remove(void) {
    prefill_data();

    int remove_result = hashmap_remove(map, "test2");
    TEST_ASSERT_EQUAL_INT(1, remove_result);

    int *result1 = hashmap_get(map, "test1");
    TEST_ASSERT_EQUAL_INT(1, result1[0]);
    TEST_ASSERT_EQUAL_INT(111, result1[1]);

    int *result2 = hashmap_get(map, "test2");
    TEST_ASSERT_EQUAL_INT(0, result2[0]);
    TEST_ASSERT_EQUAL_INT(0, result2[1]);

    int *result3 = hashmap_get(map, "test3");
    TEST_ASSERT_EQUAL_INT(1, result3[0]);
    TEST_ASSERT_EQUAL_INT(333, result3[1]);
}

void test_hashmap_size(void) {
    TEST_ASSERT_EQUAL_INT(0, hashmap_size(map));

    prefill_data();

    TEST_ASSERT_EQUAL_INT(7, hashmap_size(map));
}


void test_hashmap_is_empty(void) {
    TEST_ASSERT_TRUE(hashmap_is_empty(map));

    prefill_data();

    TEST_ASSERT_FALSE(hashmap_is_empty(map));
}

void test_hashmap_contains_key(void) {
    prefill_data();

    TEST_ASSERT_TRUE(hashmap_contains_key(map, "test1"));
    TEST_ASSERT_FALSE(hashmap_contains_key(map, "test10"));
}

void test_hashmap_clean(void) {
    prefill_data();

    TEST_ASSERT_EQUAL_INT(7, hashmap_size(map));

    hashmap_clear(map);

    TEST_ASSERT_EQUAL_INT(0, hashmap_size(map));

    TEST_ASSERT_FALSE(hashmap_contains_key(map, "test1"));
    TEST_ASSERT_FALSE(hashmap_contains_key(map, "test7"));
}

void test_hashmap_keys(void) {
    prefill_data();

    char *expected_keys[] = {"test1",
                             "test2",
                             "test3",
                             "test4",
                             "test5",
                             "test6",
                             "test7"};

    char *unexpected_keys[] = {"test8",
                            "test9",
                            "test10"};

    void *actual_keys = hashmap_keys(map, ",");

    for (size_t i = 0; i < 7; i++) {
        char *result = strstr(actual_keys, expected_keys[i]);
        TEST_ASSERT_NOT_NULL(result);
    }

    for (size_t i = 0; i < 3; i++) {
        char *result = strstr(actual_keys, unexpected_keys[i]);
        TEST_ASSERT_NULL(result);
    }


}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_hashmap_create);
    RUN_TEST(test_hashmap_size);
    RUN_TEST(test_hashmap_is_empty);
    RUN_TEST(test_hashmap_keys);
    RUN_TEST(test_hashmap_put);
    RUN_TEST(test_hashmap_remove);
    RUN_TEST(test_hashmap_contains_key);
    RUN_TEST(test_hashmap_clean);
    return UNITY_END();
}
