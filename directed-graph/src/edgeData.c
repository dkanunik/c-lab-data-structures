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

void recalculateEdgeData(DirectedGraph const *graph, size_t size) {
    for (size_t i = 0; i < size; i++) {
        graph->edgeData[i]->size = size;
    }
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

    data->index = size;
    graph->edgeData = edges;
    graph->edgeData[size] = data;

    recalculateEdgeData(graph, size + 1);
}

EdgeData **getEdgesData(DirectedGraph *graph) {
    if (graph == NULL) {
        return NULL;
    }

    size_t size = 0;

    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        Edge *currentEdge = currentVertex->edges;
        while (currentEdge != NULL) {
            EdgeData *data = createEdgeData(currentVertex, currentEdge->toVertex);
            appendEdgeData(graph, data, size);
            currentEdge = currentEdge->next;
            size++;
        }
        currentVertex = currentVertex->previous;
    }
    return graph->edgeData;
}
