
#include "utils.h"
#include "graph.h"
#include "stack.h"
#include "../tests/test-utils.h"
#include <math.h>
#define _USE_MATH_DEFINES (1)

#ifndef __GUI_H__
#define __GUI_H__

#define FONTSIZE 12
#define PI 3.14159l
#define lGUI (false)
#define SVG_NODE_LIMIT 32

#define PHSYIC_ENGINE_FILENAME "physic_engine.txt"
#define OUTPUT_GUI_FILENAME "GuiGraph.html"
#define LAYER_INFO_FILENAME "LAYERS_INFO.txt"

char *drawSVGRect(char *buffer, int n, dimension dSize, position rectTopLeftPostion){
    const String63 CONST_RECT_TAGS[5] = {
        "<rect width=\"",
        "\" height=\"",
        "\" x=\"",
        "\" y=\"",
        "\" rx=\"10\" ry=\"10\" fill=\"orange\"/>"
    };
    String255 strOutput = "";
    String31 strNumBuffer = "";
    String7 strNumFormat = "%d";

    int i = 0;
    int pointBuffer = 0;
    for (i = 0; i < 5; i++){
        strcat(strOutput, CONST_RECT_TAGS[i]);
        switch(i){
            case 0:
                pointBuffer = dSize.width;
                break;
            case 1:
                pointBuffer = dSize.height;
                break;
            case 2:
                pointBuffer = rectTopLeftPostion.x;
                break;
            case 3:
                pointBuffer = rectTopLeftPostion.y;
                break;
        }
        sprintf(strNumBuffer, strNumFormat, pointBuffer);
        if (i != 4) 
            strcat(strOutput, strNumBuffer);
    }

    strncpy(buffer, strOutput, n);
    return buffer;
}

char *drawSVGRectId(char *buffer, int n, dimension dSize, position rectTopLeftPostion, char *name){
    const String63 CONST_RECT_TAGS[6] = {
        "<rect width=\"",
        "\" height=\"",
        "\" x=\"",
        "\" y=\"",
        "\" id=\"",
        "\" rx=\"10\" ry=\"10\" fill=\"orange\"/>"
    };
    String255 strOutput = "";
    String31 strNumBuffer = "";
    String7 strNumFormat = "%d";

    int i = 0;
    int pointBuffer = 0;
    for (i = 0; i < 6; i++){
        strcat(strOutput, CONST_RECT_TAGS[i]);
        switch(i){
            case 0:
                pointBuffer = dSize.width;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 1:
                pointBuffer = dSize.height;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 2:
                pointBuffer = rectTopLeftPostion.x;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 3:
                pointBuffer = rectTopLeftPostion.y;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 4: 
                strcat(strOutput, name);
        }
            
    }

    strncpy(buffer, strOutput, n);
    return buffer;
}

char *drawSVGRectWithText(char *buffer, int n, dimension dSize, position rectTopLeftPostion, char *name, char *text, int fontSize){
    const String63 CONST_RECT_TAGS[6] = {
        "<rect width=\"",
        "\" height=\"",
        "\" x=\"",
        "\" y=\"",
        "\" id=\"",
        "\" rx=\"10\" ry=\"10\" fill=\"orange\"/>"
    };
    String255 strOutput = "";
    String31 strNumBuffer = "";
    String7 strNumFormat = "%d";

    int i = 0;
    int pointBuffer = 0;
    for (i = 0; i < 6; i++){
        strcat(strOutput, CONST_RECT_TAGS[i]);
        switch(i){
            case 0:
                pointBuffer = dSize.width + ((int) strlen(text)) * fontSize;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 1:
                pointBuffer = dSize.height;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 2:
                pointBuffer = rectTopLeftPostion.x;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 3:
                pointBuffer = rectTopLeftPostion.y;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 4: 
                strcat(strOutput, name);
        }
            
    }

    strncpy(buffer, strOutput, n);
    return buffer;
}

