#include <malloc.h>
#include <stdlib.h>
#include "directedGraph.h"
#include <stdbool.h>

void freeGraph(DirectedGraph *graph) {
    if (graph == NULL) {
        return;
    }
    Vertex *vertex = graph->vertices;
    while (vertex != NULL) {
        Vertex *nextVertex = vertex->previous;
        Edge *edge = vertex->edges;
        while (edge != NULL) {
            Edge *nextEdge = edge->next;
            free(edge);
            edge = nextEdge;
        }
        free(vertex);
        vertex = nextVertex;
    }
    graph->vertices = NULL;
}

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

Edge *createEdge(Vertex *vertex) {
    Edge *edge = (Edge *) malloc(sizeof(Edge));
    if (edge == NULL) {
        fprintf(stderr, "Memory allocation failed during Edge creation\n");
        exit(EXIT_FAILURE);
    }

    edge->toVertex = vertex;
    edge->next = NULL;
    return edge;
}

void addVertex(DirectedGraph *graph, int id) {
    Vertex *vertex = createVertex(id);
    vertex->previous = graph->vertices;
    graph->vertices = vertex;
}

void addEdge(DirectedGraph *graph, int fromVertexId, int toVertexId) {
    Vertex *fromVertex = NULL;
    Vertex *toVertex = NULL;
    Vertex *vertex = graph->vertices;

    while (vertex != NULL) {
        if (vertex->id == fromVertexId) {
            fromVertex = vertex;
        }
        if (vertex->id == toVertexId) {
            toVertex = vertex;
        }
        vertex = vertex->previous;
    }

    if (fromVertex == NULL || toVertex == NULL) {
        fprintf(stderr, "One or both vertices not found.\n");
        return;
    }

    Edge *edge = createEdge(toVertex);

    edge->next = fromVertex->edges;
    fromVertex->edges = edge;
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

bool containsEdge(DirectedGraph *graph, int fromVertex, int toVertex) {
    if (graph == NULL) {
        return false;
    }

    Edge *edge = NULL;
    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        if (currentVertex->id != fromVertex) {
            currentVertex = currentVertex->previous;
            continue;
        }
        edge = currentVertex->edges;
        while (edge != NULL) {
            if (edge->toVertex->id == toVertex) {
                return true;
            }
            edge = edge->next;
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

