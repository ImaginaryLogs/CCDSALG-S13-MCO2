#include <stdio.h>
#include <math.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"
// #include "gui.h"

#define TEST_INPUT_FILENAME "..\\graphs\\GRAPH2.txt"

/**
 * References:
 * 
 */

int main() {
    
    // program variables
    String31 directory = "..\\graphs\\";
    String31 filename;
    int errorCode;
    AdjList* currVertex;
    String31 startingVertexID;
    Graph* graph = createGraph();
    FILE *fp;

    /* ask the user for the filename */
    /*
    printf("Input filename: ");
    scanf(" %s", filename);
    strcat(directory, filename);
    */

    // String127 e = "";
    // getcwd(e, 127);
    // printf("%s", e);

    /* construct the undirected graph */
    errorCode = constructGraph(TEST_INPUT_FILENAME, graph);
    if (errorCode == -1) {
        printf("%s not found.\n", filename);
        return 1;
    }

    /* generate the output file */
    fp = fopen(OUTPUT_FILENAME, "w");
    printVertexInfoToGraph(fp, graph);
    fclose(fp);

    /* ask the user for the starting vertex */
    printf("Input starting vertex for the traversal: ");
    scanf(" %s", startingVertexID);

    /* execute the two traversal methods and produce the output files */
    errorCode = breadthFirstSearch(graph, startingVertexID);
    if (errorCode == 0) {
        depthFirstSearch(graph, startingVertexID);
        // createHTMLGraphic(graph);
    }
    
    /* free allocated memory */
    deleteGraph(&graph);
    return 0;
}