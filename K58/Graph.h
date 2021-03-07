#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h" //int linked list
#include "libfdr/fields.h"

#define INFINITIVE_VALUE 10000000

typedef struct{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2, int weight);
int getEdgeValue(Graph graph, int v1, int v2); // return INFINITIVE_VALUE if no edge between v1 and v2
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
int shortestPath(Graph graph, int s, int t, int *path, int *length);
void addVertex(Graph graph, int id, char *name);
char *getVertex(Graph graph, int id);
int hasEdge(Graph graph, int v1, int v2);
int DAG(Graph graph);
void topologicalSort(Graph graph, int *output, int *n);
void dropGraph(Graph graph);
