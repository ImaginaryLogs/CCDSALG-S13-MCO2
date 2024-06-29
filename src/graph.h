#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char String7[8];
typedef char String15[16];
typedef char String31[32];
typedef char String63[64];
typedef char String127[128];
typedef char String255[256];

#ifndef _GRAPH_H_
#define _GRAPH_H_


typedef struct AdjacencyListNodeTag {
	String15 vertexID;
	struct AdjacencyListNodeTag* nextNode;
} AdjListNode;


typedef struct AdjacencyListTag {
	AdjListNode* head;
	AdjListNode* tail;
	struct AdjacencyListTag* nextAdjList;
} AdjList;


typedef struct GraphTag {
	int vertices;
	AdjList* head;
	AdjList* tail;
} Graph;


AdjListNode* createAdjListNode(String15 vertexID) {
	AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
	strcpy(newNode->vertexID, vertexID);
	newNode->nextNode = NULL;
	return newNode;
}


AdjList* createAdjList() {
	AdjList* newAdjList = (AdjList*) malloc(sizeof(AdjList));
	newAdjList->head = NULL;
	newAdjList->tail = NULL;
	newAdjList->nextAdjList = NULL;
	return newAdjList;
}


Graph* createGraph() {
	Graph* newGraph = (Graph*) malloc(sizeof(Graph));
	newGraph->vertices = 0;
	newGraph->head = NULL;
	newGraph->tail = NULL;
	return newGraph;
}


void addVertexToAdjList(AdjList* adjList, String15 vertexID) {
	AdjListNode* newNode = createAdjListNode(vertexID);
	AdjListNode* current;
	if (adjList->head == NULL && adjList->tail == NULL) { // empty adjacency list
		adjList->head = adjList->tail = newNode;
	} else { // nonempty adjacency list
		adjList->tail = adjList->tail->nextNode = newNode;
	}
}


void addAdjListToGraph(Graph* graph, AdjList* adjList) {
	++graph->vertices;
	if (graph->head == NULL && graph->tail == NULL) { // empty graph
		graph->head = graph->tail = adjList;
	} else { // nonempty graph
		graph->tail = graph->tail->nextAdjList = adjList;
	}
}


// TODO: Implement printGraph()
void printGraph(Graph* graph) {
	
}


// TODO: Implement adjListDelete()
void deleteGraph(Graph** graph) {

}


#endif