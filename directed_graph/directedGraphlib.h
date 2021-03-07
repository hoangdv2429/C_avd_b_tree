#ifndef directedGraphlib_h
#define directedGraphlib_h

#include "jrb.h"

typedef struct _detailVertex{
char *name;
JRB indegreeTree;
} *detailVertex;


typedef struct _Graph{
JRB edges;
JRB vertices;
} *Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
//int getComponents(Graph graph);
void dropGraph(Graph graph);

#endif
