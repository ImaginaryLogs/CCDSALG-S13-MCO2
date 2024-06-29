#include <stdio.h>

#include "stack.h"
#include "queue.h"
#include "adj_list.h"
#include "graph.h"
#include "traversal.h"

typedef char String7[8];
typedef char String15[16];
typedef char String31[32];
typedef char String63[64];
typedef char String127[128];
typedef char String255[256];

#define INPUT_FILE_NAME "GRAPH.txt"
#define OUTPUT_FILE_NAME "TRAVERSALS.txt"

int main() {
    
    // program variables
    String31 fileName, startingVertex;
    AdjList* adjList;
    int errorCode;
    
    /* ask the user for the filename */
    printf("Input filename: ");
    scanf(" %s", fileName);

    // TODO: Address the error code instances. Refer to MCO1.
    /* construct the adjacency list and its corresponding undirected graph */
    errorCode = constructAdjacencyList(fileName, adjList);
    errorCode = constructUndirectedGraph(adjList);

    /* ask the user for the starting vertex */
    printf("Input starting vertex for the traversal: ");
    scanf(" %s", startingVertex);

    /* produce the corresponding output file */
    

    return 0;
}