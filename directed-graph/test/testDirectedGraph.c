#include <stdlib.h>
#include "unity.h"
#include "directedGraph.h"

DirectedGraph graph = {NULL};

void tearDown() {
    freeGraph(&graph);
}

void setUp() {
    addVertex(&graph, 1);
    addVertex(&graph, 2);
    addVertex(&graph, 3);

    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 1);
    addEdge(&graph, 2, 3);
}

void testAddVertex() {
    int counter = 0;
    Vertex *v = graph.vertices;
    while (v != NULL) {
        counter++;
        v = v->next;
    }
    TEST_ASSERT_EQUAL_INT(3, counter);
}

void testAddEdge() {
    TEST_ASSERT_EQUAL_INT(3, graph.vertices[0].next->edges->toVertex->id);
}

void testContainsVertex() {
    TEST_ASSERT_TRUE(containsVertex(&graph, 1));
    TEST_ASSERT_FALSE(containsVertex(&graph, 111));
}

void testContainsEdge() {
    TEST_ASSERT_TRUE(containsEdge(&graph, 1, 2));
    TEST_ASSERT_TRUE(containsEdge(&graph, 2, 1));
    TEST_ASSERT_TRUE(containsEdge(&graph, 2, 3));
    TEST_ASSERT_FALSE(containsEdge(&graph, 3, 2));
    TEST_ASSERT_FALSE(containsEdge(&graph, 13, 12));
    TEST_ASSERT_FALSE(containsEdge(&graph, 1, 1));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testAddVertex);
    RUN_TEST(testAddEdge);
    RUN_TEST(testContainsVertex);
    RUN_TEST(testContainsEdge);
    return UNITY_END();
}