char *drawSVGLine(char *buffer, int n, position startPoint, position endPoint){
    const String63 CONST_RECT_TAGS[5] = {
        "<line x1=\"",
        "\" y1=\"",
        "\" x2=\"",
        "\" y2=\"",
        "\" style=\"stroke:black;stroke-width:5\"/>"
    };
    String255 strOutput = "";
    String31 strNumBuffer = "";
    String7 strNumFormat = "%d";

    int i = 0;
    int pointBuffer = 0;
    for (i = 0; i < 5; i++){
        strcat(strOutput, CONST_RECT_TAGS[i]);
        switch(i){
            case 0:
                pointBuffer = startPoint.x;
                break;
            case 1:
                pointBuffer = startPoint.y;
                break;
            case 2:
                pointBuffer = endPoint.x;
                break;
            case 3:
                pointBuffer = endPoint.y;
                break;
        }
        sprintf(strNumBuffer, strNumFormat, pointBuffer);
        if (i != 4) 
            strcat(strOutput, strNumBuffer);
    }

    strncpy(buffer, strOutput, n);
    return buffer;
}

char *drawSVGLineFromCenterToCenter(char *buffer, int n, dimension size1, position pos1, dimension size2, position pos2){
    position center1, center2;
    center1.x = pos1.x + size1.width/2;
    center1.y = pos1.y + size1.height/2;
    center2.x = pos2.x + size2.width/2;
    center2.y = pos2.y + size2.height/2;
    return drawSVGLine(buffer, n, center1, center2);
}

char *drawSVGLineID(char *buffer, int n, position startPoint, position endPoint, char *lineID){
    const String63 CONST_RECT_TAGS[6] = {
        "<line x1=\"",
        "\" y1=\"",
        "\" x2=\"",
        "\" y2=\"",
        "\" id=\"",
        "\" style=\"stroke:black;stroke-width:1\"/>"
    };
    String255 strOutput = "";
    String31 strNumBuffer = "";
    String7 strNumFormat = "%d";

    int i = 0;
    int pointBuffer = 0;
    for (i = 0; i < 6; i++){
        strcat(strOutput, CONST_RECT_TAGS[i]);
        switch(i){
            case 0:
                pointBuffer = startPoint.x;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 1:
                pointBuffer = startPoint.y;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 2:
                pointBuffer = endPoint.x;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 3:
                pointBuffer = endPoint.y;
                sprintf(strNumBuffer, strNumFormat, pointBuffer);
                strcat(strOutput, strNumBuffer);
                break;
            case 4:
                strcat(strOutput, lineID);
        }
    }

    strncpy(buffer, strOutput, n);
    return buffer;
}

char *drawSVGLineFromCenterToCenterId(char *buffer, int n, dimension size1, position pos1, char *pointName1, dimension size2, position pos2, char *pointName2){
    String63 name = "";
    position center1, center2;
    center1.x = pos1.x + size1.width/2;
    center1.y = pos1.y + size1.height/2;
    center2.x = pos2.x + size2.width/2;
    center2.y = pos2.y + size2.height/2;
    sprintf(name, "%s_%s", pointName1, pointName2);
    return drawSVGLineID(buffer, n, center1, center2, name);
}

char *drawSVGText(char *buffer, int n, position pos, char *strText){
    const String31 CONST_RECT_TAGS[6] = {
        "<text id=\"Text", 
        "\"x=\"",
        "\" y=\"",
        "\" fill=\"black\" font-size=\"",
        "\">",
        "</text>"
    };
    String255 strOutput = "";
    sprintf(strOutput, "%s%s%s%d%s%d%s%d%s%s%s", CONST_RECT_TAGS[0], strText, CONST_RECT_TAGS[1], pos.x, CONST_RECT_TAGS[2], pos.y, CONST_RECT_TAGS[3], FONTSIZE, CONST_RECT_TAGS[4], strText, CONST_RECT_TAGS[5]);
    strncpy(buffer, strOutput, n);
    return buffer;
}

char *drawSVGTextOnRectCenter(char *buffer, int n, dimension size, position pos, char *strText){
    pos.x += (size.width - (FONTSIZE*((int) strlen(strText) - 1)) / 2) / 2;
    pos.y += (FONTSIZE/2 + size.height) / 2;
    return drawSVGText(buffer, n, pos, strText);
}

position computeNthPolygonPosition(position input, int radius, int order, int nSides){
    input.x = (int) roundl(radius * cos(2.0l*PI*order/nSides));
    input.y = (int) roundl(radius * sin(2.0l*PI*order/nSides));
    return input;
}

