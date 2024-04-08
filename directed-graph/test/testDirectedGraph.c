#include <stdlib.h>
#include "unity.h"
#include "directedGraph.h"
#include "edge.h"

bool DEBUG = false;

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
        v = v->previous;
    }
    TEST_ASSERT_EQUAL_INT(3, counter);
}

void testAddEdge() {
    TEST_ASSERT_EQUAL_INT(3, graph.vertices[0].previous->edges->toVertex->id);
}

void testContainsVertex() {
    TEST_ASSERT_TRUE(containsVertex(&graph, 1));
    TEST_ASSERT_FALSE(containsVertex(&graph, 111));
}

void testGetVertices() {
    size_t count = 0;
    int const *vertices = getVerticesData(&graph);
    while (vertices[count] != -1) {
        ++count;
    }

    TEST_ASSERT_EQUAL_INT(3, count);
}

void testContainsEdge() {
    TEST_ASSERT_TRUE(containsEdge(&graph, 1, 2));
    TEST_ASSERT_TRUE(containsEdge(&graph, 2, 1));
    TEST_ASSERT_TRUE(containsEdge(&graph, 2, 3));
    TEST_ASSERT_FALSE(containsEdge(&graph, 3, 2));
    TEST_ASSERT_FALSE(containsEdge(&graph, 13, 12));
    TEST_ASSERT_FALSE(containsEdge(&graph, 1, 1));
}

void testGetEdgesData() {
    EdgeData **edges = getEdgeData(&graph);
    TEST_ASSERT_EQUAL_INT(2, edges[0]->fromVertex);
    TEST_ASSERT_EQUAL_INT(3, edges[0]->toVertex);
    TEST_ASSERT_EQUAL_INT(2, edges[1]->fromVertex);
    TEST_ASSERT_EQUAL_INT(1, edges[1]->toVertex);
    TEST_ASSERT_EQUAL_INT(1, edges[2]->fromVertex);
    TEST_ASSERT_EQUAL_INT(2, edges[2]->toVertex);
    size_t count = 0;

    while (DEBUG) {
        EdgeData const *edgeData = edges[count++];
        printf("from [%d] to [%d]\n", edgeData->fromVertex, edgeData->toVertex);

        if (edgeData->index + 1 == edgeData->size) {
            break;
        }
    }
}

void testRemoveEdge() {
    const int FROM_ID = 2;
    const int TO_ID = 3;
    bool isEdgeFound = false;

    bool result = removeEdge(&graph, FROM_ID, TO_ID);
    TEST_ASSERT_TRUE(result);

    Vertex *currentVertex = &graph.vertices[0];
    while (currentVertex != NULL) {
        if (currentVertex->id != FROM_ID) {
            currentVertex = currentVertex->previous;
            continue;
        }

        Edge* currentEdge = currentVertex->edges;
        while (currentEdge != NULL) {
            if (currentEdge->toVertex->id == TO_ID) {
                isEdgeFound = true;
            }
            currentEdge = currentEdge->next;
        }

        break;
    }

    TEST_ASSERT_FALSE(isEdgeFound);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testAddVertex);
    RUN_TEST(testAddEdge);
    RUN_TEST(testContainsVertex);
    RUN_TEST(testContainsEdge);
    RUN_TEST(testGetVertices);
    RUN_TEST(testGetEdgesData);
    RUN_TEST(testRemoveEdge);
    return UNITY_END();
}
