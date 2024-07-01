/**
 * Stores stack information.
 */
#include "config.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef _STACK_H_
#define _STACK_H_

#define LSTAK ENABLE_LOG_STACK

/**
 * NodeTag is double-linked list.
 */
typedef struct SNodeTag {
    char element[32];
    struct SNodeTag* prevNode;
    struct SNodeTag* nextNode;
} SNode;


/**
 * A Stack is a first in, first out data structure.
 */
typedef struct StackTag {
    SNode* top;

} Stack;


/**
 * Creates an empty stack.
 */
Stack* createStack() {
    Stack* newStack = (Stack*) malloc(sizeof(Stack));
    newStack->top = NULL;
    return newStack;
};

void stackTopInspect(Stack *S) {
	SNode *current;
    LOG(LSTAK, "STACK: \n");
	if (S != NULL && S->top != NULL){
		current = S->top;
		LOG(LSTAK, "\'%s\'", current->element);
		while (current->prevNode != NULL){
			current = current->prevNode;
			LOG(LSTAK, "%s <-> %s\'%s\'", F_RED, F_NORMAL, current->element);
		}
		LOG(LSTAK, "\n");
	}
}


/**
 * Inserts an element into a stack.
 * @param S stack pointer
 * @
 */
void push(Stack* S, char* element) {
    SNode* newNode = (SNode*) malloc(sizeof(SNode));

    strcpy(newNode->element, element);
    newNode->prevNode = S->top;
    newNode->nextNode = NULL;

    if (S->top != NULL)
        S->top->nextNode = newNode;
    
    S->top = newNode;
}


void stackPrint(Stack *S){
    SNode *E = S->top;
    LOG(LSTAK, "Stack: ");
    if (S!= NULL && E != NULL){
        LOG(LSTAK, "TOP: %s", E->element);
        while (E->prevNode != NULL){
            E = E->prevNode;
            LOG(LSTAK, "%s -> ", E->element);
        }
    } else {
        LOG(LSTAK, "NULL");
    }
    
    LOG(LSTAK, "\n");
}

/**
 * Checks if a stack is empty.
 */
bool isStackEmpty(Stack* S) {
    return S->top == NULL;
}


/**
 * Removes the top element of a stack.
 */
char* pop(Stack* S, char *receivingString) {

    // CASE 1: EMPTY
    if (isStackEmpty(S)) {
        strcpy(receivingString, "");
    } else if (S->top->prevNode != NULL) {
        // CASE 2: FULL NODE
        strcpy(receivingString, S->top->element); 
        S->top = S->top->prevNode;
        free(S->top->nextNode);
        S->top->nextNode = NULL;
    } else {
        // CASE 3: ONE NODE
        strcpy(receivingString, S->top->element);
        free(S->top);
        S->top = NULL;
    }
    
    return receivingString;
}


/**
 * Returns the top element of the stack.
 */
char* stackTop(Stack* S, char* inputPointer) {
    if (!isStackEmpty(S)){
        strcpy(inputPointer, S->top->element);
    } else {
        strcpy(inputPointer, "");
    }
    return inputPointer;
}

/**
 * Frees an entire stack from the heap.
 */
void stackDelete(Stack *S) {
    while (S->top != NULL && S->top->prevNode != NULL) {
        S->top = S->top->prevNode;
        free(S->top->nextNode);
        S->top->nextNode = NULL;
        //printf("%s<- %s ->%s\n", S->top->prevNode->element, S->top->element, S->top->nextNode->element);
    }
    if (S->top != NULL)
        free(S->top);
}


#endif