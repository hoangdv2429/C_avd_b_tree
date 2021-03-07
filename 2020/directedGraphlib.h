#ifndef directedGraphlib_h
#define directedGraphlib_h

#include "jrb.h"

typedef struct _detailVertex
{
    char *name;
    JRB indegreeTree;
    int d; //distance
    int parrent;
} * detailVertex;

typedef struct _Graph
{
    JRB edges; //contain key as id, val is a tree with egde comming out from that vertex
    JRB vertices; // also contain key as id, val is "detailVertex" (as seen in the struct above)
} * Graph;

enum color
{
	white,
	gray,
	black
};

Graph createGraph();
void addVertex(Graph graph, int id, char *name); //
char *getVertex(Graph graph, int id);            // get the vertices tree "id" that going in
void addEdge(Graph graph, int v1, int v2);       // add edge from v1 to v2
int hasEdge(Graph graph, int v1, int v2);        // check if there are any edge from v1 to v2
int indegree(Graph graph, int v, int *output);   //check indegree of the given int
int outdegree(Graph graph, int v, int *output);  //check outdegree of given int
//int getComponents(Graph graph);
void dropGraph(Graph graph);
int isDAG(Graph g);                          //check if this directed-graph has a topological order - a sequence of the vertices such that every edge is directed from earlier to later in the sequence
void TopoSort(Graph g, int *output, int *n); //Topological order
int CountVertices(Graph g); //checked
void setd(Graph g, int id, int distance);
int getd(Graph g, int id); //checked
void setparrent(Graph g, int id, int parrent);
int getparrent(Graph g, int id);
void Weight_addEdge(Graph graph, int v1, int v2, int weight); // but with weight //checked
void relax(Graph graph, int v1, int v2);
void Dijkstra(Graph g, int s);                 // Dijkstra
int getEdgeValue(Graph graph, int v1, int v2); // return INFINITIVE_VALUE if there is no egde between there vertices (checked)
int shortedPath(Graph graph, int s, int t, int *path, int *length);
//
void DFS(Graph g, int id, int *output, int *n);
#endif
