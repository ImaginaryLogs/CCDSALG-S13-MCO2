#ifndef _TRAVERSAL_H_
#define _TRAVERSAL_H_

#include "../tests/test-utils.h"
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

#define OUTPUT_FILENAME "TRAVERSALS.txt"
#define LAYER_INFO_FILENAME "LAYERS_INFO.txt"
#define LTRA (true)

/**
 * Traverses a graph data structure via Breadth-First Search (BFS) and prints the traversal to an output file.
 * @param graph - pointer to the graph that will be traversed
 * @param startingVertexID - string ID of the starting vertex for the traversal
 * @return 0 if the traversal is successul; 1 if any problem occurred midway
 */
int breadthFirstSearch(Graph* graph, char* startingVertexID) {
    // signal(SIGSEGV, detectCrash);
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
    AdjList* childNode;

    FILE* fp = fopen(OUTPUT_FILENAME, "a");
    //FILE* fpLayer = fopen("Layers.txt", "w");
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

    String15 parentNodeVertextID = "ROOT";

    /* traverse the graph through BFS */
    while (!isQueueEmpty(unexploredNodesQueue)) {

        dequeue(unexploredNodesQueue, currentVertexID); // current vertex being explored
    
        currentVertexAdjList = getAdjList(graph, currentVertexID);
        if (currentVertexAdjList == NULL) {
            printf("%sVertex %s not found.%s\n", F_RED, currentVertexID, F_NORMAL);
            return -1;
        }
        strcpy(currentVertexID, currentVertexAdjList->vertexID); // fixes incorrect casing, if so
        
        currentNeighborNode = currentVertexAdjList->firstNeighbor;
        hasFinishedExploringVertex = currentNeighborNode == NULL;
        /** Take note of parent */
        strcpy(currentVertexAdjList->parentID, parentNodeVertextID);
        strcpy(parentNodeVertextID, currentVertexID);

        /* iterate through each neighbor of the current vertex */
        neighborCount = 0;
        while (!hasFinishedExploringVertex) {
            strcpy(currentNeighborVertexID, currentNeighborNode->vertexID);
            if (!doesVertexExist(graph, currentNeighborVertexID)) {
                printf("%sVertex %s not found.%s\n", F_RED, currentNeighborVertexID, F_NORMAL);
                return -1;
            }
            if (!isVertexExplored(graph, currentNeighborNode->vertexID)) {
                LOG(LTRA, "%s->%s\n",parentNodeVertextID, currentNeighborNode->vertexID);

                strcpy(neighborArr[neighborCount], currentNeighborVertexID);
                ++neighborCount;
                setVertexToExplored(graph, currentNeighborVertexID);

                childNode = getAdjList(graph, currentNeighborNode->vertexID);
                strcpy(childNode->parentID, parentNodeVertextID);
                childNode->layer = currentVertexAdjList->layer + 1;
            }
            currentNeighborNode = currentNeighborNode->nextNode;
            hasFinishedExploringVertex = currentNeighborNode == NULL;
        }
        // Sort the neighbor array in increasing lexicographic order.
        sortArr(neighborArr, neighborCount, true);
        // Append the sorted neighbor array to the unexploredNodesStruct.
        for (i = 0; i < neighborCount; ++i) {
            enqueue(unexploredNodesQueue, neighborArr[i]);
            strcpy(neighborArr[i], ""); // simultaneously clear the neighbor array
        }
        fprintf(fp, "%s ", currentVertexID); // print the vertex ID to the output file
        //fprintf(fpLayer, "(%s, %s, %d) ", currentVertexID, currentVertexAdjList->parentID, currentVertexAdjList->layer);
    }

    fprintf(fp, "%s", F_NORMAL);
    fclose(fp);
    //fclose(fpLayer);
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
        // Sort the neighbor array in decreasing lexicographic order.
        sortArr(neighborArr, neighborCount, false);
        // Append the sorted neighbor array to the unexploredNodesStruct.
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

void InorderTreeWalk(Graph* graph, char* currentVertexID, int n, FILE *fp, bool isBFSRelative){
    ++n;
    if (n > 500)
        return;   
    Queue *childNodeQueue = createQueue();
    String31 childrenID ="";
    AdjList* currentVertexAdjList = getAdjList(graph, currentVertexID);
    AdjList* currentNeighborAdjList;
    AdjListNode* currentNeighborNode = currentVertexAdjList->firstNeighbor;
    bool hasFinishedExploringVertex = currentNeighborNode == NULL, isExplorationOnBFS = false;
    setVertexToExplored(graph, currentVertexID);
    int parentLayer = currentVertexAdjList->layer, childLayer = 0;
    while(!hasFinishedExploringVertex){
        currentNeighborAdjList = getAdjList(graph, currentNeighborNode->vertexID);
        childLayer = currentNeighborAdjList->layer;
        isExplorationOnBFS = (!isBFSRelative || childLayer > parentLayer);
        if (!isVertexExplored(graph, currentNeighborNode->vertexID) && isExplorationOnBFS) {
            enqueue(childNodeQueue, currentNeighborNode->vertexID);
            setVertexToExplored(graph, currentNeighborNode->vertexID);
            strcpy(currentNeighborAdjList->parentID, currentVertexID);
        }
        currentNeighborNode = currentNeighborNode->nextNode;
        hasFinishedExploringVertex = currentNeighborNode == NULL;
    }

    if (!isQueueEmpty(childNodeQueue)){
        dequeue(childNodeQueue, childrenID);
        InorderTreeWalk(graph, childrenID, n, fp, isBFSRelative);
        fprintf(fp, "%d %s\n", currentVertexAdjList->layer, currentVertexID);
        fprintf(stdout, "%d %s\n", currentVertexAdjList->layer, currentVertexID);
        while(!isQueueEmpty(childNodeQueue)){
            dequeue(childNodeQueue, childrenID);
            InorderTreeWalk(graph, childrenID, n, fp, isBFSRelative);
        }
    } else {
        fprintf(fp, "%d %s\n", currentVertexAdjList->layer, currentVertexID);
        fprintf(stdout, "%d %s\n", currentVertexAdjList->layer, currentVertexID);
    }
    deleteQueue(&childNodeQueue);
}

int inorderTraversal(Graph* graph, char* startingVertexID) {
    int nodesExplored = 0;
    /* traverse the graph through DFS */
    setGraphToUnexplored(graph);

    FILE* fp = fopen(LAYER_INFO_FILENAME, "w");
    if (fp == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }
    bool isBasedOnBFS = true;
    InorderTreeWalk(graph, startingVertexID, nodesExplored, fp, isBasedOnBFS);
    fclose(fp);
    return 0;
}


#endif