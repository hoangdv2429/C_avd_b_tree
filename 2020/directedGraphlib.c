#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directedGraphlib.h"
#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 10000000
#define MAX_V 50

Graph createGraph()
{
	Graph g = (Graph)malloc(sizeof(struct _Graph));
	if (g == NULL)
	{
		printf("NULL, can not allocate mem, abort...\n");
		return NULL;
	}
	g->vertices = make_jrb();
	g->edges = make_jrb();
	return g;
}

void addVertex(Graph graph, int id, char *name)
{
	if (getVertex(graph, id) != NULL)
		return;

	JRB vertices = graph->vertices;
	JRB edges = graph->edges;
	JRB tree;

	//update vertex
	detailVertex iver = (detailVertex)malloc(sizeof(struct _detailVertex));
	if (iver == NULL)
	{
		printf("NULL, can not allocate mem, abort...\n");
		return;
	}
	iver->name = strdup(name);
	//update vertices
	iver->indegreeTree = make_jrb();
	jrb_insert_int(vertices, id, new_jval_v(iver));

	//update edge (add new "tree" to the newly added id)
	tree = make_jrb();
	jrb_insert_int(edges, id, new_jval_v(tree));
}

char *getVertex(Graph graph, int id)
{
	JRB vnode = jrb_find_int(graph->vertices, id);

	if (vnode == NULL)
		return NULL;

	detailVertex iver = (detailVertex)vnode->val.v;

	return iver->name;
}

void addEdge(Graph graph, int v1, int v2)
{
	if (hasEdge(graph, v1, v2) == 1)
		return;
	JRB enode = jrb_find_int(graph->edges, v1);
	JRB vnode = jrb_find_int(graph->vertices, v2);
	JRB tree;
	if ((enode == NULL) || (vnode == NULL))
	{
		printf("vertex not found\n");
		return;
	}
	// add v2 to the "edge" tree of v1 (this tree is a set of all edges coming out from v1)
	tree = (JRB)(enode->val).v;
	jrb_insert_int(tree, v2, JNULL);
	// add v1 to the "indegree" tree of v2 (this tree is a set of all edges that connect to v2)
	detailVertex iver = (detailVertex)vnode->val.v;
	tree = iver->indegreeTree;
	jrb_insert_int(tree, v1, JNULL);
}

int hasEdge(Graph graph, int v1, int v2)
{
	JRB enode = jrb_find_int(graph->edges, v1);
	JRB tree;
	if (enode == NULL)
	{
		printf("vertex not found\n");
		return 0;
	}
	tree = (JRB)(enode->val).v;
	if (jrb_find_int(tree, v2) != NULL)
	{
		printf("already have an edge from %d to %d.\n", v1, v2);
		return 1;
	}

	else
		return 0;
}

int indegree(Graph graph, int v, int *output)
{
	JRB vnode = jrb_find_int(graph->vertices, v);
	JRB tree, node;
	int innum = 0;

	if (vnode == NULL)
	{
		printf("vertex not found\n");
		return 0;
	}
	detailVertex iver = (detailVertex)vnode->val.v;
	tree = iver->indegreeTree;
	//traverse tree
	jrb_traverse(node, tree)
	{
		output[innum] = node->key.i;
		innum++;
		//printf("\nnumber innum:%d\n",output[innum-1]);
	}
	return innum;
}

int outdegree(Graph graph, int v, int *output)
{
	JRB enode = jrb_find_int(graph->edges, v);
	JRB tree, node;
	int outnum = 0;

	if (enode == NULL)
	{
		printf("vertex not found\n");
		return 0;
	}

	tree = (JRB)(enode->val).v;
	//traverse tree
	jrb_traverse(node, tree)
	{
		output[outnum] = node->key.i;
		outnum++;
		//printf("\nnumber innum:%d\n",output[outnum-1]);
	}
	return outnum;
}

void dropGraph(Graph graph)
{
	JRB node, innode;
	detailVertex detailnode;

	jrb_traverse(node, graph->edges)
	{
		jrb_free_tree((JRB)jval_v(node->val));
	}
	jrb_free_tree(graph->edges);

	jrb_traverse(node, graph->vertices)
	{
		detailnode = (detailVertex)node->val.v;
		free(detailnode->name);
		jrb_free_tree((JRB)detailnode->indegreeTree);
	}
	jrb_free_tree(graph->vertices);

	free(graph);
}