int linearSearch(String31 array[], int n, String15 key) {
    int index = -1, i = 0, hasFound = 0;

    for (i = 0; i < n && !hasFound; ++i){
        LOG(lGUI, "\tSearch: %s vs %s == %d\n", array[i], key, strcmp(key, array[i]) == 0);
        if (strcmp(array[i], key) == 0){
            index = i;
            hasFound = 1;
        }
    }

    return index;
}

void instantiateCircleNodes(Graph *graph, dimension rectSize, position nodes[], int size){
    int i = 0, radius = (size - (rectSize.height > rectSize.width ? rectSize.height : rectSize.width) ) / 2;
    for (i = 0; i < graph->numVertices; i++){
        nodes[i] = computeNthPolygonPosition(nodes[i], radius, i, graph->numVertices);
        nodes[i].x += radius;
        nodes[i].y += radius;
    }
}

void instantiateBFSNodes(Graph *graph, position nodes[], dimension rectSize){
    int i = 0;
    for (i = 0; i < graph->numVertices; i++){
        nodes[i].x = 0;
        nodes[i].y = -200;
    }
}

void createCircleGraph(FILE *fpGraph, Graph *graph, int size, Queue *lineNames, Queue *pointNames, dimension rectSize){
    String255 strBufferSVG = "";
    String31 nodeNames[SVG_NODE_LIMIT];
    position nodes[SVG_NODE_LIMIT];

    int i = 0;

    instantiateCircleNodes(graph, rectSize, nodes, size);

    fprintf(fpGraph, "\n");

    int exploredNodes = 0;
    AdjList *currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        strcpy(nodeNames[exploredNodes], currVertex->vertexID);
        enqueue(pointNames, currVertex->vertexID);
        exploredNodes++;
        currVertex = currVertex->nextAdjList;
    }

    int nIndex = 0;
    String31 childName ="";
    position parentPos, childPos;
    LOG(lGUI, "Points: %d\n", exploredNodes);
    AdjList *currAdjList;
    AdjListNode *currNode;

    Queue *traversedNodes = createQueue();
    String63 combinednames1 = "", combinednames2 = "";
    bool isLineUnique = false;

    // For every parent node
    for (i = 0; i < graph->numVertices; i++){
        currAdjList = getAdjList(graph, nodeNames[i]);
        currNode = currAdjList->firstNeighbor;
        parentPos = nodes[i];
        nIndex = 0;
        LOG(lGUI,"%s->%s\n", nodeNames[i], currNode->vertexID);
        while (currNode != NULL && nIndex != -1) {
            isLineUnique = false;
            strcpy(childName, currNode->vertexID);
            currNode = currNode->nextNode;
            nIndex = linearSearch(nodeNames, exploredNodes, childName);
            LOG(lGUI, "Conditions: %d && %d\n", currNode != NULL, nIndex != -1);
            sprintf(combinednames1, "%s_%s", nodeNames[i], childName);
            sprintf(combinednames2, "%s_%s", childName,  nodeNames[i]);
            isLineUnique = nIndex != -1 && queueSearch(traversedNodes, combinednames1) == -1 && queueSearch(traversedNodes, combinednames2) == -1;
            if (isLineUnique) {
                childPos = nodes[nIndex];
                fprintf(fpGraph, "\t%s\n", drawSVGLineFromCenterToCenterId(strBufferSVG, 255, rectSize, parentPos, nodeNames[i], rectSize, childPos, childName));
                enqueue(traversedNodes, combinednames1);
                enqueue(lineNames, combinednames1);
                enqueue(traversedNodes, combinednames2);
            } else {
                LOG(lGUI, "%s Not found: %s\n", nodeNames[i], childName);
            }
        }
    }

    for (i = 0; i < graph->numVertices; i++){
        fprintf(fpGraph, "\t%s\n", "<g>");
        fprintf(fpGraph, "\t\t%s\n", drawSVGRectId(strBufferSVG, 255, rectSize, nodes[i], nodeNames[i]));
        fprintf(fpGraph, "\t\t%s\n", drawSVGTextOnRectCenter(strBufferSVG, 255, rectSize, nodes[i], nodeNames[i]));
        fprintf(fpGraph, "\t%s\n", "</g>");
    }
}

