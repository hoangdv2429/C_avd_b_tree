#include <stdio.h>
#include <stdlib.h>
#include "graphlib.h"
graph creategraph()
{
  return make_jrb();
}
void addedge(graph graph, int v1, int v2)
{
  JRB node = jrb_find_int(graph, v1);
  JRB tree;
  //add node in to the tree
  //if Node v1 is not found, create new tree, insert v1 and new tree into the graph.
  //then add v2 (NULL) into the tree
  //if Node v1 is found, add v2 NUll, into the tree of v1
  if (node == NULL)
  {
    tree = make_jrb();
    jrb_insert_int(graph, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, JNULL);
  }
  else
  {
    tree = (JRB)(node->val).v;
    jrb_insert_int(tree, v2, JNULL);
  }
  node = jrb_find_int(graph, v2);
  if (node == NULL)
  {
    tree = make_jrb();
    jrb_insert_int(graph, v2, new_jval_v(tree));
    jrb_insert_int(tree, v1, JNULL);
  }
  else
  {
    tree = (JRB)(node->val).v;
    jrb_insert_int(tree, v1, JNULL);
  }
  //do the same for v2
}
int adjacent(graph graph, int v1, int v2)
{
  JRB tree, node = jrb_find_int(graph, v1);
  if (node == NULL)
    return 0;
  tree = (JRB)(node->val).v;
  if (jrb_find_int(tree, v2) == NULL)
    return 0;
  return 1;
}
int incidentedges(graph graph, int vertex, int *output)
{
  int num = 0;
  JRB tree, node = jrb_find_int(graph, vertex);
  if (node == NULL)
    return 0;
  tree = (JRB)(node->val).v;
  jrb_traverse(node, tree)
  {
    output[num++] = (node->key).i;
  }
  return num;
}
void dropgraph(graph graph)
{
  JRB node;
  jrb_traverse(node, graph)
  {
    jrb_free_tree((JRB)jval_v(node->val));
  }
  jrb_free_tree(graph);
}
