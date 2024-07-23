#ifndef _TRAVERSAL_H_
#define _TRAVERSAL_H_


#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

#define OUTPUT_FILENAME "..\\bin\\TRAVERSALS.txt"


int breadthFirstSearch(Graph* graph, char* startingVertexID) {

    Queue* unexploredNodesQueue = createQueue();
    AdjList* currentVertexAdjList;
    int errorCode;
    bool hasFinishedExploringVertex;
    String31 currentVertexID;
    AdjListNode* currentNeighborNode;
    String31 currentNeighborVertexID;
    String31 neighborArr[999]; // assume there is a maximum of 999 neighbors for any given node
    int neighborCount;
    int i;

    FILE* fp = fopen(OUTPUT_FILENAME, "a");
    if (fp == NULL) {
        printf("Error opening output file!\n");
        return -1;
    }
    fprintf(fp, "\n\n");

    setGraphToUnexplored(graph);
    enqueue(unexploredNodesQueue, startingVertexID);

    errorCode = setVertexToExplored(graph, startingVertexID);
    if (errorCode == -1) {
        printf("Vertex '%s' not found.\n", startingVertexID);
        return -1;
    }

    /* traverse the graph through BFS */
    while (!isQueueEmpty(unexploredNodesQueue)) {

        dequeue(unexploredNodesQueue, currentVertexID); // current vertex being explored

        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("Vertex '%s' not found.\n", currentVertexID);
            return -1;
        }
        strcpy(currentVertexID, currentVertexAdjList->vertexID);

        currentNeighborNode = currentVertexAdjList->firstNeighbor;
        hasFinishedExploringVertex = currentNeighborNode == NULL;

        /* iterate through each neighbor of the current vertex */
        neighborCount = 0;
        while (!hasFinishedExploringVertex) {
            strcpy(currentNeighborVertexID, currentNeighborNode->vertexID);
            if (!doesVertexExist(graph, currentNeighborVertexID)) {
                printf("Vertex '%s' not found.\n", currentNeighborVertexID);
                return -1;
            }
            if (!isVertexExplored(graph, currentNeighborVertexID)) {
                strcpy(neighborArr[neighborCount], currentNeighborVertexID);
                ++neighborCount;
                setVertexToExplored(graph, currentNeighborVertexID);
            }
            currentNeighborNode = currentNeighborNode->nextNode;
            hasFinishedExploringVertex = currentNeighborNode == NULL;
        }
        // TODO: Function that sorts the neighbor array in increasing/decreasing lexicographic order.
        sortArr(neighborArr, neighborCount, true);
        // TODO: Append the sorted neighbor array to the unexploredNodesStruct.
        for (i = 0; i < neighborCount; ++i) {
            enqueue(unexploredNodesQueue, neighborArr[i]);
            strcpy(neighborArr[i], ""); // simultaneously clear the neighbor array
        }
        fprintf(fp, "%s ", currentVertexID); // print the vertex ID to the output file
    }

    fclose(fp);
    return 0;
}


int depthFirstSearch(Graph* graph, char* startingVertexID) {
    
    Stack* unexploredNodesStack = createStack();
    AdjList* currentVertexAdjList;
    int errorCode;
    bool hasFinishedExploringVertex;
    String31 currentVertexID;
    AdjListNode* currentNeighborNode;
    String31 currentNeighborVertexID;
    String31 neighborArr[999]; // assume there is a maximum of 999 neighbors for any given node
    int neighborCount;
    int i;

    FILE* fp = fopen(OUTPUT_FILENAME, "a");
    if (fp == NULL) {
        printf("Error opening output file!\n");
        return -1;
    }
    fprintf(fp, "\n\n");

    setGraphToUnexplored(graph);
    push(unexploredNodesStack, startingVertexID);

    errorCode = setVertexToExplored(graph, startingVertexID);
    if (errorCode == -1) {
        printf("Vertex '%s' not found.\n", startingVertexID);
        return -1;
    }

    /* traverse the graph through DFS */
    while (!isStackEmpty(unexploredNodesStack)) {

        pop(unexploredNodesStack, currentVertexID); // current vertex being explored

        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("Vertex '%s' not found.\n", currentVertexID);
            return -1;
        }
        strcpy(currentVertexID, currentVertexAdjList->vertexID);

        currentNeighborNode = currentVertexAdjList->firstNeighbor;
        hasFinishedExploringVertex = currentNeighborNode == NULL;

        /* iterate through each neighbor of the current vertex */
        neighborCount = 0;
        while (!hasFinishedExploringVertex) {
            strcpy(currentNeighborVertexID, currentNeighborNode->vertexID);
            if (!doesVertexExist(graph, currentNeighborVertexID)) {
                printf("Vertex '%s' not found.\n", currentNeighborVertexID);
                return -1;
            }
            if (!isVertexExplored(graph, currentNeighborVertexID)) {
                strcpy(neighborArr[neighborCount], currentNeighborVertexID);
                ++neighborCount;
                setVertexToExplored(graph, currentNeighborVertexID);
            }
            currentNeighborNode = currentNeighborNode->nextNode;
            hasFinishedExploringVertex = currentNeighborNode == NULL;
        }
        sortArr(neighborArr, neighborCount, false);
        for (i = 0; i < neighborCount; ++i) {
            push(unexploredNodesStack, neighborArr[i]);
            strcpy(neighborArr[i], ""); // simultaneously clear the neighbor array
        }
        fprintf(fp, "%s ", currentVertexID); // print the vertex ID to the output file
    }

    fprintf(fp, "\n");
    fclose(fp);
    return 0;
}


#endif