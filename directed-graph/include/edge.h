#ifndef EDGE_DATA_H
#define EDGE_DATA_H

#include <stdbool.h>
#include "directedGraph.h"

typedef struct Edge {
    struct Vertex *toVertex;
    struct Edge *next;
} Edge;

typedef struct EdgeData {
    int fromVertex;
    int toVertex;
    size_t index;
    size_t size;
} EdgeData;

typedef struct DirectedGraph DirectedGraph;

EdgeData **getEdgeData(DirectedGraph *graph);

bool removeEdge(DirectedGraph *graph, int fromVertex, int toVertex);

void freeEdgeData(DirectedGraph *graph);

#endif //EDGE_DATA_H
