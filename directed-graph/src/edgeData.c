#include <malloc.h>
#include <stdlib.h>
#include "directedGraph.h"

EdgeData *createEdgeData(const Vertex *fromVertex, const Vertex *toVertex) {
    EdgeData *edgeData = (EdgeData *) malloc(sizeof(EdgeData));
    if (edgeData == NULL) {
        fprintf(stderr, "Memory allocation failed during EdgeData creation\n");
        exit(EXIT_FAILURE);
    }

    edgeData->fromVertex = fromVertex->id;
    edgeData->toVertex = toVertex->id;
    return edgeData;
}

void appendEdgeData(DirectedGraph *graph, EdgeData *data, size_t size) {
    EdgeData **edges;

    if (graph->edgeData == NULL) {
        edges = malloc(sizeof(EdgeData *));
    } else {
        edges = realloc(graph->edgeData, (size + 1) * sizeof(EdgeData *));
    }

    if (edges == NULL) {
        fprintf(stderr, "Memory allocation failed during EdgeData appending\n");
        exit(EXIT_FAILURE);
    }
    graph->edgeData = edges;
    graph->edgeData[size] = data;
}

EdgeData *getEdgeData(DirectedGraph *graph) {
    if (graph == NULL) {
        return NULL;
    }

    size_t size = 0;

    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        Edge *currentEdge = currentVertex->edges;
        while (currentEdge != NULL) {
            EdgeData *data = createEdgeData(currentVertex, currentVertex->edges->toVertex);
            appendEdgeData(graph, data, size);
            size++;
            currentEdge = currentEdge->next;
        }
        currentVertex = currentVertex->previous;
    }
    return *graph->edgeData;
}
