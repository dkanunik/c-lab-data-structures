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
        Vertex *nextVertex = vertex->next;
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
    vertex->next = NULL;
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
    vertex->next = graph->vertices;
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
        vertex = vertex->next;
    }

    if (fromVertex == NULL || toVertex == NULL) {
        fprintf(stderr, "One or both vertices not found.\n");
        return;
    }

    Edge *edge = createEdge(toVertex);

    edge->next = fromVertex->edges;
    fromVertex->edges = edge;
}

bool containsVertex(const DirectedGraph *graph, int id) {
    if (graph == NULL) {
        return false;
    }

    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        if (currentVertex->id == id) {
            return true;
        }
        currentVertex = currentVertex->next;
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
            currentVertex = currentVertex->next;
            continue;
        }
        edge = currentVertex->edges;
        while (edge != NULL) {
            if (edge->toVertex->id == toVertex) {
                return true;
            }
            edge = edge->next;
        }
        currentVertex = currentVertex->next;
    }
    return false;
}

int *getVertices(DirectedGraph *graph) {
    int count = 0;
    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        count++;
        currentVertex = currentVertex->next;
    }

    if (count == 0) {
        return NULL;
    }

    int *vertices = (int *) malloc(count * sizeof(int));
    if (vertices == NULL) {
        fprintf(stderr, "Memory allocation failed during getVertices() call\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        vertices[index++] = currentVertex->id;
        currentVertex = currentVertex->next;
    }

    return vertices;
}
