#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directedGraphlib.h"
#include "fields.h"

void input(Graph classes, int argc, int **argv)
{
    char **matrix;
    int nlines, i, n;
    IS is;

    /* Error check the command line. */

    if (argc != 2)
    {
        fprintf(stderr, "usage: tailany1 n\n");
        exit(1);
    }
    if (sscanf(argv[1], "%d", &n) == 0 || n <= 0)
    {
        fprintf(stderr, "usage: tailany1 n\n");
        fprintf(stderr, "       bad n: %s\n", argv[1]);
        exit(1);
    }

    /* Allocate the array */

    matrix = (char **)malloc(sizeof(char *) * n);
    if (matrix == NULL)
    {
        perror("malloc");
        exit(1);
    }

    is = new_inputstruct(NULL);
    if (is == NULL)
    {
        perror("stdin");
        exit(1);
    }

    nlines = 0;
    while (get_line(is) >= 0)
    {
        //     if (nlines >= n)
        //         free(lastn[nlines % n]);
        //     lastn[nlines % n] = strdup(is->text1);
        //     nlines++;
        // }
        for (i = 0; i < is->NF; i++)
        {
            printf("%d: %s\n", is->line, is->fields[i]);
            matrix[i][is->line - 1] = is->fields[i];
        }
    }

    //all vertices in matrix added
    for (int i = 0; i < is->NF; i++)
    {
        addVertex(classes, i, i + '0');
    }

    for (int i = 0; i < is->NF; i++)
    {
        for (int j = 0; j < is->NF; j++)
        {
            if (i == j)
            {
            }
            else
            {
                Weight_addEdge(classes, i, j, matrix[i][j]);
            }
        }
    }
}

void printMatrix(Graph graph)
{
    int i, j, numOfV;
    numOfV = CountVertices(graph);

    for (i = 0; i < numOfV; i++)
    {
        for (j = 0; j < numOfV; j++)
        {
            if (hasEdge(graph, i, j))
                printf("\t%d", getEdgeValue(graph, i, j));
            else
            {
                printf("\t0");
            }
        }
        printf("\n");
    }
}

void num_of_ver_and_arc(Graph graph)
{
    int i, j, numOfV, numofA = 0;
    numOfV = CountVertices(graph);

    for (i = 0; i < numOfV; i++)
    {
        for (j = 0; j < numOfV; j++)
        {
            if (hasEdge(graph, i, j))
                numofA++;
        }
    }
    printf("Num of vertices and ars is: %d %d", numOfV, numofA);
}

void addjecent(Graph graph)
{
    int id;
    printf("name of room: ");
    scanf("%d", &id);
    int *output;
    int numofV = CountVertices(graph);
    output = malloc(sizeof(int) * numofV);

    int out = outdegree(graph, id, output);
    printf("\nthis room connect to: ");
    for (int i = 0; i < out; i++)
    {
        printf("%d ", output[i]);
    }
}


int main(int argc, char **argv)
{
    return 0;
}