#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <stdbool.h>

typedef struct Vertex {
    int id;
    struct Edge *edges;
    struct Vertex *next;
} Vertex;

typedef struct Edge {
    struct Vertex *toVertex;
    struct Edge *next;
} Edge;

typedef struct {
    Vertex *vertices;
} DirectedGraph;

Vertex *createVertex(int id);

Edge *createEdge(Vertex *vertex);

void addVertex(DirectedGraph *graph, int id);

void addEdge(DirectedGraph *graph, int fromVertexId, int toVertexId);

void freeGraph(DirectedGraph *graph);

bool containsVertex(const DirectedGraph *graph, int id);

bool containsEdge(DirectedGraph *graph, int fromVertex, int toVertex);

int *getVertices(DirectedGraph *graph);

#endif //DIRECTED_GRAPH_H