int createBFSGraph(FILE *fpGraph, Graph* graph, int side, FILE *filePointerLayerInfo, dimension rectSize){
    String31 allNodeNames[SVG_NODE_LIMIT];
    AdjList *currAdjList;

    position nodes[SVG_NODE_LIMIT];

    instantiateBFSNodes(graph, nodes, rectSize);
    
    int exploredNodes = 0;
    AdjList *currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        strcpy(allNodeNames[exploredNodes], currVertex->vertexID);
        exploredNodes++;
        currVertex = currVertex->nextAdjList;
    }
    
    int i = 0, layer, corres;
    String31 strLayer = "";
    i = 0;
    int xOffset = 0, yOffset = 0;
    while (!feof(filePointerLayerInfo)) {
        fscanf(filePointerLayerInfo, "%d %s ", &layer, strLayer);
        corres = linearSearch(allNodeNames, SVG_NODE_LIMIT, strLayer);
        if (corres == -1)
            return -1;
        xOffset = rectSize.width*i;
        yOffset = layer*rectSize.height*3;
        nodes[corres].x = xOffset + 10*i; 
        nodes[corres].y = yOffset;
        i++;
    }

    String255 strBufferSVG = "";
    String31 parentID = "", childID = "";
    position parentPos, childPos;
    // For every parent node
    for (i = 0; i < graph->numVertices; i++){
        currAdjList = getAdjList(graph, allNodeNames[i]);
        strcpy(parentID, currAdjList->parentID);
        
        if (strcmp(parentID, "ROOT") != 0) {
            
            strcpy(childID, currAdjList->vertexID);
            corres = linearSearch(allNodeNames, SVG_NODE_LIMIT, childID);
            if (corres == -1)
                return -2;
            childPos = nodes[corres];
            corres = linearSearch(allNodeNames, SVG_NODE_LIMIT, parentID);
            if (corres == -1)
                return -3;
            parentPos = nodes[corres];

            printf("(%s %s)\n", childID, parentID); 

            strcat(parentID, "1");
            strcat(childID, "1");
            fprintf(fpGraph, "\t%s\n", drawSVGLineFromCenterToCenterId(strBufferSVG, 255, rectSize, parentPos, parentID, rectSize, childPos, childID));
        }
    }
    
    for (i = 0; i <graph->numVertices; i++){
        strcpy(parentID, allNodeNames[i]);
        strcat(parentID, " ");
        fprintf(fpGraph, "\t%s\n", "<g>");
        fprintf(fpGraph, "\t\t%s\n", drawSVGRectId(strBufferSVG, 255, rectSize, nodes[i], parentID));
        fprintf(fpGraph, "\t\t%s\n", drawSVGTextOnRectCenter(strBufferSVG, 255, rectSize, nodes[i], parentID));
        fprintf(fpGraph, "\t%s\n", "</g>");
    }
    return 0;
}

void writeLinesIDs(FILE *fp, Queue *lineNames){
    String255 buffer = "";
    fprintf(fp, "\tconst lineNameIds = [ \"%s\"", dequeue(lineNames, buffer));
    while(!isQueueEmpty(lineNames)){
        fprintf(fp, ", ");
        fprintf(fp, "\"%s\"", dequeue(lineNames, buffer));
    }
    fprintf(fp, "]\n");
}

void writePointIDs(FILE *fp, Queue *textNames, Queue *pointNames){
    String255 buffer = "";
    enqueue(textNames, queueHead(pointNames));
    fprintf(fp, "\tconst pointNameIds = [ \"%s\"", dequeue(pointNames, buffer));
    while(!isQueueEmpty(pointNames)){
        fprintf(fp, ", ");
        enqueue(textNames, queueHead(pointNames));
        fprintf(fp, "\"%s\"", dequeue(pointNames, buffer));
    }
    fprintf(fp, "]\n");
}