int isDAG(Graph g)
{
	// DFS from each "start" vertex, if that vertex get visited again then this graph is not DAG.
	int n, u, v, start;
	int output[100], visited[1000];

	Dllist node, stack;
	JRB vertex;

	jrb_traverse(vertex, (*g).vertices)
	{
		memset(visited, 0, sizeof(visited));

		start = jval_i(vertex->key);

		stack = new_dllist();

		visited[start] = 1;

		dll_append(stack, new_jval_i(start));

		while (!dll_empty(stack))
		{
			node = dll_last(stack);
			u = jval_i(node->val);
			dll_delete_node(node);
			n = outdegree(g, u, output);
			for (int i = 0; i < n; i++)
			{
				v = output[i];
				if (v == start) // found the loop
					return 0;
				if (!visited[v])
				{
					dll_append(stack, new_jval_i(v));
					visited[v] = 1;
				}
			}
		}
	}
	return 1;
}

void TopoSort(Graph g, int *output, int *n)
{
	int indeg[1000], tmp[100], m, i, u, v, cnt = 0;
	JRB vertex;
	Dllist node, queue;

	queue = new_dllist();
	//check if this graph have any loop
	if (!isDAG(g))
	{
		printf("Given graph is not DAG.\n");
		return;
	}
	//Find all vertices with zero indegree, put it into queue
	jrb_traverse(vertex, (*g).vertices)
	{
		u = jval_i(vertex->key);
		indeg[u] = indegree(g, u, tmp);
		if (!indeg[u])
			dll_append(queue, new_jval_i(u));
	}

	while (!dll_empty(queue))
	{
		node = dll_first(queue);
		u = jval_i(node->val);
		dll_delete_node(node);

		output[cnt++] = u;
		m = outdegree(g, u, tmp);
		for (i = 0; i < m; i++)
		{
			v = tmp[i];
			indeg[v]--;
			if (!indeg[v])
				dll_append(queue, new_jval_i(v));
		}
	}
	*n = cnt;
}

//

int CountVertices(Graph g) //worked
{
	JRB node;
	int n = 0;
	jrb_traverse(node, g->vertices)
	{
		n++;
	}

	return n;
}

void Weight_addEdge(Graph graph, int v1, int v2, int weight)
{
	if (hasEdge(graph, v1, v2) == 1)
		return;
	JRB enode = jrb_find_int(graph->edges, v1);
	JRB vnode = jrb_find_int(graph->vertices, v2);
	JRB tree;
	if ((enode == NULL) || (vnode == NULL))
	{
		printf("vertex not found\n");
		return;
	}
	Jval Jweight;
	Jweight = new_jval_i(weight);
	// add v2 to the v1 tree (with weight) (this tree is a set of all edges coming out from v1)
	tree = (JRB)(enode->val).v;
	jrb_insert_int(tree, v2, Jweight);
	// add v1 to the "indegree" tree of v2 (this tree is a set of all edges that connect to v2)
	detailVertex iver = (detailVertex)vnode->val.v;
	tree = iver->indegreeTree;
	jrb_insert_int(tree, v1, Jweight);
};

void setd(Graph g, int id, int distance)
{
	JRB node;
	node = jrb_find_int(g->vertices, id);
	detailVertex iver = (detailVertex)node->val.v;
	iver->d = distance;
}

void setparrent(Graph g, int id, int parrent)
{
	JRB node;
	node = jrb_find_int(g->vertices, id);
	detailVertex iver = (detailVertex)node->val.v;
	iver->parrent = parrent;
}

int getd(Graph g, int id)
{
	JRB node;
	node = jrb_find_int(g->vertices, id);
	detailVertex iver = (detailVertex)node->val.v;
	return iver->d;
}

int getparrent(Graph g, int id)
{
	JRB node;
	node = jrb_find_int(g->vertices, id);
	if (node == NULL)
	{
		//printf("Vertex not found\n");
		return 999;
	}

	detailVertex iver = (detailVertex)node->val.v;
	return iver->parrent;
}

void relax(Graph graph, int v1, int v2) //starting from v1, improve the shortest path to v2 found so far by going through u
{
	JRB u, v;
	u = jrb_find_int(graph->vertices, v1);
	v = jrb_find_int(graph->vertices, v2);

	if (u != NULL && v != NULL && getd(graph, v2) > (getd(graph, v1) + getEdgeValue(graph, v1, v2)))
	{
		setd(graph, v2, getd(graph, v1) + getEdgeValue(graph, v1, v2));
		setparrent(graph, v2, v1);
	}
}

int getEdgeValue(Graph graph, int v1, int v2) // (worked) return INFINITIVE_VALUE if there is no egde between there vertices
{
	JRB enode = jrb_find_int(graph->edges, v1);
	JRB tree;
	JRB tmp;
	if (enode == NULL)
	{
		printf("vertex not found\n");
		return INFINITIVE_VALUE;
	}
	tree = (JRB)(enode->val).v;
	tmp = jrb_find_int(tree, v2);
	if (jrb_find_int(tree, v2) != NULL)
	{

		int weight = jval_i(tmp->val);
		return weight;
	}
	else
		return INFINITIVE_VALUE;
}

