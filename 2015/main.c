#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "graph.h"

Graph input_data_from_file(char* file_name)
{
    Graph G = createGraph();
    FILE* f = fopen(file_name, "r");
    char ip[20];
    int n, id1, id2, d;

    fscanf(f, "%d\n", &n);
    for (int i = 0; i < n; ++i)
    {
        fscanf(f, "%d %s\n", &id1, ip);
        addVertex(G, id1, ip);
    }

    fscanf(f, "%d\n", &n);
    for (int i = 0; i < n; ++i)
    {
        fscanf(f, "%d %d %d\n", &id1, &id2, &d);
        addEdge(G, id1, id2, d);
        addEdge(G, id2, id1, d);
    }
    return G;
}

int main(int argc, char* argv[])
{

    if (strcmp(argv[1], "-h") == 0)
    {
        printf("C-Advanced, HK20152\n");
        return 0;
    }
        
    if (strcmp(argv[1], "-v") == 0)
    {
        Graph G = input_data_from_file(argv[2]);
        JRB iter;
        jrb_traverse(iter, G.vertices)
        {
            printf("%d %s\n", jval_i(iter->key), jval_s(iter->val));
        }
        dropGraph(G);
        return 0;
    }

    if (strcmp(argv[1], "-w") == 0)
    {
        Graph G = input_data_from_file(argv[2]);
        int id1 = atoi(argv[3]);
        int id2 = atoi(argv[4]);
        double d = getEdgeValue(G, id1, id2);
        if (d == INFINITIVE_VALUE)
            printf("-1\n");
        else
            printf("%.0lf\n", d);
        dropGraph(G);
        return 0;
    }

    if (strcmp(argv[1], "-p") == 0)
    {
        Graph G = input_data_from_file(argv[2]);
        int id1 = atoi(argv[3]);
        int id2 = atoi(argv[4]);
        int path[100], length;
        double d = shortestPath(G, id1, id2, path, &length);
        printf("%.0lf\n", d);
        for (int i = 0; i < length; ++i)
            printf("%s\n", getVertex(G, path[i]));
        dropGraph(G);
        return 0;
    }

    if (strcmp(argv[1], "-n") == 0)
    {
        Graph G = input_data_from_file(argv[2]);
        int id = atoi(argv[3]);
        int n, output[100];
        n = outdegree(G, id, output);
        printf("%d\n", n);
        for (int i = 0; i < n; ++i)
            printf("%d %s %.0lf\n", output[i], getVertex(G, output[i]), getEdgeValue(G, id, output[i]));
        dropGraph(G);
        return 0;
    }

    if (strcmp(argv[1], "-s") == 0)
    {
        Graph G = input_data_from_file(argv[2]);
        int length = argc - 3; // So luong dinh con nhap vao (argc tru di 3 tham so dau khong phai la dinh con)
        int arr[length]; // Mang chua cac dinh cua do thi con

        // Them id dinh vao mang arr (lay tu argv[3] den argv[argc-1])
        for (int i = 3, j = 0; i < argc; ++i, ++j)
            arr[j] = atoi(argv[i]); // argv[i] la kieu string -> chuyen ve kieu int

        // Sap xep cac dinh theo thu tu id tang dan (de tranh trung lap khi kiem tra so canh)
        for (int i = 0; i < length - 1; ++i)
            for (int j = i + 1; j < length; ++j)
                if (arr[i] > arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }

        // Dem so canh: duyet tung phan tu -> dem so canh co id lon hon ma no lien ket toi (vi la do thi vo huong nen de tranh trung lap)
        int edge_count = 0; // So canh
        for (int i = 0; i < length - 1; ++i) // Duyet toan bo
            for (int j = i + 1; j < length; ++j) // Duyet cac dinh co id lon hon no
            {
                if (getEdgeValue(G, arr[i], arr[j]) != INFINITIVE_VALUE)
                    edge_count++; // Tang so canh len 1
            }

        // Hien thi cac dinh co trong do thi con
        printf("%d\n", length);
        for (int i = 0; i < length; ++i)
            printf("%d %s\n", arr[i], getVertex(G, arr[i]));
        printf("%d\n", edge_count);

        // Hien thi cac canh: duyet tung phan tu -> Hien thi dinh va canh co id lon hon ma no lien ket toi (vi la do thi vo huong nen de tranh trung lap)
        double d;
        for (int i = 0; i < length - 1; ++i) // Duyet toan bo
            for (int j = i + 1; j < length; ++j) // Duyet cac dinh co id lon hon no
            {
                d = getEdgeValue(G, arr[i], arr[j]);
                if (d != INFINITIVE_VALUE)
                    printf("%d %d %.0lf\n", arr[i], arr[j], d); // In ra man hinh dinh, canh neu co lien ket
            }
        
        dropGraph(G);
        return 0;
    }
    return 0;
}