void writeTextsIDs(FILE *fp, Queue *textNames){
    String255 buffer = "";
    fprintf(fp, "\tconst textNames = [ \"Text%s\"", dequeue(textNames, buffer));
    while(!isQueueEmpty(textNames)){
        fprintf(fp, ", ");
        fprintf(fp, "\"Text%s\"", dequeue(textNames, buffer));
    }
    fprintf(fp, "]\n");
}

void writeHTMLLines(FILE * fp, String127 CONST_HTML_TAGS[], int beginningPoint, int endPoint){
    int nWrittenTags = 0;
    for (nWrittenTags = beginningPoint; nWrittenTags < endPoint + 1; nWrittenTags++){
        fprintf(fp, "%s\n", CONST_HTML_TAGS[nWrittenTags]);
    }
}

void createHTMLGraphic(Graph *graph){ 
    String127 CONST_HTML_TAGS[13] = {
        "<!DOCTYPE html>\n\t<html lang=\"en\">\n\t<head>\n\t\t<meta charset=\"utf-8\">",
        "\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">",
        "\t\t<title>GUI</title>\n\t</head>\n\n\t<body>",
        "\t<h1>1 BFS TREE:</h1>",
        "\t</svg>\n",
        "\t<input type=\"button\" value=\"Start\" onclick=\"startAnimation()\"/>",
	    "\t<input type=\"button\" value=\"Step\" onclick=\"stepAnimation()\" />",
	    "\t<input type=\"button\" value=\"Stop\" onclick=\"stopAnimation()\" />",
        "\t<h1>2 GRAPH:</h1>",
        "\t</svg>\n",
        "<script>",
        "</script>",
        "\t</body>\n</html>",
    };
    String31 CONST_SVG_TAGS[3] = {
        "<svg width=\"",
        "\" height=\"",
        "\">"
    };

    dimension rectSize;
    rectSize.height = 40;
    rectSize.width = 80;

    FILE *filePointerOutputGUI  = fopen(OUTPUT_GUI_FILENAME, "w");
    FILE *filePointPhysicEngine = fopen(PHSYIC_ENGINE_FILENAME, "r");
    FILE *filePointerLayerInfo  = fopen(LAYER_INFO_FILENAME, "r");
    
    Queue *nameQueueLines   = createQueue();
    Queue *nameQueuePoint   = createQueue();
    Queue *nameQueueTexts   = createQueue();
    String255 buffer = "";
    
    int side = 1000, errorCode = 0;
    // Set-up of HTML file
    writeHTMLLines(filePointerOutputGUI, CONST_HTML_TAGS, 0, 3);
    
    // SVG 1
    fprintf(filePointerOutputGUI, "\t%s%d%s%d%s\n", CONST_SVG_TAGS[0], side*5, CONST_SVG_TAGS[1], side*2, CONST_SVG_TAGS[2]);
    errorCode = createBFSGraph(filePointerOutputGUI, graph, side, filePointerLayerInfo, rectSize);
    if (errorCode != 0){
        printf("BFS Error Code: %d\n", errorCode);
        printf("Please be sure to properly format the traversals.\n");
    }
    writeHTMLLines(filePointerOutputGUI, CONST_HTML_TAGS, 4, 8);
    fprintf(filePointerOutputGUI, "\t%s%d%s%d%s\n", CONST_SVG_TAGS[0], side*5, CONST_SVG_TAGS[1], side*3, CONST_SVG_TAGS[2]);
    createCircleGraph(filePointerOutputGUI, graph, side, nameQueueLines, nameQueuePoint, rectSize);
    

    /**
     * Write the Physics Engine  
     * SVG 2
     */
    writeHTMLLines(filePointerOutputGUI, CONST_HTML_TAGS, 9, 10);
    writeLinesIDs(filePointerOutputGUI, nameQueueLines);
    writePointIDs(filePointerOutputGUI, nameQueueTexts, nameQueuePoint);
    writeTextsIDs(filePointerOutputGUI, nameQueueTexts);

    while (!feof(filePointPhysicEngine)) {
        fprintf(filePointerOutputGUI, "\t%s", fgets(buffer, 255, filePointPhysicEngine));
    }

    // Closing of HTML file
    writeHTMLLines(filePointerOutputGUI, CONST_HTML_TAGS, 11, 12);

    fclose(filePointerOutputGUI);
}

#endif