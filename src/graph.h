#ifndef _GRAPH_H_
#define _GRAPH_H_


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

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
	int degree;
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
	newAdjList->degree = 0;
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
	++adjList->degree;
}


void addAdjListToGraph(Graph* graph, AdjList* adjList) {
	++graph->vertices;
	if (graph->firstAdjList == NULL && graph->lastAdjList == NULL) { // empty graph
		graph->firstAdjList = graph->lastAdjList = adjList;
	} else { // nonempty graph
		graph->lastAdjList = graph->lastAdjList->nextAdjList = adjList;
	}
}


// TODO: Implement deleteGraph() to free used memory.
void deleteGraph(Graph** graph) {
	return;
}


/**
 * Constructs a graph given adjacency list information from a file.
 */
int constructGraph(char* filename, Graph* graph) {
	
	FILE* fp;
	int numVertices;
	int i;

	String31 currentVertexID;
	AdjList* currentAdjList;
	String31 neighborVertexID;
	bool hasReachedEnd;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		return -1; // unsuccessful
	}

	/* iterate through each vertex of the undirected graph */
	fscanf(fp, "%d", &numVertices);
	// ### printf("Vertices: %d\n", numVertices);
	for (i = 0; i < numVertices; i++) {
		// ### printf("i = %d\n", i);
		fscanf(fp, "%s", currentVertexID);
		// ### printf("Vertex ID = %s", currentVertexID);
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

  return 0; // successful
}


/**
 * Prints graph vertex information to the provided file pointer.
 */
void printVertexInfoToGraph(FILE* fp, Graph* graph) {
	AdjList* currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        fprintf(fp, "\n%-15s%d", currVertex->vertexID, currVertex->degree);
        currVertex = currVertex->nextAdjList;
    }
}


/**
 * Gets an adjacency list from a graph given a vertex ID.
 */
AdjList* getAdjList(Graph* graph, char* vertexID) {

	AdjList* adjList = NULL;
	AdjList* currAdjList = graph->firstAdjList;
	bool hasFoundAdjList = false;

	while (currAdjList != NULL && !hasFoundAdjList) {
		if (insensitiveStrCmp(currAdjList->vertexID, vertexID)) {
			adjList = currAdjList;
			hasFoundAdjList = true;
		}
		currAdjList = currAdjList->nextAdjList;
	}
	return adjList;
}


/**
 * Determines whether a particular vertex exists in a graph.
 */
bool doesVertexExist(Graph* graph, char* vertexID) {

	AdjList* currVertex = graph->firstAdjList;
	bool hasFoundVertex = false;

	while (currVertex != NULL && !hasFoundVertex) {
		if (insensitiveStrCmp(currVertex->vertexID, vertexID) == 0) {
			hasFoundVertex = true;
		} else {
			currVertex = currVertex->nextAdjList;
		}
	}

	return hasFoundVertex;
}


/**
 * Determines whether a particular vertex (i.e., adjacency list) of a graph has been explored.
 */
bool isVertexExplored(Graph* graph, char* vertexID) {

	AdjList* currVertex = graph->firstAdjList;
	bool hasFoundVertex = false;
	bool hasBeenExplored = false;

	while (currVertex != NULL && !hasFoundVertex) {
		if (insensitiveStrCmp(currVertex->vertexID, vertexID)) {
			hasBeenExplored = currVertex->hasBeenExplored;
			hasFoundVertex = true;
		} else {
			currVertex = currVertex->nextAdjList;
		}
	}

	return hasBeenExplored;
}


/**
 * Sets the hasBeenExplored attribute of a particular vertex (i.e., adjacency list) of a graph to true.
 */
int setVertexToExplored(Graph* graph, char* vertexID) {

	AdjList* currVertex = graph->firstAdjList;
	bool hasFoundVertex = false;

	while (currVertex != NULL && !hasFoundVertex) {
		if (insensitiveStrCmp(currVertex->vertexID, vertexID)) {
			currVertex->hasBeenExplored = true;
			hasFoundVertex = true;
		} else {
			currVertex = currVertex->nextAdjList;
		}
	}

	if (hasFoundVertex) {
		return 0;
	}
	return -1;
}


/**
 * Sets the hasBeenExplored attribute of all vertices (i.e., adjacency list) of a graph to false.
 */
int setGraphToUnexplored(Graph* graph) {
	AdjList* currVertex = graph->firstAdjList;
	while (currVertex != NULL) {
		currVertex->hasBeenExplored = false;
		currVertex = currVertex->nextAdjList;
	}
	return 1;
}


#endif