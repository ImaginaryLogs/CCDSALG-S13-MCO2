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

/**
 * Corresponds to a node of an adjacency list data structure, i.e., a neighbor of a particular vertex.
 */
typedef struct AdjacencyListNodeTag {
	String15 vertexID;
	struct AdjacencyListNodeTag* nextNode;
} AdjListNode;

/**
 * Corresponds to an adjacency list data structure containing a vertex and its neighbors.
 */
typedef struct AdjacencyListTag {
	String15 parentID;
	String15 vertexID;
	int layer;
	int degree;
	bool hasBeenExplored;
	AdjListNode* firstNeighbor;
	AdjListNode* lastNeighbor;
	struct AdjacencyListTag* nextAdjList;
} AdjList;

/**
 * Corresponds to a graph data structure containing adjacency list information.
 */
typedef struct GraphTag {
	int numVertices;
	AdjList* firstAdjList;
	AdjList* lastAdjList;
} Graph;

/**
 * Creates an adjacency list node given a vertex ID.
 * @param vertexID - ID of the vertex of the node
 * @return - a pointer to the newly created adjacency list node
 */
AdjListNode* createAdjListNode(String15 vertexID) {
	AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
	strcpy(newNode->vertexID, vertexID);
	newNode->nextNode = NULL;
	return newNode;
}

/**
 * Creates an adjacency list given a vertex ID.
 * @param vertexID - ID of the vertex of the adjacency list
 * @return - a pointer to the newly created adjacency list
 */
AdjList* createAdjList(char* vertexID) {
	AdjList* newAdjList = (AdjList*) malloc(sizeof(AdjList));
	strcpy(newAdjList->vertexID, vertexID);
	strcpy(newAdjList->parentID, "");
	newAdjList->layer = 0;
	newAdjList->degree = 0;
	newAdjList->hasBeenExplored = false;
	newAdjList->firstNeighbor = NULL;
	newAdjList->lastNeighbor = NULL;
	newAdjList->nextAdjList = NULL;
	return newAdjList;
}

/**
 * Creates a graph.
 * @return - a pointer to the newly created graph
 */
Graph* createGraph() {
	Graph* newGraph = (Graph*) malloc(sizeof(Graph));
	newGraph->numVertices = 0;
	newGraph->firstAdjList = NULL;
	newGraph->lastAdjList = NULL;
	return newGraph;
}

/**
 * Adds a node to an adjacency list.
 * @param adjList - pointer to the adjacency list being added to
 * @param vertexID - ID of the vertex being added into the adjacency list
 */
void addNodeToAdjList(AdjList* adjList, String15 vertexID) {
	AdjListNode* newNode = createAdjListNode(vertexID);
	if (adjList->firstNeighbor == NULL && adjList->lastNeighbor == NULL) { // empty adjacency list
		adjList->firstNeighbor = adjList->lastNeighbor = newNode;
	} else { // nonempty adjacency list
		adjList->lastNeighbor = adjList->lastNeighbor->nextNode = newNode;
	}
	++adjList->degree;
}

/**
 * Adds an adjacency list to a graph.
 * @param graph - pointer to the graph being added to
 * @param adjList - pointer to the adjacency list being added into the graph
 */
void addAdjListToGraph(Graph* graph, AdjList* adjList) {
	++graph->numVertices;
	if (graph->firstAdjList == NULL && graph->lastAdjList == NULL) { // empty graph
		graph->firstAdjList = graph->lastAdjList = adjList;
	} else { // nonempty graph
		graph->lastAdjList = graph->lastAdjList->nextAdjList = adjList;
	}
}


// TODO: Implement deleteGraph() to free allocated memory.
/**
 * Frees up memory allocated to a graph.
 * @param graph - pointer to a pointer to a graph
 */
void deleteGraph(Graph** graph) {
	return;
}


/**
 * Constructs a graph given adjacency list information from a file.
 * @param filename - string name of the file containing adjacency list information
 * @param graph - pointer to a graph
 * @return 0 if successful; 1 if unsuccessful
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

  return 0; // successful
}


/**
 * Prints graph vertex information to a file.
 * @param fp - pointer to the file being printed to
 * @param graph - pointer to the graph containing the vertex information
 */
void printGraphVertexInfoToFile(FILE* fp, Graph* graph) {
	AdjList* currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        fprintf(fp, "\n%s%-15s%d%s", F_CYAN, currVertex->vertexID, currVertex->degree, F_NORMAL);
        currVertex = currVertex->nextAdjList;
    }
}


/**
 * Gets an adjacency list from a graph given a vertex ID.
 * @param graph - pointer to a graph
 * @param vertexID - string name of the vertexID
 * @return a pointer to the adjacency list if the vertex ID exists; NULL if nonexistent
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
 * Determines whether a vertex exists in a graph.
 * @param graph - pointer to the graph being checked
 * @param vertexID - string ID of the vertex
 * @return true if the vertex is found; false, otherwise
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
 * @param graph - pointer to the graph being checked
 * @param vertexID - string ID of the vertex being checked
 * @return true if the vertex has been explored; false, otherwise
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
 * @param graph - pointer to the graph containing the vertex
 * @param vertexID - string ID of the vertex
 * @return 0 if the vertex is found; -1 if not
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
 * @param graph - pointer to the graph being modified
 */
void setGraphToUnexplored(Graph* graph) {
	AdjList* currVertex = graph->firstAdjList;
	while (currVertex != NULL) {
		currVertex->hasBeenExplored = false;
		currVertex = currVertex->nextAdjList;
	}
}


#endif