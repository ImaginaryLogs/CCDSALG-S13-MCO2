#include <stdio.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"

#define INPUT_FILENAME "GRAPH.txt"


int main() {
    
    // program variables
    String31 filename, startingVertex;
    int errorCode;
    Graph* graph;
    
    /* ask the user for the filename */
    printf("Input filename: ");
    scanf(" %s", filename);

    // TODO: Address the error code. Refer to MCO1.
    /* construct the undirected graph*/
    errorCode = constructGraph(filename, &graph);
    // insert error handling code here

    /* ask the user for the starting vertex */
    printf("Input starting vertex for the traversal: ");
    scanf(" %s", startingVertex);

    /* execute the chosen traversal method and produce the output file */
    breadthFirstSearch(graph, startingVertex);
    depthFirstSearch(graph, startingVertex);

    return 0;
}