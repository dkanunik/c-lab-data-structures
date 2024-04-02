#ifndef EDGE_DATA_H
#define EDGE_DATA_H

#include <stdbool.h>
#include "directedGraph.h"

typedef struct EdgeData {
    int fromVertex;
    int toVertex;
    size_t index;
    size_t size;
} EdgeData;

typedef struct DirectedGraph DirectedGraph;

EdgeData **getEdgesData(DirectedGraph *graph);

#endif //EDGE_DATA_H
