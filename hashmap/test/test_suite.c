#include "hashmap.h"
#include "unity.h"

HashMap *map = NULL;

void setUp() {
    map = hashmap_create();
    hashmap_put(map, "test1", 111);
    hashmap_put(map, "test2", 222);
    hashmap_put(map, "test3", 333);
    hashmap_put(map, "test4", 444);
    hashmap_put(map, "test5", 555);
    hashmap_put(map, "test6", 666);
    hashmap_put(map, "test7", 777);
}

void tearDown() {
    hashmap_free(map);
}

void test_hashmap_create(void) {
    TEST_ASSERT_EQUAL_INT(7, map->nodes_count);
    TEST_ASSERT_EQUAL_INT(50, map->index_count);
}

void test_hashmap_put(void) {
    TEST_ASSERT_EQUAL_INT(7, map->nodes_count);

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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_hashmap_create);
    RUN_TEST(test_hashmap_put);
    RUN_TEST(test_hashmap_remove);
    return UNITY_END();
}
