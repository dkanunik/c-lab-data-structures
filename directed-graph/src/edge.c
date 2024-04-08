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

EdgeData **getEdgeData(DirectedGraph *graph) {
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

void freeEdgeData(DirectedGraph *graph) {
    if (graph == NULL || graph->edgeData == NULL) {
        return;
    }

    size_t count = 0;
    size_t size = (*graph->edgeData)->size;

    while (count < size) {
        EdgeData *edgeData = graph->edgeData[count++];
        free(edgeData);
    }

    graph->edgeData = NULL;
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

Edge *createEdge(Vertex *fromVertex, Vertex *toVertex) {
    Edge *edge = (Edge *) malloc(sizeof(Edge));
    if (edge == NULL) {
        fprintf(stderr, "Memory allocation failed during Edge creation\n");
        exit(EXIT_FAILURE);
    }

    edge->toVertex = toVertex;
    edge->next = fromVertex->edges;
    return edge;
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

    Edge *edge = createEdge(fromVertex, toVertex);
    fromVertex->edges = edge;
}

void relinkEdges(Vertex *fromVertex, Edge *prev, Edge *current) {
    if (prev != NULL) {
        prev->next = current->next;
    } else {
        fromVertex->edges = current->next;
    }

    free(current);
}

bool removeEdge(DirectedGraph *graph, int fromVertex, int toVertex) {
    if (graph == NULL) {
        return false;
    }

    Edge *prevEdge = NULL;

    Vertex *currentVertex = graph->vertices;
    while (currentVertex != NULL) {
        Edge *currentEdge = currentVertex->edges;
        while (currentEdge != NULL) {
            if (currentVertex->id == fromVertex && currentEdge->toVertex->id == toVertex) {
                relinkEdges(currentVertex, prevEdge, currentEdge);
                return true;
            } else {
                prevEdge = currentEdge;
                currentEdge = currentEdge->next;
            }
        }
        currentVertex = currentVertex->previous;
    }
    return false;
}
