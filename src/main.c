#include <math.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"
// #include "gui.h"

// #define TEST_INPUT_FILENAME "..\\graphs\\GRAPH2.txt" // testing

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

    /* execute the two traversal methods and produce the output files */
    errorCode = breadthFirstSearch(graph, startingVertexID);
    if (errorCode == 0) {
        depthFirstSearch(graph, startingVertexID);
        // createHTMLGraphic(graph);
    }
    
    /* final executions */
    printf("%s", F_NORMAL);
    deleteGraph(&graph);
    return 0;
}