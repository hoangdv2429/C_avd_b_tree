#include "directedGraphlib.h"
#include <stdio.h>

int main(){
  int i, n, output[100];
  Graph g = createGraph();
  char s1[] = "station 1";
  char s2[] = "station 2";
  char s3[] = "station 3";
  //printf("\n%s\n",s);
  addVertex(g,1,s1);
  addVertex(g,2,s2);
  addVertex(g,3,s3);
  char *out = getVertex(g,1);
  printf("\nname of v1: %s\n",out);
  addEdge(g,1,2);
  addEdge(g,1,3);
  
  if(hasEdge(g,1,2)==1)
	printf("\nv1 v2 has edge\n");
  else
	printf("\nv1 v2 has no edge\n");
  
  int innum = indegree(g,2,output);
  printf("\nindegree of v2: \n");
  for(i=0;i<innum;i++)
  {
	  printf(" %d ",output[i]);
  }
  
  int outnum = outdegree(g,2,output);
  printf("\noutdegree of v2: \n");
  for(i=0;i<outnum;i++)
  {
	  printf(" %d ",output[i]);
  }

  innum = indegree(g,1,output);
  printf("\nindegree of v1: \n");
  for(i=0;i<innum;i++)
  {
	  printf(" %d ",output[i]);
  }

  outnum = outdegree(g,1,output);
  printf("\noutdegree of v1: \n");
  for(i=0;i<outnum;i++)
  {
	  printf(" %d ",output[i]);
  }
  printf("\n");
  dropGraph(g);
}
