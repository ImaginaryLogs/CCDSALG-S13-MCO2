#include <stdio.h>
#include <math.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"
#include "gui.h"

#define TEST_INPUT_FILENAME "GRAPH2.txt"


int main() {
    
    // program variables
    // String31 directory = "..\\graphs\\";
    // String31 filename;
    int errorCode;
    AdjList* currVertex;
    String31 startingVertexID;
    Graph* graph = createGraph();
    FILE *fp;

    /* ask the user for the filename */
    // ### printf("Input filename: ");
    // ### scanf(" %s", filename);

    // TODO: Address the error code. Refer to MCO1.
    /* construct the undirected graph */
    // ### strcat(directory, filename);
    // String127 e = "";
    // getcwd(e, 127);
    // printf("%s", e);
    errorCode = constructGraph(TEST_INPUT_FILENAME, graph);
    if (errorCode == -1)
        printf("File not found.\n");
    // insert error handling code here

    fp = fopen(OUTPUT_FILENAME, "w");
    if (fp == NULL)
        printf("Output file failed to be generated.\n");

    // temporary; will be refactored elsewhere
    currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        printf("\n%-15s%d", currVertex->vertexID, currVertex->degree);
        fprintf(fp, "\n%-15s%d", currVertex->vertexID, currVertex->degree);
        currVertex = currVertex->nextAdjList;
        // ### printf("Here 4\n");
    }
    printf("\n");
    // ### printf("Here 5\n");
    fclose(fp);

    /* ask the user for the starting vertex */
    printf("Input starting vertex for the traversal: ");
    scanf(" %s", startingVertexID);

    /* execute the chosen traversal method and produce the output file */
    breadthFirstSearch(graph, startingVertexID);
    printf("Finished BFS!\n");
    depthFirstSearch(graph, startingVertexID);
    printf("Finished DFS!\n");
    inorderTraversal(graph, startingVertexID);
    printf("Finished Calculating BFS Tree positions!\n");
    createHTMLGraphic(graph);
    printf("Finished Printing Graph!\n");
    printf("Reached end of program!\n");
    deleteGraph(&graph);
    return 0;
}