#include <math.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"
#include "gui.h"

#define TEST_INPUT_FILENAME "GRAPH2.txt"

// #define TEST_INPUT_FILENAME "..\\graphs\\GRAPH2.txt" // testing

int main() {
    
    // program variables
    String31 directory = "..\\graphs\\";
    String31 filename;
    int errorCode;

    String31 startingVertexID;
    Graph* graph = createGraph();
    FILE *fp;

    /* ask the user for the filename */
    printf("%sInput filename: %s", F_NORMAL, F_CYAN);
    scanf(" %s", filename);
    strcat(directory, filename);

    // String127 e = "";
    // getcwd(e, 127);
    // printf("%s", e);

    /* construct the undirected graph */
    errorCode = constructGraph(directory, graph);
    if (errorCode == -1) {
        printf("%s%s not found.%s\n", F_RED, filename, F_NORMAL);
        return 1;
    }

    /* generate the output file */
    fp = fopen(OUTPUT_FILENAME, "w");
    printGraphVertexInfoToFile(fp, graph);
    fclose(fp);

    /* ask the user for the starting vertex */
    printf("%sInput starting vertex for the traversal: %s", F_NORMAL, F_CYAN);
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