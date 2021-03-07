#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directedGraphlib.h"

void Input(Graph products)
{
    FILE *fp, *fp2;
    int num;
    char str[100];
    char *filename1 = "orderhistory.txt";
    char *filename = "products.txt";
    char *token = malloc(sizeof(char));
    int order[100];

    fp = fopen(filename, "r");
    fp2 = fopen(filename1, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
    }
    if (fp2 == NULL)
    {
        printf("Could not open file %s", filename1);
    }

    while (!feof(fp))
    {   
        fscanf(fp, "%d %s\n", &num, str);
        addVertex(products, num, str);
        printf("%d %6s\n", num, str);
    }
    while (fgets(str, 100, fp2) != NULL)
    {
        int n = 0;

        char *token = strtok(str, " ");
        while (token != NULL)
        {
            order[n] = atoi(token);
            printf("\n%d\n", atoi(token));
            token = strtok(NULL, " ");
            n++;
        }

        for (int i = 0; i < n; i++)

        {   
            Weight_addEdge(products, order[i], order[i + 1], 1);
            Weight_addEdge(products, order[i + 1], order[i], 1);
        }
    }
    fclose(fp);
    fclose(fp2);
}

int main()
{
    int choice;
    printf("Welcome to \"Product management\". \n");
    Graph products = createGraph();
    printf("Menu:\n1) print all products\n2) print orderhistory\n3) The connection between the two products\n4) products that have connection with this one \n5) (randomly) show products that connect between these products\n ");
    printf("Choice: ");
    scanf("%d%*c", &choice);

    Input(products);

    switch (choice)
    {
    case 1:
        printf("Cac san pham gom\n");

        break;

    default:
        break;
    }
}