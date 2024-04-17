#include <stdlib.h>
#include "unity.h"
#include "directedGraph.h"

void checkIfVertexExist(size_t expectedVertexCount, int removeVertexId);

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

void testGetVertexCount() {
    const size_t EXPECTED_VERTEX_COUNT = 3;
    size_t currentVertexCount = getVertexCount(&graph);
    TEST_ASSERT_EQUAL_INT(EXPECTED_VERTEX_COUNT, currentVertexCount);
}

void testAddVertex() {
    const size_t EXPECTED_VERTEX_COUNT = 3;
    int counter = 0;
    Vertex *v = graph.vertices;
    while (v != NULL) {
        counter++;
        v = v->previous;
    }
    TEST_ASSERT_EQUAL_INT(EXPECTED_VERTEX_COUNT, counter);
}

void testAddEdge() {
    TEST_ASSERT_EQUAL_INT(3, graph.vertices[0].previous->edges->toVertex->id);
}

void testContainsVertex() {
    TEST_ASSERT_TRUE(containsVertex(&graph, 1));
    TEST_ASSERT_FALSE(containsVertex(&graph, 111));
}

void testGetVerticesData() {
    size_t count = 0;
    int const *vertices = getVerticesData(&graph);
    while (vertices[count] != -1) {
        ++count;
    }

    TEST_ASSERT_EQUAL_INT(3, count);
}

void testGetVertexOutcomeNeighbors_2() {
    Vertex *neighbors = getVertexOutcomeNeighbors(&graph, 2);
    size_t count = 0;
    size_t EXPECTED_COUNT = 2;
    while (neighbors != NULL) {
        TEST_ASSERT_TRUE(neighbors->id == 1 || neighbors->id == 3);
        count++;
        neighbors = neighbors->previous;
    }
    TEST_ASSERT_EQUAL_INT(EXPECTED_COUNT, count);
}

void testGetVertexOutcomeNeighbors_4() {
    Vertex const *neighbors = getVertexOutcomeNeighbors(&graph, 4);
    TEST_ASSERT_NULL(neighbors);
}

void testGetVertexOutcomeNeighbors_5() {
    addVertex(&graph, 5);
    Vertex const *neighbors = getVertexOutcomeNeighbors(&graph, 5);
    TEST_ASSERT_NULL(neighbors);
}

void testGetVertexIncomeNeighbors_1() {
    Vertex *neighbors = getVertexIncomeNeighbors(&graph, 1);
    size_t count = 0;
    size_t EXPECTED_COUNT = 1;
    while (neighbors != NULL) {
        TEST_ASSERT_TRUE(neighbors->id == 2);
        count++;
        neighbors = neighbors->previous;
    }
    TEST_ASSERT_EQUAL_INT(EXPECTED_COUNT, count);
}

void testGetVertexIncomeNeighbors_2() {
    Vertex *neighbors = getVertexIncomeNeighbors(&graph, 2);
    size_t count = 0;
    size_t EXPECTED_COUNT = 1;
    while (neighbors != NULL) {
        TEST_ASSERT_TRUE(neighbors->id == 1);
        count++;
        neighbors = neighbors->previous;
    }
    TEST_ASSERT_EQUAL_INT(EXPECTED_COUNT, count);
}

void testGetVertexIncomeNeighbors_4() {
    Vertex const *neighbors = getVertexIncomeNeighbors(&graph, 4);
    TEST_ASSERT_NULL(neighbors);
}

