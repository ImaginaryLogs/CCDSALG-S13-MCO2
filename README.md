# CCDSALG-MCO2

# Table of Contents
- [Table of Contents](#table-of-contents)
- [1 Introduction](#1-introduction)
  - [1.1 Background](#11-background)
  - [1.2 Authors](#12-authors)
- [2 Code Documentation and Description](#2-code-documentation-and-description)
  - [2.1 Graph Implementation](#21-graph-implementation)

# 1 Introduction

> "What is the Social Network (MC02)?"

This is a simple program that uses an application of Undirected Graphs, along with Depth First Search and Breadth First Search.

## 1.1 Background
This project is created by Group 15 for their MC02 Project in their CCDSALG Class S13. This is under De La Salle University - Manila.

## 1.2 Authors and Contributions
These are university students of De La Salle University - Manila, Philippines. They are:

  1. Bunyi, Christian Joseph C. @cjbnyi - Graph Implementation
  2. Campo, Roan Cedric V. @ImaginaryLogs - GUI Implementation
  3. Chan, Enzo Rafael S. @nomu-chan - Traversals Implementation



# 2 Code Documentation and Description

## 2.1 Graph Implementation
For the graph implementation, an Adjacency List was utilized as it consumes less memory as compared to an adjacency matrix. 

The graph contains three tags/nodes: A graph tag, which contains adjacency list tags, which contains the neighboring nodes.

Given the following (tree) graph using numbers for now instead of names/Vertex IDs:

$$
\begin{array}{l}
\text{1 (Root)} \\
\quad \text{├── 2 (Branch)} \\
\quad \quad \text{├── 4 (Sub-branch)} \\
\quad \quad \quad \text{├── 7 (Leaf)} \\
\quad \quad \quad \text{└── 8 (Leaf)} \\
\quad \quad \text{└── 5 (Sub-branch)} \\
\quad \quad \quad \text{└── 9 (Leaf)} \\
\quad \text{└── 3 (Branch)} \\
\quad \quad \text{└── 6 (Sub-branch)} \\
\quad \quad \quad \text{└── 10 (Leaf)} \\
\end{array}
$$

And its adjacency list:

$$
\begin{align*}
1 & : [2, 3] \\
2 & : [1, 4, 5] \\
3 & : [1, 6] \\
4 & : [2, 7, 8] \\
5 & : [2, 9] \\
6 & : [3, 10] \\
7 & : [4] \\
8 & : [4] \\
9 & : [5] \\
10 & : [6] \\
\end{align*}
$$

In this particular graph, the Graph Tag will store the following:
- Number of Vertices (10)
- Pointer to First Adjacency List ( $1 : [2, 3]$ )
- Pointer to Last Adjacency List ( $10 : [6]$ )

Using the first adjacency list in the graph, $1 : [2, 3]$ , the Adjacency List Tag will store the following:
- Vertex ID or the Node ID/Name ( $1$ )
- Degree of the Node (2) - which will be used for the output traversals.
- Pointer to First Neighboring Node ( $2$ )
- Pointer to Last Neighboring Node ( $3$ ) 
- Pointer to the next Adjacency List Tag ( $2 : [1, 4, 5]$ )
- Parent ID - which will be used for the graphics section.
- The Layer of the Node - which will be used for the graphics section.
- Finally, a Bool - ```hasBeenExplored``` - which will be used for traversal. If the vertex has been explored/traversed, this will be marked as True. 

Using the first adjacency node in the adjacency list, $2 in 1 : [2, 3]$ , the Adjacency List Node Tag will store the following:
- Vertex ID or the Node ID/Name ( $2$ )
- Pointer to the next node ( $3$ )


## 2.2 Breadth First Search Algorithm Implementation
For the Breadth First Search (BFS), queues are utilized for recording the traversals.

The BFS will only take the graph tag and the start vertex as parameters.

Setting up the loop for traversal, the graph's vertices in the adjacency lists will all be set to unexplored. The adjacency list containing the start vertex as the main vertex will then be enqueued in the ```unexploredNodesQueue``` queue and will also be considered explored.

For the main loop, the following processes are applied:
- The queue will be dequeued, and the vertex dequeued will be printed in the output file.
- The neighboring nodes of the vertex are then processed
    - Each of the neighboring nodes are iterated. If the neighboring node has not been explored, they will first be added to an array.
    - If there are any unexplored neighboring nodes, the array will be sorted. As traversal prioritizes the lowest vertex ID (i.e. the first vertex ID in lexographical order), the array will first be sorted in increasing lexographical order (A to Z), and then they will be appended/enqueued inside the queue in that order (the lowest vertex ID first). Meanwhile, all of these vertices are marked as explored. If the appended vertex does not have a parentID, they will inherit the vertex ID of first vertex that explored it, and it will inherit the parent vertex's layer increased by one. The root node will have a parent of "ROOT".
    - If there are no remaining unexplored nodes or after enqueuing all of the neighboring nodes, the process for this iteration is finished and the array is cleared for the next iteration.

After all vertices have been explored and printed and the ```unexploredNodesQueue``` is empty, the BFS is finished.

The usage of queues here ensures that the graph will explore all of the vertices in the current depth before it goes deeper into the graph.

In addition, though not required as per the specs (that it is assumed that the information stored in the input text file are correct), the BFS can determine if an invalid neighboring node is found.


## 2.3 Depth First Search Algorithm Implementation
For the Depth First Search (DFS), stacks are utilized instead for recording the traversals. 

Similar to the BFS, the DFS will only take the graph tag and the start vertex as parameters.

Setting up the loop for traversal, the graph's vertices in the adjacency lists will all be set to unexplored. The adjacency list containing the start vertex as the main vertex will then be pushed in the ```unexploredNodesStack``` stack and will also be considered explored.

For the main loop, the following processes are applied:
- The stack will be popped, and the vertex popped will be printed in the output file.
- The neighboring nodes of the vertex are then processed
    - Each of the neighboring nodes are iterated. If the neighboring node has not been explored, they will first be added to an array.
    - If there are any unexplored neighboring nodes, the array will be sorted. As traversal prioritizes the lowest vertex ID (i.e. the first vertex ID in lexographical order), the array will first be sorted in **decreasing** lexographical order (Z to A), and then they will be appended/pushed inside the stack in that order (the highest vertex ID first). Meanwhile, all of these vertices are marked as explored.
    - If there are no remaining unexplored nodes or after pushing all of the neighboring nodes, the process for this iteration is finished and the array is cleared for the next iteration.

After all vertices have been explored and printed and the ```unexploredNodesStack``` is empty, the BFS is finished.

The array is sorted in **decreasing** order as when popping the stack, the last element placed will be popped. As we want to first pop the node with the lowest vertex ID, then the last one pushed is supposed to be the neighboring node with the highest vertex ID.

The usage of stacks here ensures that the graph will explore all of the vertices downwards in one direction (in this case, the lowest vertex ID first), then backtracks until it finds another path that has not been traversed.

Similarly, though not required, the DFS function can determine if an invalid neighboring node is found.

## 2.4 Drawing of given graph
For the drawing of any graph, an HTML file is made with the corresponding SVG graphical representation of the said graph. 

The vertices are plotted on a circle calculated using the parametric equations of circle. 
The x-coordinate is calculated by $x= cos(2\pi \cdot \frac{i}{m} )$, and the y-coordinate is calculated using $y= sin(2\pi \cdot \frac{i}{m})$.
Lines are drawn to connect each vertex to their neighboring nodes. 

A circular relationship graph was used to display a given graph so that for each point on the circle, every other possible point is visible.

The circular relationship graph has an in-built physics engine to display the graph in different ways based on the connection it has. 

## 2.5 Drawing of BFS tree
For the drawing of the BFS tree, the same HTML file of any given graph is used with the corresponding SVG graphical representation of the said BFS Tree. 

The y-position of the nodes of the tree are calculated based on the layer each node has on the Adjacency List. The higher the layer is, the more lower it be displayed on the SVG file. 
Additional, the x-position is calculated from a modified inorder walk of the said tree.

The modified inorder traversal goes through the following steps:
 - Determine whether the number of recursion, $n$, is lower than the set limit. If it is, then return early to avoid stack overflow, else increase it and pass it on.
 - It gets a given vertexID's adjency list.
 - It then adds them based on the two conditions: the given vertex is unexplored, and if the BFS-based-exploration bool is toggled, then check if the next vertex's layer information is higher than it. Those that fit the conditions are then to an exploration queue and marked as explored.
 - If the exploration queue is not empty, it recursively explores the first node as the left node recursively through another modified inorder traveral algorithm, then file prints itself and its layer information on the LAYER_INFO.txt file, then process the rest of the children nodes in recursively.
 - If it is empty, then it is a leaf node, so it should file print itself and its layer information on the same LAYER_INFO.txt file/

The output is an inorder traversal in a BFS tree. An inorder traversal of the tree tells us the correct ordering of nodes, and the order at which the information is displayed on the LAYER_INFO.txt file tells us what the x-position of nodes should be, along with the y-position of the nodes. 

The BFS GUI algorithm takes the position information of the text file and exaggerates their position in order to look correctly on the SVG file. The y-position is multiplied by a given rectangle node's height multiplied by three, while the x-position is the product of the order at which it is displayed times the sum of the rectangle node's width plus some spacing offset.

The GUI BFS tree algorithm creates lines from one vertex to its parent. Unless the given node's parent is "ROOT", it will draw an SVG line from that node to it.

## 2.6 Graph Limitations 
Our program can detect the errors stated in the specifications, such as the nonexistent start vertex input and the nonexistent file name input. Though not necessary (as the specs assume the input file is always correct), it can also detect nonexistent vertices inside an adjacency list. 

The only limitations we can think of are graphs that have too many vertices.

## 2.7 Test Cases

For the test cases, we have tested the sample test cases that results to an error, such as the nonexistent start vertex input and the nonexistent file name input. Attached in the next pages are the test cases for valid inputs.
