
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
#define lGUI (1)

#define OUTPUT_FILENAME "TRAVERSALS.txt"

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
        "\" style=\"stroke:black;stroke-width:5\"/>"
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
    const String31 CONST_RECT_TAGS[5] = {
        "<text x=\"",
        "\" y=\"",
        "\" fill=\"black\" font-size=\"",
        "\">",
        "</text>"
    };
    String255 strOutput = "";
    sprintf(strOutput, "%s%d%s%d%s%d%s%s%s", CONST_RECT_TAGS[0], pos.x, CONST_RECT_TAGS[1], pos.y, CONST_RECT_TAGS[2], FONTSIZE, CONST_RECT_TAGS[3], strText, CONST_RECT_TAGS[4]);
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

void instantiateNodes(Graph *graph, dimension rectSize, position nodes[], int size){
    int i = 0, radius = (size - (rectSize.height > rectSize.width ? rectSize.height : rectSize.width) ) / 2;
    for (i = 0; i < graph->vertices; i++){
        nodes[i] = computeNthPolygonPosition(nodes[i], radius, i, graph->vertices);
        nodes[i].x += radius;
        nodes[i].y += radius;
    }
}

void createCircleGraph(FILE *fpGRAPH, Graph *graph, int size){
    String255 strBufferSVG = "";
    String31 nodeNames[16];
    position nodes[16];
    dimension rectSize;
    rectSize.height = 60;
    rectSize.width = 80;
    int i = 0;

    instantiateNodes(graph, rectSize, nodes, size);

    fprintf(fpGRAPH, "\n");

    int exploredNodes = 0;
    AdjList *currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        strcpy(nodeNames[exploredNodes], currVertex->vertexID);
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
    for (i = 0; i < graph->vertices; i++){
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
                fprintf(fpGRAPH, "\t%s\n", drawSVGLineFromCenterToCenterId(strBufferSVG, 255, rectSize, parentPos, nodeNames[i], rectSize, childPos, childName));
                enqueue(traversedNodes, combinednames1);
                enqueue(traversedNodes, combinednames2);
            } else {
                LOG(lGUI, "%s Not found: %s\n", nodeNames[i], childName);
            }
        }
    }

    for (i = 0; i < graph->vertices; i++){
        fprintf(fpGRAPH, "\t%s\n", "<g>");
        fprintf(fpGRAPH, "\t\t%s\n", drawSVGRectId(strBufferSVG, 255, rectSize, nodes[i], nodeNames[i]));
        fprintf(fpGRAPH, "\t\t%s\n", drawSVGTextOnRectCenter(strBufferSVG, 255, rectSize, nodes[i], nodeNames[i]));
        fprintf(fpGRAPH, "\t%s\n", "</g>");
    }
}

void createHTMLGraphic(Graph *graph){
    signal(SIGSEGV, detectCrash);
    const String31 OUTPUT_GUI_FILENAME = "GuiGraph.html";
    const String127 CONST_HTML_TAGS[11] = {
        "<!DOCTYPE html>\n\t<html lang=\"en\">\n\t<head>\n\t\t<meta charset=\"utf-8\">",
        "\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">",
        "\t\t<title>GUI</title>\n\t</head>\n\n\t<body>",
        "\t<h1>OUTPUT:</h1>",
        "\t</svg>\n",
        "<input type=\"button\" value=\"Start\" onclick=\"startAnimation()\"/>",
	    "<input type=\"button\" value=\"Step\" onclick=\"stepAnimation()\" />",
	    "<input type=\"button\" value=\"Stop\" onclick=\"stopAnimation()\" />",
        "<script>",
        "</script>",
        "\t</body>\n</html>",
    };
    FILE *fp = fopen(OUTPUT_GUI_FILENAME, "w");
    
    int nWrittenTags = 0;
    for (nWrittenTags = 0; nWrittenTags < 4; nWrittenTags++){
        fprintf(fp, "%s\n", CONST_HTML_TAGS[nWrittenTags]);
    }

    const String31 CONST_SVG_TAGS[3] = {
        "<svg width=\"",
        "\" height=\"",
        "\">"
    };

    int side = 1000;
    fprintf(fp, "\t%s%d%s%d%s\n", CONST_SVG_TAGS[0], side, CONST_SVG_TAGS[1], side, CONST_SVG_TAGS[2]);

    // fprintf(fp, "%s\n", drawSVGRect(strBufferSVG, 255, p, e));
    createCircleGraph(fp, graph, side);

    for (nWrittenTags = 4; nWrittenTags < 9; nWrittenTags++){
        fprintf(fp, "%s\n", CONST_HTML_TAGS[nWrittenTags]);
    }

    FILE *fp2 = fopen("pe.txt", "w");
    String255 buffer = "";
    while (!feof(fp2)) {
        fprintf(fp, "%s", fgets(buffer, 255, fp2));
    }

    for (nWrittenTags = 9; nWrittenTags < 11; nWrittenTags++){
        fprintf(fp, "%s\n", CONST_HTML_TAGS[nWrittenTags]);
    }


    fclose(fp);
}



#endif