void Dijkstra(Graph g, int s)
{
	//
	int *output, *n; //topological order to put in queue
	int u;
	n = (int *)(malloc(sizeof(int)));
	output = (int *)malloc(sizeof(int) * CountVertices(g));
	Dllist tmp, queue;
	queue = new_dllist();
	//
	JRB node;
	JRB s_vertex;
	s_vertex = jrb_find_int(g->vertices, s);

	jrb_traverse(node, g->vertices)
	{
		detailVertex iver = (detailVertex)node->val.v;
		iver->d = INFINITIVE_VALUE;
		iver->parrent = -99;
	}

	setd(g, s, 0);
	setparrent(g, s, s);

	if (isDAG(g))
	{
		TopoSort(g, output, n);
	}
	else
	{
		DFS(g, s, output, n);
	}

	for (int i = 0; i < *n; i++)
	{
		dll_append(queue, new_jval_i(output[i])); //insert at the end of the queue
	}

	while (!dll_empty(queue))
	{
		int *OutOfAnEdge = (int *)malloc(sizeof(int) * 100);
		tmp = dll_first(queue);
		u = jval_i(tmp->val);
		dll_delete_node(tmp);

		JRB VertexU = jrb_find_int(g->edges, u);
		int out = outdegree(g, u, OutOfAnEdge);
		for (int i = 0; i < out; i++)
		{
			relax(g, u, OutOfAnEdge[i]);
		}
	}
}

int shortedPath(Graph graph,const int s, int t, int *path, int *length) //call after Djisktra
{
	JRB u_s;
	JRB v_t;
	v_t = jrb_find_int(graph->vertices, t);
	detailVertex iver = (detailVertex)v_t->val.v;
	*length = iver->d;
	//printf("This length is: %d\n", *length);
	int recursive = t;
	int n = 0;

	do
	{
		path[n] = recursive;
		n++;
		//printf("res: %d num of path: %d\n", recursive, n - 1);
		recursive = getparrent(graph, recursive);
		if (recursive == 999)
		{
			break;
		}
	} while (recursive != s);

	path[n] = s; //fix path[n] not located

	if (*length == INFINITIVE_VALUE)
	{
		printf("Can't reach %s from %s\n", getVertex(graph, t), getVertex(graph, s));
		return 0;
	}
	else if (*length == 0)
	{
		return 2; //mean itself
	}

	printf("Shortest distance from %s to %s is: %d\n", getVertex(graph, s), getVertex(graph, t), *length);

	for (int i = n; i > 0; i--)
	{
		//printf("%d i: %d\n", path[i], i);
		printf("%s -> ", getVertex(graph, path[i]));
	}
	printf("%s \n", getVertex(graph, t));

	return 1;
}

//BFS

//DFS

enum color *initColors()
{
	enum color *colors = (enum color *)malloc(MAX_V * sizeof(enum color));
	for (int i = 0; i < MAX_V; i++)
	{
		colors[i] = white;
	}
	return colors;
}
int *initList()
{
	int *list = (int *)malloc(sizeof(int) * MAX_V);
	for (int i = 0; i < MAX_V; i++)
	{
		list[i] = -1;
	}
	return list;
}

void DFS_visit(Graph g, JRB u, enum color *colors, int *adjList, int *time, int *output) // u is a node find from vertices tree
{
	(*time)++;
	int *surround = (int *)malloc(sizeof(int) * 50);
	int size;
	colors[jval_i(u->key)] = gray;

	size = outdegree(g, jval_i(u->key), surround);
	for (int i = 0; i < size; i++)
	{
		//printf(" before adj %d\n", surround[i]);
		if (colors[surround[i]] == white)
		{
			output[*time] = surround[i];
			//printf("after check %d\n", surround[i]);
			adjList[surround[i]] = jval_i(u->key);
			DFS_visit(g, jrb_find_int(g->edges, surround[i]), colors, adjList, time, output);
		}
	}
	
	colors[jval_i(u->key)] = black;
	free(surround);
}

void DFS(Graph g, int s, int *output, int *n)
{
	enum color *colors = initColors();
	int *adjList = initList();
	int *time = (int *)malloc(sizeof(int));
	JRB tmp = jrb_find_int(g->edges, s);
	if (tmp == NULL)
	{
		printf("\nThere is no such vertex.\n");
	}
	else
	{
		*time = 0;
		output[*time] = s;
		DFS_visit(g, tmp, colors, adjList, time, output);
	}
	*n = *time;
	free(colors);
	free(adjList);
	free(time);
}
