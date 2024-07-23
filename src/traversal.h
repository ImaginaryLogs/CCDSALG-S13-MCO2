#ifndef _TRAVERSAL_H_
#define _TRAVERSAL_H_


#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

#define OUTPUT_FILENAME "..\\bin\\TRAVERSALS.txt"


/**
 * Traverses a graph data structure via Breadth-First Search (BFS) and prints the traversal to an output file.
 * @param graph - pointer to the graph that will be traversed
 * @param startingVertexID - string ID of the starting vertex for the traversal
 * @return 0 if the traversal is successul; 1 if any problem occurred midway
 */
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
        printf("Error opening output file.\n");
        return -1;
    }
    fprintf(fp, "\n\n%s", F_GREEN);

    setGraphToUnexplored(graph);
    enqueue(unexploredNodesQueue, startingVertexID);

    errorCode = setVertexToExplored(graph, startingVertexID);
    if (errorCode == -1) {
        printf("%sVertex %s not found.%s\n", F_RED, startingVertexID, F_NORMAL);
        return -1;
    }

    /* traverse the graph through BFS */
    while (!isQueueEmpty(unexploredNodesQueue)) {

        dequeue(unexploredNodesQueue, currentVertexID); // current vertex being explored

        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("%sVertex %s not found.%s\n", F_RED, currentVertexID, F_NORMAL);
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
                printf("%sVertex %s not found.%s\n", F_RED, currentNeighborVertexID, F_NORMAL);
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

    fprintf(fp, "%s", F_NORMAL);
    fclose(fp);
    return 0;
}


/**
 * Traverses a graph data structure via Depth-First Search (DFS) and prints the traversal to an output file.
 * @param graph - pointer to the graph that will be traversed
 * @param startingVertexID - string ID of the starting vertex for the traversal
 * @return 0 if the traversal is successul; 1 if any problem occurred midway
 */
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
        printf("Error opening output file.\n");
        return -1;
    }
    fprintf(fp, "\n\n%s", F_MAGENTA);

    setGraphToUnexplored(graph);
    push(unexploredNodesStack, startingVertexID);

    errorCode = setVertexToExplored(graph, startingVertexID);
    if (errorCode == -1) {
        printf("%sVertex %s not found.%s\n", F_RED, startingVertexID, F_NORMAL);
        return -1;
    }

    /* traverse the graph through DFS */
    while (!isStackEmpty(unexploredNodesStack)) {

        pop(unexploredNodesStack, currentVertexID); // current vertex being explored

        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("%sVertex %s not found.%s\n", F_RED, currentVertexID, F_NORMAL);
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
                printf("%sVertex %s not found.%s\n", F_RED, currentNeighborVertexID, F_NORMAL);
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

    fprintf(fp, "%s", F_NORMAL);
    fprintf(fp, "\n");
    fclose(fp);
    return 0;
}


#endif