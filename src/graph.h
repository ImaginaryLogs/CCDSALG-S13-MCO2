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


// TODO: Return an error code if graph is null.
void addAdjListToGraph(Graph* graph, AdjList* adjList) {
	// ### printf("Here 2\n");
	++graph->vertices;
	// ### printf("Vertices: %d\n", graph->vertices);
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
		printf("File not found!\n");
		return -1; // TODO: change this to an error code
	}

	/* iterate through each vertex of the undirected graph */
	fscanf(fp, "%d", &numVertices);
	// ### printf("Vertices: %d\n", numVertices);
	for (i = 0; i < numVertices; i++) {
		// ### printf("i = %d\n", i);
		fscanf(fp, "%s", currentVertexID);
		// ### printf("Vertex id = %s", currentVertexID);
		currentAdjList = createAdjList(currentVertexID);

		/* iterate through each neighbor of the current vertex */
		do {
			fscanf(fp, "%s", neighborVertexID);
            hasReachedEnd = strcmp(neighborVertexID, "-1") == 0;
            if (!hasReachedEnd) {
				addNodeToAdjList(currentAdjList, neighborVertexID);
            }
			// ### printf("Here!!");
		} while (!hasReachedEnd);
		// ### printf("Here 1\n");
		addAdjListToGraph(graph, currentAdjList);
		// ### printf("Here 3\n");
	}

  // TODO: return a success code
}


/**
 * Gets an adjacency list from a graph given a vertex ID.
 */
AdjList* getAdjList(Graph* graph, char* vertexID) {

	AdjList* adjList = NULL;
	AdjList* currAdjList = graph->firstAdjList;
	bool hasFoundAdjList = false;

	while (currAdjList != NULL && !hasFoundAdjList) {
		if (strcmp(currAdjList->vertexID, vertexID) == 0) {
			adjList = currAdjList;
			hasFoundAdjList = true;
		}
		currAdjList = currAdjList->nextAdjList;
	}
	return adjList;
}


/**
 * Determines whether a particular vertex (i.e., adjacency list) of a graph has been explored.
 */
int isVertexExplored(Graph* graph, char* vertexID) {

	AdjList* currVertex = graph->firstAdjList;
	bool hasFoundVertex = false;
	int hasBeenExplored = -1;

	while (currVertex != NULL && !hasFoundVertex) {
		if (strcmp(currVertex->vertexID, vertexID) == 0) {
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
		if (strcmp(currVertex->vertexID, vertexID) == 0) {
			currVertex->hasBeenExplored = true;
			hasFoundVertex = true;
		} else {
			currVertex = currVertex->nextAdjList;
		}
	}

	if (hasFoundVertex)
		return 0;
	return 1;
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