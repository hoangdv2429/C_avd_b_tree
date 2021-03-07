#ifndef graphlib_h
#define graphlib_h
#include"jrb.h"
typedef JRB graph;

graph creategraph();
void addedge(graph graph, int v1, int v2);
int adjacent(graph graph, int v1, int v2);
int incidentedges(graph graph, int vertex, int* output); 
void dropgraph(graph graph);
#endif
