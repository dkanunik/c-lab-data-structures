#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <stdbool.h>

typedef struct EdgeData {
    int fromVertex;
    int toVertex;
    size_t index;
    size_t size;
} EdgeData;

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


void addVertex(DirectedGraph *graph, int vertexId);

bool containsVertex(DirectedGraph *graph, int vertexId);

Vertex *getVertex(DirectedGraph *graph, int id);

int *getVerticesData(DirectedGraph *graph);

Vertex* getVertexOutcomeNeighbors(DirectedGraph *graph, int id);

size_t getVertexCount(DirectedGraph *graph);

bool removeVertex(DirectedGraph *graph, int removeVertexId);

void freeVertex(Vertex *vertex);

void addEdge(DirectedGraph *graph, int fromVertexId, int toVertexId);

EdgeData **getEdgeData(DirectedGraph *graph);

bool containsEdge(DirectedGraph *graph, int fromVertex, int toVertex);

bool removeEdge(DirectedGraph *graph, int fromVertex, int toVertex);

void freeEdgeData(DirectedGraph *graph);

void freeGraph(DirectedGraph *graph);

#endif //DIRECTED_GRAPH_H
