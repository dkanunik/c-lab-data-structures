#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <stdbool.h>
#include "edgeData.h"

typedef struct EdgeData EdgeData;

typedef struct Vertex {
    int id;
    struct Edge *edges;
    struct Vertex *previous;
} Vertex;

typedef struct Edge {
    struct Vertex *toVertex;
    struct Edge *next;
} Edge;

typedef struct DirectedGraph {
    Vertex *vertices;
    EdgeData **edgeData;
} DirectedGraph;

Vertex *createVertex(int id);

Edge *createEdge(Vertex *vertex);

void addVertex(DirectedGraph *graph, int id);

void addEdge(DirectedGraph *graph, int fromVertexId, int toVertexId);

void freeGraph(DirectedGraph *graph);

bool containsVertex(DirectedGraph *graph, int id);

bool containsEdge(DirectedGraph *graph, int fromVertex, int toVertex);

int *getVerticesData(DirectedGraph *graph);

#endif //DIRECTED_GRAPH_H
