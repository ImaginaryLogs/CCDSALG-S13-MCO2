#include <stdio.h>

#include "stack.h"
#include "queue.h"
#include "graph.h"
#include "traversal.h"

int main() {
    int numVertices;
    scanf(" %d", &numVertices);
    constructAdjacencyList(numVertices);

    return 0;
}