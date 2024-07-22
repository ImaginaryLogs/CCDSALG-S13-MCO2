
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
        "\" fill=\"yellow\"/>"
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

char *drawSVGText(char *buffer, int n, position pos, char *strText){
    const String63 CONST_RECT_TAGS[5] = {
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

void createHTMLGraphic(Graph *graph){
    signal(SIGSEGV, detectCrash);
    const String31 OUTPUT_GUI_FILENAME = "GuiGraph.html";
    const String127 CONST_HTML_TAGS[5] = {
        "<!DOCTYPE html>\n\t<html lang=\"en\">\n\t<head>\n\t\t<meta charset=\"utf-8\">",
        "\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">",
        "\t\t<title>GUI</title>\n\t</head>\n\n\t<body>",
        "\t<h1>OUTPUT:</h1>",
        "\t</svg>\n\t</body>\n</html>",
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
    int side = 500;
    fprintf(fp, "\t%s%d%s%d%s\n", CONST_SVG_TAGS[0], side, CONST_SVG_TAGS[1], side, CONST_SVG_TAGS[2]);

    

    // fprintf(fp, "%s\n", drawSVGRect(strBufferSVG, 255, p, e));
    createCircleGraph(fp, graph);

    for (nWrittenTags = 4; nWrittenTags < 5; nWrittenTags++){
        fprintf(fp, "%s\n", CONST_HTML_TAGS[nWrittenTags]);
    }

    fclose(fp);
}

position computeNthPolygonPosition(position input, int radius, int order, int nSides){
    input.x = (int) roundl(radius * cos(2.0l*PI*order/nSides));
    input.y = (int) roundl(radius * sin(2.0l*PI*order/nSides));
    return input;
}

void createCircleGraph(FILE *fpGRAPH, Graph *graph){
    String255 strBufferSVG = "";
    dimension p;
    p.height = 60;
    p.width = 80;

    position nodes[16];
    String31 nodeNames[16];
    int exploredNodes = 0;
    int i = 0;
    for (i = 0; i < graph->vertices; i++){
        nodes[i] = computeNthPolygonPosition(nodes[i], 200, i, graph->vertices);
        nodes[i].x += 200;
        nodes[i].y += 200;
    }
    fprintf(fpGRAPH, "\n");

    AdjList *currVertex = graph->firstAdjList;
    while (currVertex != NULL) {
        strcpy(nodeNames[exploredNodes], currVertex->vertexID);
        exploredNodes++;
        currVertex = currVertex->nextAdjList;
        // ### printf("Here 4\n");
    }



    int j = 0;
    int nIndex = 0;
    String31 childNode ="";
    position parentPos, childPos;
    LOG(lGUI, "Points: %d\n", exploredNodes);
    for (i = 0; i < graph->vertices; i++){
        AdjList *currAdjList = getAdjList(graph, nodeNames[i]);
        AdjListNode *currNode = currAdjList->firstNeighbor;
        parentPos = nodes[i];
        nIndex = 0;
        LOG(lGUI,"%s->%s\n", nodeNames[i], currNode->vertexID);
        while (currNode != NULL && nIndex != -1) {
            strcpy(childNode, currNode->vertexID);
            currNode = currNode->nextNode;
            nIndex = linearSearch(nodeNames, exploredNodes, childNode);
            LOG(lGUI, "Conditions: %d && %d\n", currNode != NULL, nIndex != -1);
            if (nIndex != -1) {
                childPos = nodes[nIndex];
                fprintf(fpGRAPH, "\t%s\n", drawSVGLineFromCenterToCenter(strBufferSVG, 255, p, parentPos, p, childPos));
            } else {
                LOG(lGUI, "%s Not found: %s\n", nodeNames[i], childNode);
            }
        }
        linearSearch(nodeNames, exploredNodes, nodeNames[i]);
    }

    for (i = 0; i < graph->vertices; i++){
        fprintf(fpGRAPH, "\t%s\n", drawSVGRect(strBufferSVG, 255, p, nodes[i]));
        fprintf(fpGRAPH, "\t%s\n", drawSVGTextOnRectCenter(strBufferSVG, 255, p, nodes[i], nodeNames[i]));
    }
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


void init(){
    FILE *fp;
    String255 strBufferSVG = "";
    String31 name = "Frieren";
    dimension p;
    p.height = 60;
    p.width = 80;

    position e, f;
    e.x = 30;
    e.y = 35;

    f.x = 120;
    f.y = 125;
    
    fprintf(fp, "%s\n", "<svg width=\"500\" height=\"500\">");
    fprintf(fp, "%s\n", drawSVGRect(strBufferSVG, 255, p, e));
    fprintf(fp, "%s\n", drawSVGRect(strBufferSVG, 255, p, f));
    fprintf(fp, "%s\n", drawSVGTextOnRectCenter(strBufferSVG, 255, p, e, name));
    fprintf(fp, "%s\n", drawSVGLineFromCenterToCenter(strBufferSVG, 255, p, e, p, f));
}


#endif