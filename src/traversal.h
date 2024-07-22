#ifndef _TRAVERSAL_H_
#define _TRAVERSAL_H_


#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

#define OUTPUT_FILENAME "TRAVERSALS.txt"


// TODO: Return the appropriate error code.
// BFS
int breadthFirstSearch(Graph* graph, char* startingVertexID) {

    Queue* unexploredNodesQueue = createQueue();
    AdjList* currentVertexAdjList;
    bool hasFinishedExploringVertex;
    String15 currentVertexID;
    AdjListNode* currentNeighborNode;

    FILE* fp = fopen(OUTPUT_FILENAME, "a");
    if (fp == NULL) {
        printf("Error opening output file!\n");
        return -1;
    }
    fprintf(fp, "\n\n");

    setGraphToUnexplored(graph);
    enqueue(unexploredNodesQueue, startingVertexID);
    setVertexToExplored(graph, startingVertexID);

    /* traverse the graph through BFS */
    while (!isQueueEmpty(unexploredNodesQueue)) {

        dequeue(unexploredNodesQueue, currentVertexID); // current vertex being explored

        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("Error getting adjacency list!\n");
            return -1;
        }

        currentNeighborNode = currentVertexAdjList->firstNeighbor;
        hasFinishedExploringVertex = currentNeighborNode == NULL;

        /* iterate through each neighbor of the current vertex */
        while (!hasFinishedExploringVertex) {
            if (!isVertexExplored(graph, currentNeighborNode->vertexID)) {
                enqueue(unexploredNodesQueue, currentNeighborNode->vertexID);
                setVertexToExplored(graph, currentNeighborNode->vertexID);
            }
            currentNeighborNode = currentNeighborNode->nextNode;
            hasFinishedExploringVertex = currentNeighborNode == NULL;
        }
        
        fprintf(fp, "%s ", currentVertexID); // print the vertex ID to the output file
    }

    fclose(fp);
    return 0;
}


// TODO: Return the appropriate error code.
// DFS
int depthFirstSearch(Graph* graph, char* startingVertexID) {
    Stack* unexploredNodesStack = createStack();
    AdjList* currentVertexAdjList;
    bool hasFinishedExploringVertex;
    String15 currentVertexID;
    AdjListNode* currentNeighborNode;

    FILE* fp = fopen(OUTPUT_FILENAME, "a");
    if (fp == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }
    fprintf(fp, "\n\n");

    setGraphToUnexplored(graph);
    push(unexploredNodesStack, startingVertexID);
    setVertexToExplored(graph, startingVertexID);

    /* traverse the graph through DFS */
    while (!isStackEmpty(unexploredNodesStack)) {

        pop(unexploredNodesStack, currentVertexID); // current vertex being explored

        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("Error getting adjacency list!\n");
            return -1;
        }

        currentNeighborNode = currentVertexAdjList->firstNeighbor;
        hasFinishedExploringVertex = currentNeighborNode == NULL;

        /* iterate through each neighbor of the current vertex */
        while (!hasFinishedExploringVertex) {
            if (!isVertexExplored(graph, currentNeighborNode->vertexID)) {
                push(unexploredNodesStack, currentNeighborNode->vertexID);
                setVertexToExplored(graph, currentNeighborNode->vertexID);
            }
            currentNeighborNode = currentNeighborNode->nextNode;
            hasFinishedExploringVertex = currentNeighborNode == NULL;
        }

        fprintf(fp, "%s ", currentVertexID); // print the vertex ID to the output file
    }

    fprintf(fp, "\n");
    fclose(fp);
    return 0;
}


#endif