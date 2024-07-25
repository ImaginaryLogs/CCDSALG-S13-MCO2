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

// TODO: Return the appropriate error code.
// BFS
int breadthFirstSearch(Graph* graph, char* startingVertexID) {
    signal(SIGSEGV, detectCrash);
    Queue* unexploredNodesQueue = createQueue();
    AdjList* currentVertexAdjList;
    bool hasFinishedExploringVertex;
    String15 currentVertexID;
    AdjListNode* currentNeighborNode;
    AdjList* childNode;

    FILE* fp = fopen(OUTPUT_FILENAME, "a");
    //FILE* fpLayer = fopen("Layers.txt", "w");

    if (fp == NULL) {
        printf("Error opening output file!\n");
        return -1;
    }

    // if (fpLayer == NULL){
    //     printf("Error opening Layer.txt file!\n");
    //     return -2;
    // }

    fprintf(fp, "\n\n");

    setGraphToUnexplored(graph);
    enqueue(unexploredNodesQueue, startingVertexID);
    setVertexToExplored(graph, startingVertexID);

    String15 parentNodeVertextID = "ROOT";

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
        /** Take note of parent */
        strcpy(currentVertexAdjList->parentID, parentNodeVertextID);
        strcpy(parentNodeVertextID, currentVertexID);

        /* iterate through each neighbor of the current vertex */
        while (!hasFinishedExploringVertex) {
            if (!isVertexExplored(graph, currentNeighborNode->vertexID)) {
                enqueue(unexploredNodesQueue, currentNeighborNode->vertexID);
                setVertexToExplored(graph, currentNeighborNode->vertexID);

                childNode = getAdjList(graph, currentNeighborNode->vertexID);
                strcpy(childNode->parentID, parentNodeVertextID);
                childNode->layer = currentVertexAdjList->layer + 1;
            }
            currentNeighborNode = currentNeighborNode->nextNode;
            hasFinishedExploringVertex = currentNeighborNode == NULL;
        }
        
        fprintf(fp, "%s ", currentVertexID); // print the vertex ID to the output file
        //fprintf(fpLayer, "(%s, %s, %d) ", currentVertexID, currentVertexAdjList->parentID, currentVertexAdjList->layer);
    }

    fclose(fp);
    //fclose(fpLayer);
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

        fprintf(fp, "%s\n", currentVertexID); // print the vertex ID to the output file
    }

    fprintf(fp, "\n");
    fclose(fp);
    
    return 0;
}

void InorderTreeWalk(Graph* graph, char* currentVertexID, int n, FILE *fp){
    ++n;
    if (n > 500)
        return;   
    Queue *childNodeQueue = createQueue();
    String31 childrenID ="";
    AdjList* currentVertexAdjList = getAdjList(graph, currentVertexID);
    AdjList* currentNeighborAdjList;
    AdjListNode* currentNeighborNode = currentVertexAdjList->firstNeighbor;
    bool hasFinishedExploringVertex = currentNeighborNode == NULL;
    setVertexToExplored(graph, currentVertexID);

    while(!hasFinishedExploringVertex){
        if (!isVertexExplored(graph, currentNeighborNode->vertexID)) {
            enqueue(childNodeQueue, currentNeighborNode->vertexID);
            setVertexToExplored(graph, currentNeighborNode->vertexID);
            currentNeighborAdjList = getAdjList(graph, currentNeighborNode->vertexID);
            strcpy(currentNeighborAdjList->parentID, currentVertexID);
        }
        currentNeighborNode = currentNeighborNode->nextNode;
        hasFinishedExploringVertex = currentNeighborNode == NULL;
    }

    if (!isQueueEmpty(childNodeQueue)){
        dequeue(childNodeQueue, childrenID);
        InorderTreeWalk(graph, childrenID, n, fp);
        fprintf(fp, "%d %s\n", currentVertexAdjList->layer, currentVertexID);
        while(!isQueueEmpty(childNodeQueue)){
            dequeue(childNodeQueue, childrenID);
            InorderTreeWalk(graph, childrenID, n, fp);
        }
    } else {
        fprintf(fp, "%d %s\n", currentVertexAdjList->layer, currentVertexID);
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
    
    InorderTreeWalk(graph, startingVertexID, nodesExplored, fp);
    fclose(fp);
    return 0;
}


#endif