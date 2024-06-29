#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef _QUEUE_H_
#define _QUEUE_H_

#define LQUE ENABLE_LOG_QUEUE

/**
 * Stores queue information.
*/
typedef struct QNodeTag {
	char data[32];
	struct QNodeTag* pNext;
} qNode;

/*
	NOTE: In this code, "Tail" is defined as the last element inserted rather than
	the malloc where the next element will be inserted.
*/
typedef struct QueueTag {
	qNode* pQHead;
	qNode* pQTail;
} Queue;

qNode* queueNodeCreate(char* element) {
	qNode* newNode = (qNode*) malloc(sizeof(qNode));
	strcpy(newNode->data, element);
	newNode->pNext = NULL;
	return newNode;
}

Queue* queueCreate() {
	Queue* q = (Queue*) malloc (sizeof(Queue));
	q->pQHead = NULL;
	q->pQTail = NULL;
	return q;
}

void enqueue(Queue* q, char* inputString) {
	qNode* newQNode = queueNodeCreate(inputString);
	if (q->pQTail == NULL) {
		q->pQHead = q->pQTail = newQNode;
	}
	q->pQTail->pNext = newQNode;
	q->pQTail = newQNode;
}


char* dequeue(Queue* q, char* outputString) {
	if (q != NULL && q->pQHead != NULL && q->pQTail != NULL){
		qNode* removeNode = q->pQHead;
		strcpy(outputString, q->pQHead->data);
		q->pQHead = q->pQHead->pNext;

		if (q->pQHead == NULL)
			q->pQTail = NULL;

		free(removeNode);
	}
	
	return outputString;
}


char* queueHead(Queue* q) {
	return q->pQHead->data;
}

char* queueTail(Queue *q) {

	return q->pQTail->data;
}

bool queueEmpty(Queue *q) {
	return q == NULL || (q->pQHead == NULL && q->pQTail == NULL);
}

void queueDelete(Queue **q){
	qNode *previous;
	while ((*q)->pQHead != NULL && (*q)->pQHead->pNext != NULL) {
		previous = (*q)->pQHead;
        (*q)->pQHead = (*q)->pQHead->pNext;
        free(previous);
        previous = NULL;
        
    }
    if ((*q)->pQHead != NULL){
		free((*q)->pQHead);
    	(*q)->pQHead = NULL;
	}

	if ((*q)->pQTail != NULL){
		free((*q)->pQTail);
  	    (*q)->pQTail = NULL;
	}
	free((*q));
	(*q) = NULL;
}

void queuePrint(Queue *q){
	qNode *current;
	// LOG(LQUE, "QUEUE: \n");
	if (q != NULL && q->pQHead != NULL){
		current = q->pQHead;
		// LOG(LQUE, "\'%s\'", current->data);
		while (current->pNext != NULL && q->pQHead != current->pNext){
			current = current->pNext;
			// LOG(LQUE, "%s -> %s\'%s\'", F_RED, F_NORMAL, current->data);
		}
		// LOG(LQUE, "\n");
	}
}

char *queueToString(Queue *q, char *queueExpect, int size, int hasColor) {
	String255 temp = "";
	qNode *current;
	if (q != NULL && q->pQHead != NULL){
		current = q->pQHead;
		if (hasColor)
			sprintf(queueExpect, "%s%s ",F_BLUE ,current->data);
		else
			sprintf(queueExpect, "%s ",current->data);
		strncat(queueExpect, temp, size);

		while (current->pNext != NULL && q->pQHead != current->pNext){
			current = current->pNext;
			sprintf(temp, "%s ", current->data);
			strncat(queueExpect, temp, size);
		}
		if (hasColor) {
			sprintf(temp, "%s", F_NORMAL);
			strncat(queueExpect, temp, size);
		}

	}
	return queueExpect;
}

void stringToQueue(char *strInput, Queue *QueuePostfix){
	int charPosition = 0;
	int intOutput    = 0;
	int parseState   = 0;
	
	String255 strOutput = "";
	String255 token = "";

	while((int) strlen(strInput) > 0 && (int) strlen(strInput) > charPosition) {
		parseState = parseStringInput(strInput, &charPosition, &intOutput, strOutput);
		
		switch(parseState) {
			case TOKEN_NUMBER:
				sprintf(token, "%d", intOutput);
				enqueue(QueuePostfix, token);
				break;
			case TOKEN_OPERATION:
				if (strcmp(strOutput, " ") != 0)
					enqueue(QueuePostfix, strOutput);
				break; 
		}
	}
}

#endif