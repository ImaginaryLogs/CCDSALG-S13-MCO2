#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"

#ifndef _ADJ_LIST_H_
#define _ADJ_LIST_H_


typedef struct AdjacencyListNodeTag {
	Queue* vertexIDQ;
	struct AdjacencyListNodeTag* nextAdjListNode;
} AdjListNode;


typedef struct AdjacencyListTag {
	AdjListNode* head;
	AdjListNode* tail;
} AdjList;


AdjListNode* createAdjListNode(Queue* q) {
	AdjListNode* newAdjListNode = (AdjListNode*) malloc(sizeof(AdjListNode));
	newAdjListNode->vertexIDQ = q;
	newAdjListNode->nextAdjListNode = NULL;
	return newAdjListNode;
}


AdjList* createAdjList() {
	AdjList* newAdjList = (AdjList*) malloc(sizeof(AdjList));
	newAdjList->head = NULL;
	newAdjList->tail = NULL;
	return newAdjList;
}


void addQueueToAdjList(AdjList* adjList, Queue* q) {
	AdjListNode* newAdjListNode = createAdjListNode(q);
	if (adjList->tail == NULL) { // adjacency list is empty
		adjList->head = adjList->tail = newAdjListNode;
	} else { // adjacency list is not empty
		adjList->tail = adjList->tail->nextAdjListNode = newAdjListNode;
	}
}


// TODO: Implement adjListDelete()
void adjListDelete(AdjList** adjList) {

}


// TODO: Test this.
void adjListPrint(AdjList* adjList) {

	AdjListNode* currentAdjListNode = adjList->head;
	int hasReachedEnd = false;

	printf("ADJACENCY LIST:\n");
	if (adjList != NULL && currentAdjListNode != NULL) { // adjacency list is existent and not empty
		while (!hasReachedEnd) {
			queuePrint(currentAdjListNode->vertexIDQ);
			currentAdjListNode = currentAdjListNode->nextAdjListNode;
			hasReachedEnd = currentAdjListNode == NULL;
		}
	} else { // adjacency list is nonexistent or empty
		printf("Empti adj list :<\n");
	}
}


#endif