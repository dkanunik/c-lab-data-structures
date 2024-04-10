#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <stdbool.h>

typedef struct EdgeData EdgeData;

typedef struct Vertex {
    int id;
    struct Edge *edges;
    struct Vertex *previous;
} Vertex;

typedef struct DirectedGraph {
    Vertex *vertices;
    EdgeData **edgeData;
} DirectedGraph;

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

void addVertex(DirectedGraph *graph, int vertexId);

void addEdge(DirectedGraph *graph, int fromVertexId, int toVertexId);

void freeGraph(DirectedGraph *graph);

bool containsVertex(DirectedGraph *graph, int vertexId);

bool containsEdge(DirectedGraph *graph, int fromVertex, int toVertex);

int *getVerticesData(DirectedGraph *graph);

size_t getVertexCount(DirectedGraph *graph);

bool removeVertex(DirectedGraph *graph, int removeVertexId);

void freeVertex(Vertex *vertex);

#endif //DIRECTED_GRAPH_H
