#include <malloc.h>
#include <stdlib.h>
#include "directedGraph.h"

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

    freeEdgeData(graph);

    graph->vertices = NULL;
}

bool isEmpty(const DirectedGraph* graph) {
    if (graph == NULL) {
        return true;
    }

    if (graph->vertices == NULL) {
        return true;
    }

    return false;
}

size_t size(const DirectedGraph* graph) {
    size_t count = 0;
    Vertex* currentVertex = graph->vertices;

    while (currentVertex != NULL) {
        count++;
        currentVertex = currentVertex->previous;
    }

    return count;
}