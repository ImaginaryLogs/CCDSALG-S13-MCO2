#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String7[8];
typedef char String15[16];
typedef char String31[32];
typedef char String63[64];
typedef char String127[128];
typedef char String255[256];


typedef struct AdjacencyListNodeTag {
	String15 vertexID;
	struct AdjacencyListNodeTag* nextNode;
} AdjListNode;


typedef struct AdjacencyListTag {
	String15 vertexID;
	bool hasBeenExplored;
	AdjListNode* firstNeighbor;
	AdjListNode* lastNeighbor;
	struct AdjacencyListTag* nextAdjList;
} AdjList;


typedef struct GraphTag {
	int vertices;
	AdjList* firstAdjList;
	AdjList* lastAdjList;
} Graph;


AdjListNode* createAdjListNode(String15 vertexID) {
	AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
	strcpy(newNode->vertexID, vertexID);
	newNode->nextNode = NULL;
	return newNode;
}


AdjList* createAdjList(char* vertexID) {
	AdjList* newAdjList = (AdjList*) malloc(sizeof(AdjList));
	strcpy(newAdjList->vertexID, vertexID);
	newAdjList->hasBeenExplored = false;
	newAdjList->firstNeighbor = NULL;
	newAdjList->lastNeighbor = NULL;
	newAdjList->nextAdjList = NULL;
	return newAdjList;
}


Graph* createGraph() {
	Graph* newGraph = (Graph*) malloc(sizeof(Graph));
	newGraph->vertices = 0;
	newGraph->firstAdjList = NULL;
	newGraph->lastAdjList = NULL;
	return newGraph;
}


void addNodeToAdjList(AdjList* adjList, String15 vertexID) {
	AdjListNode* newNode = createAdjListNode(vertexID);
	if (adjList->firstNeighbor == NULL && adjList->lastNeighbor == NULL) { // empty adjacency list
		adjList->firstNeighbor = adjList->lastNeighbor = newNode;
	} else { // nonempty adjacency list
		adjList->lastNeighbor = adjList->lastNeighbor->nextNode = newNode;
	}
}


void addAdjListToGraph(Graph* graph, AdjList* adjList) {
	++graph->vertices;
	if (graph->firstAdjList == NULL && graph->lastAdjList == NULL) { // empty graph
		graph->firstAdjList = graph->lastAdjList = adjList;
	} else { // nonempty graph
		graph->lastAdjList = graph->lastAdjList->nextAdjList = adjList;
	}
}


// TODO: Implement printGraph()
void printGraph(Graph* graph) {
	
}


// TODO: Implement adjListDelete()
void deleteGraph(Graph** graph) {
  
}


// TODO: Return the appropriate error code.
/**
 * Constructs a graph given adjacency list information from a file.
 */
int constructGraph(char* filename, Graph** graph) {

	FILE* fp;
	int numVertices;
	int i;

	String31 currentVertexID;
	AdjList* currentAdjList;
	String31 neighborVertexID;
	bool hasReachedEnd;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		return -1; // TODO: change this to an error code
	}

	/* iterate through each vertex of the undirected graph */
	fscanf(fp, "%d", &numVertices);
	for (i = 0; i < numVertices; i++) {
		
		fscanf(fp, "%s", currentVertexID);
		currentAdjList = createAdjList(currentVertexID);

		/* iterate through each neighbor of the current vertex */
		do {
			fscanf(fp, "%s", neighborVertexID);
            hasReachedEnd = strcmp(neighborVertexID, "-1") == 0;
            if (!hasReachedEnd) {
				addNodeToAdjList(currentAdjList, neighborVertexID);
            }
		} while (!hasReachedEnd);

		addAdjListToGraph(graph, currentAdjList);
	}

  // TODO: return a success code
}


#endif