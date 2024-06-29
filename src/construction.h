#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "queue.h"
#include "graph.h"

#ifndef _CONSTRUCTION_H_
#define _CONSTRUCTION_H_


// TODO: Return the appropriate error code.
// Note: Outdated.
/**
 * Constructs an adjacency list given information from a file.
 */
int constructAdjacencyList(char* fileName, AdjList* adjList) {

    FILE* fp;
    int numVertices;
    int i;

    String31 currentVertexID;
    String31 neighborVertexID;
    int hasReachedEnd;
    Queue* q;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        return -1; // TODO: change this to an error code
    }
    fscanf(fp, "%d", &numVertices);

    /* iterate through each vertex of the undirected graph */
    for (i = 0; i < numVertices; i++) {

        q = queueCreate();

        fscanf(fp, "%s", currentVertexID);
        enqueue(q, currentVertexID);

        /* iterate through each neighbor of the current vertex */
        do {
            fscanf(fp, "%s", neighborVertexID);
            hasReachedEnd = strcmp(neighborVertexID, "-1") == 0;
            if (!hasReachedEnd) {
                enqueue(q, neighborVertexID);
            }
        } while (!hasReachedEnd);

        addQueueToAdjList(adjList, q);
    }

    fclose(fp);
}


// TODO: Return the appropriate error code.
/**
 * Constructs an undirected graph given an adjacency list.
 */
int constructUndirectedGraph(AdjList* adjList) {


}


#endif