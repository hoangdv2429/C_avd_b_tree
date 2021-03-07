#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "jrb.h"
#include "dllist.h"
#include <stdlib.h>
#define INFINITIVE_VALUE 1000000
#define MAX 1000
typedef struct
{
	JRB edges;
	JRB vertices;
	JRB Pagerank;
} Graph;
Graph createGraph()
{
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
	g.Pagerank = make_jrb();
	return g;
}

void addVertex(Graph g, int id, char *name)
{
	JRB node = jrb_find_int(g.vertices, id);
	if (node == NULL)
		jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}
char *getVertex(Graph g, int id)
{
	JRB node = jrb_find_int(g.vertices, id);
	if (node == NULL)
		return NULL;
	else
		return jval_s(node->val);
}
int hasEdge(Graph graph, int v1, int v2)
{
	JRB node, tree;
	node = jrb_find_int(graph.edges, v1);
	if (node == NULL)
		return 0;
	tree = (JRB)jval_v(node->val);
	if (jrb_find_int(tree, v2) == NULL)
		return 0;
	else
		return 1;
}
double getEdgeValue(Graph graph, int v1, int v2)
{
	JRB node, tree;
	node = jrb_find_int(graph.edges, v1);
	if (node == NULL)
		return INFINITIVE_VALUE;
	tree = (JRB)jval_v(node->val);
	node = jrb_find_int(tree, v2);
	if (node == NULL)
		return INFINITIVE_VALUE;
	else
		return jval_d(node->val);
}
void addEdge(Graph graph, int v1, int v2, double weight)
{
	JRB node, tree;
	if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
	{
		node = jrb_find_int(graph.edges, v1);
		if (node == NULL)
		{
			tree = make_jrb();
			jrb_insert_int(graph.edges, v1, new_jval_v(tree));
			jrb_insert_int(tree, v2, new_jval_d(weight));
		}
		else
		{
			tree = (JRB)jval_v(node->val);
			jrb_insert_int(tree, v2, new_jval_d(weight));
		}
	}
}
int indegree(Graph graph, int v, int *output)
{
	JRB tree, node;
	int total = 0;
	jrb_traverse(node, graph.edges)
	{
		tree = (JRB)jval_v(node->val);
		if (jrb_find_int(tree, v))
		{
			output[total] = jval_i(node->key);
			total++;
		}
	}
	return total;
}
int outdegree(Graph graph, int v, int *output)
{
	JRB tree, node;
	int total;
	node = jrb_find_int(graph.edges, v);
	if (node == NULL)
		return 0;
	tree = (JRB)jval_v(node->val);
	total = 0;
	jrb_traverse(node, tree)
	{
		output[total] = jval_i(node->key);
		total++;
	}
	return total;
}
int DAG(Graph graph)
{
	int visited[1000];
	int n, output[100], i, u, v, start;
	Dllist node, stack;
	JRB vertex;
	jrb_traverse(vertex, graph.vertices)
	{
		memset(visited, 0, sizeof(visited));
		start = jval_i(vertex->key);
		stack = new_dllist();
		dll_append(stack, new_jval_i(start));
		while (!dll_empty(stack))
		{
			node = dll_last(stack);
			u = jval_i(node->val);
			dll_delete_node(node);
			if (!visited[u])
			{
				visited[u] = 1;
				n = outdegree(graph, u, output);
				for (i = 0; i < n; i++)
				{
					v = output[i];
					if (v == start)
						return 0;
					if (!visited[v])
						dll_append(stack, new_jval_i(v));
				}
			}
		}
	}
	return 1;
}
double shortestPath(Graph G, int s, int t, int *path, int *length)
{
	int previous[MAX];	  // Lưu các node trước đó, dùng để tìm đường đi (path)
	double distance[MAX]; // Khoảng cách ngắn nhất giữa S đến các đỉnh
	int add[MAX];		  // Kiểm tra node đã visited
	Dllist queue = new_dllist();
	Dllist iter;
	Dllist node;
	int u;

	for (int i = 0; i < MAX; ++i)
		distance[i] = INFINITIVE_VALUE;
	distance[s] = 0;
	memset(add, 0, sizeof(int) * MAX);
	dll_append(queue, new_jval_i(s));
	add[s] = 1;

	while (!dll_empty(queue))
	{
		// Lấy ra đỉnh có khoảng cách gần s nhất trong queue
		double min = INFINITIVE_VALUE;
		dll_traverse(iter, queue)
		{
			u = jval_i(iter->val);
			if (min > distance[u])
			{
				min = distance[u];
				node = iter;
			}
		}
		u = jval_i(node->val);
		dll_delete_node(node);

		if (u == t)
			break;

		// Cập nhật lại khoảng cách của các đỉnh kề u so với s
		// So khoảng cách d[u] và d[v] + c(u, v)
		int n, v, w, output[MAX];
		n = outdegree(G, u, output);
		for (int i = 0; i < n; ++i)
		{
			v = output[i];
			w = getEdgeValue(G, u, v);
			if (distance[v] > distance[u] + w)
			{
				distance[v] = distance[u] + w;
				previous[v] = u;
			}

			if (!add[v])
			{
				add[v] = 1;
				dll_append(queue, new_jval_i(v));
			}
		}
	}

	// Tìm đường đi (path), số đỉnh đi qua (length) và tổng quãng đường (return) (từ previous)
	int n, tmp[MAX];
	if (distance[t] != INFINITIVE_VALUE)
	{
		// Path
		tmp[0] = t;
		n = 1;
		u = t;
		while (u != s)
		{
			u = previous[u];
			tmp[n] = u;
			n++;
		}

		*length = n;
		// Reverse
		for (int i = n - 1; i >= 0; --i)
			path[n - i - 1] = tmp[i];
	}

	free_dllist(queue);
	return distance[t];
}
void dropGraph(Graph graph)
{
	JRB node, tree;
	jrb_traverse(node, graph.edges)
	{
		tree = (JRB)jval_v(node->val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(graph.edges);
	jrb_free_tree(graph.vertices);
}
void Menu()
{
	printf("*************MENU*************\n");
	printf("1. In so luongwebpage va url\n");
	printf("2. pagerank 1 lan\n");
	printf("3. pagerank m lan\n");
	printf("4. In ra so luong webpage va spampot\n");
	printf("5. In ra khoang cach nho nhat\n");
	printf("6. Thoat chuong trinh\n");
}
void intputwebpage(Graph G, char *filename, int *n)
{
	char str[250];
	int id;

	FILE *f;
	f = fopen(filename, "r");
	fscanf(f, "%d", n);
	for (int i = 0; i < *n; i++)
	{
		fscanf(f, "%s %d", str, &id);
		addVertex(G, id, str);
	}
}

void InputpageConnection(Graph G, char *filename, int *soluong)
{
	FILE *f = fopen(filename, "r");
	char str[200];
	int id1;
	int id2;
	int arr[100];
	int n;
	int i;
	fscanf(f, "%d", soluong);
	for (int j = 0; j < *soluong; j++)
	{
		fgets(str, 101, f);
		i = 0;
		char *token = strtok(str, " ");
		while (token != NULL)
		{
			arr[i] = atoi(token);
			i++;
			token = strtok(NULL, " ");
		}
		n = i;
		id1 = arr[0];

		for (int k = 1; k < n; k++)
		{
			id2 = arr[k];
			addEdge(G, id1, id2, 1);
		}
	}
	fclose(f);
}
void func(Graph G)
{
	JRB node;
	int total1;
	int total2;
	int output1[100];

	int max;
	int min;
	min = INFINITIVE_VALUE;
	max = 0;
	jrb_traverse(node, G.vertices)
	{
		total1 = indegree(G, jval_i(node->key), output1);
		if (total1 > max)
			max = total1;
		;

		if (total1 < min)
			min = total1;
	}
	jrb_traverse(node, G.vertices)
	{
		total1 = indegree(G, jval_i(node->key), output1);

		if (total1 == max)
			printf("Nhieu lien ket toi nhat %s\n", getVertex(G, jval_i(node->key)));
		if (total1 == min)
			printf("It lien ket toi nhat %s\n", getVertex(G, jval_i(node->key)));
	}
}
void updatedistance(Graph G, int id1, int id2, double d)
{
	JRB node, tree, node1;
	node = jrb_find_int(G.edges, id1);
	tree = (JRB)jval_v(node->val);
	node1 = jrb_find_int(tree, id2);

	jrb_delete_node(node1);
	jrb_insert_int(tree, id2, new_jval_d(d));
}
/*void InputpageConnection2(Graph G,char *filename,int *soluong,int lanthu){
	FILE* f = fopen(filename, "r");
   char str[200];
   int id1;
   int id2;
   int arr[100];
   int n;
   int i;
   double d[100];
   int output[100];
   
	fscanf(f,"%d",soluong);
   for(int j=0;j<*soluong;j++){
       fgets(str,101,f);
       i=0;
       char *token = strtok(str," ");
       while(token!=NULL){
           arr[i]=atoi(token);
           i++;
           token = strtok(NULL," ");
       }
       n=i;
	   id1=arr[0];
	  
	   d[0]=0;
	   for(int k=1;k<n;k++){
		   id2=arr[k];
		    if(lanthu==0){
		JRB tree = jrb_find_int(G.Pagerank)
		jrb_insert_int(tree,id2,)   
	   }
		  
		   
		   d[k]=getEdgeValue(G,id1,id2);
			d[k]=d[k]/(outdegree(G,id2,output));
			d[0]=d[k]+d[0];

		   
	   }
	   JRB tree = (G.Pagerank);
	   jrb_insert_int(tree,id1,new_jval_d(d[0]));
	   
	   
	   
}
}
}*/

void funt2(Graph graph)
{
	
}

void func4(Graph G)
{
	JRB node;
	int total1;
	int total2, total3, total4;
	int output1[100];
	int output2[100];
	int max;
	int min;
	int numof1 = 0;
	int numof2 = 0;
	min = INFINITIVE_VALUE;
	max = 0;
	jrb_traverse(node, G.vertices)
	{
		total1 = indegree(G, jval_i(node->key), output1);
		total3 = outdegree(G, jval_i(node->key), output2);
		if (total1 > 0 && total3 == 0)
			numof1++;
		if (total1 == 0 && total3 >0)
		{
			numof2++;
		}		
	}
	
	printf("co lien ket den nhung khong co lien ket di: %d\n", numof1);
	printf("co lien ket di nhung khong co lien ket den (spambot): %d\n", numof2);
	
}



void func5(Graph G)
{
	int id1, id2;
	printf("Nhap id1");
	scanf("%d", &id1);
	printf("Nhap id2");
	scanf("%d", &id2);
	int path[1000];
	int lenght;

	double d = shortestPath(G, id1, id2, path, &lenght);
	if (id1 == id2)
	{
		printf("-1");
	}
	else
	{
		printf(" ");
	}
}
int main()
{
	int choice;
	Graph G = createGraph();
	JRB node;
	int n;
	do
	{
		Menu();
		printf("MENU\n");
		printf(">>>> ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			intputwebpage(G, "webpages.txt", &n);
			printf("1. In so luong webpage va url\n");
			printf("2. In ra webpages nhieu lien ket nhat va it lien ket toi nhat\n");
			int choice1;
			scanf("%d", &choice1);
			if (choice1 == 1)
			{
				printf("%d\n", n);
				jrb_traverse(node, G.vertices)
				{
					printf("%s %d\n", getVertex(G, jval_i(node->key)), (jval_i(node->key)));
				}
				printf("\n");
			}
			if (choice1 == 2)
			{

				InputpageConnection(G, "pageConnections.txt", &n);
				func(G);
			}

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			func4(G);
			break;
		case 5:
			func5(G);
			break;
		case 6:
			return 0;
			break;
		}
	} while (choice != 6);
}
