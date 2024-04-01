#ifndef EDGE_DATA_H
#define EDGE_DATA_H

#include <stdbool.h>
#include "directedGraph.h"

typedef struct EdgeData {
    int fromVertex;
    int toVertex;
} EdgeData;

typedef struct DirectedGraph DirectedGraph;

EdgeData *getEdgeData(DirectedGraph *graph);

#endif //EDGE_DATA_H