void testGetVertexIncomeNeighbors_5() {
    addVertex(&graph, 5);
    Vertex const *neighbors = getVertexIncomeNeighbors(&graph, 5);
    TEST_ASSERT_NULL(neighbors);
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

void testRemoveNonexistentVertex() {
    const size_t EXPECTED_VERTEX_COUNT = 3;
    const int NONEXISTENT_VERTEX_ID = 1000;

    bool currentRemoveResult = removeVertex(&graph, NONEXISTENT_VERTEX_ID);
    size_t currentVertexCount = getVertexCount(&graph);

    TEST_ASSERT_FALSE(currentRemoveResult);
    TEST_ASSERT_EQUAL_INT(EXPECTED_VERTEX_COUNT, currentVertexCount);
}

void testRemoveExistentVertex_1() {
    const size_t EXPECTED_VERTEX_COUNT = 2;
    const int REMOVE_VERTEX_ID = 1;

    checkIfVertexExist(EXPECTED_VERTEX_COUNT, REMOVE_VERTEX_ID);
}

void testRemoveExistentVertex_2() {
    const size_t EXPECTED_VERTEX_COUNT = 2;
    const int REMOVE_VERTEX_ID = 2;

    checkIfVertexExist(EXPECTED_VERTEX_COUNT, REMOVE_VERTEX_ID);
}

void testRemoveExistentVertex_3() {
    const size_t EXPECTED_VERTEX_COUNT = 2;
    const int REMOVE_VERTEX_ID = 3;

    checkIfVertexExist(EXPECTED_VERTEX_COUNT, REMOVE_VERTEX_ID);
}

void checkIfVertexExist(const size_t expectedVertexCount, const int removeVertexId) {
    bool currentRemoveResult = removeVertex(&graph, removeVertexId);
    size_t currentVertexCount = getVertexCount(&graph);

    TEST_ASSERT_TRUE(currentRemoveResult);
    TEST_ASSERT_EQUAL_INT(expectedVertexCount, currentVertexCount);

    size_t count = 0;
    bool isVertexExisted = false;
    int const *vertices = getVerticesData(&graph);
    while (vertices[count] != -1) {
        if (vertices[count] == removeVertexId) {
            isVertexExisted = true;
            break;
        }
        ++count;
    }

    TEST_ASSERT_FALSE(isVertexExisted);
}

void testIsEmpty() {
    TEST_ASSERT_FALSE(isEmpty(&graph));

    removeVertex(&graph, 1);
    removeVertex(&graph, 2);
    removeVertex(&graph, 3);

    TEST_ASSERT_TRUE(isEmpty(&graph));
}

void testSize() {
    const size_t EXP_SZ_BEFORE_DEL = 3;
    const size_t EXP_SZ_AFTER_DEL = 0;
    TEST_ASSERT_EQUAL_INT(EXP_SZ_BEFORE_DEL, size(&graph));

    removeVertex(&graph, 1);
    removeVertex(&graph, 2);
    removeVertex(&graph, 3);

    TEST_ASSERT_EQUAL_INT(EXP_SZ_AFTER_DEL, size(&graph));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testAddVertex);
    RUN_TEST(testGetVertexCount);
    RUN_TEST(testAddEdge);
    RUN_TEST(testContainsVertex);
    RUN_TEST(testContainsEdge);
    RUN_TEST(testGetVertexOutcomeNeighbors_2);
    RUN_TEST(testGetVertexOutcomeNeighbors_4);
    RUN_TEST(testGetVertexOutcomeNeighbors_5);
    RUN_TEST(testGetVertexIncomeNeighbors_1);
    RUN_TEST(testGetVertexIncomeNeighbors_2);
    RUN_TEST(testGetVertexIncomeNeighbors_4);
    RUN_TEST(testGetVertexIncomeNeighbors_5);
    RUN_TEST(testGetVerticesData);
    RUN_TEST(testGetEdgesData);
    RUN_TEST(testRemoveEdge);
    RUN_TEST(testRemoveNonexistentVertex);
    RUN_TEST(testRemoveExistentVertex_1);
    RUN_TEST(testRemoveExistentVertex_2);
    RUN_TEST(testRemoveExistentVertex_3);
    RUN_TEST(testIsEmpty);
    RUN_TEST(testSize);
    return UNITY_END();
}
