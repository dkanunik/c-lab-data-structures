#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "directedGraph.h"

Vertex *createVertex(int id) {
    Vertex *vertex = (Vertex *) malloc(sizeof(Vertex));
    if (vertex == NULL) {
        fprintf(stderr, "Memory allocation failed during Vertex creation\n");
        exit(EXIT_FAILURE);
    }

    vertex->id = id;
    vertex->edges = NULL;
    vertex->previous = NULL;
    return vertex;
}

void addVertex(DirectedGraph *graph, int id) {
    Vertex *vertex = createVertex(id);
    vertex->previous = graph->vertices;
    graph->vertices = vertex;
}

bool containsVertex(DirectedGraph *graph, int id) {
    if (graph == NULL) {
        return false;
    }

    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        if (currentVertex->id == id) {
            return true;
        }
        currentVertex = currentVertex->previous;
    }
    return false;
}

int *getVerticesData(DirectedGraph *graph) {
    int count = 0;
    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        count++;
        currentVertex = currentVertex->previous;
    }

    if (count == 0) {
        return NULL;
    }

    int *vertices = (int *) malloc(count * sizeof(int) + 1);
    if (vertices == NULL) {
        fprintf(stderr, "Memory allocation failed during getVerticesData() call\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        vertices[index++] = currentVertex->id;
        currentVertex = currentVertex->previous;
    }

    vertices[index++] = -1;
    return vertices;
}

bool removeVertex(DirectedGraph *graph, int removeVertexId) {
    Vertex *passedVertex = NULL;
    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        if (currentVertex->id == removeVertexId) {
            if (currentVertex->previous != NULL && passedVertex != NULL) {
                passedVertex->previous = currentVertex->previous;
            }

            if (currentVertex->previous == NULL && passedVertex != NULL) {
                passedVertex->previous = NULL;
            }

            if (graph->vertices->id == currentVertex->id) {
                graph->vertices =  currentVertex->previous;
            }

            freeVertex(currentVertex);
            return true;
        }
        passedVertex = currentVertex;
        currentVertex = currentVertex->previous;
    }

    return false;
}

size_t getVertexCount(DirectedGraph *graph) {
    size_t counter = 0;
    Vertex *v = graph->vertices;
    while (v != NULL) {
        counter++;
        v = v->previous;
    }
    return counter;
}

void freeVertex(Vertex *vertex) {
    free(vertex);
}
