#include "conio.h"
#include "stdio.h"

void exch(int *array, int i, int j)
{
    int t = *(array+i);
    *(array+i) = *(array+j);
    *(array+j) = t;
}

void sort(int a[], int l, int r) {
    if (r <= l) return;
    int i = l-1, j = r;
    int p = l-1, q = r;
    while(1) {
        while (a[++i] < a[r]);
        while (a[r] < a[--j]) if (j == l) break;
        if (i >= j) break;
        exch(a, i, j);
        if (a[i]==a[r]) exch(a, ++p, i);
        if (a[j]==a[r]) exch(a, --q, j);
    }
    exch(a, i, r);
    j = i - 1;
    i = i + 1;
    int k;
    for (k = l ; k <= p; k++) exch(a, k, j--);
    for (k = r-1; k >= q; k--) exch(a, k, i++);
    sort(a, l, j);
    sort(a, i, r);
}

int main()
{
    int x[2] = {12,3};
    exch(x,0,1);
    printf("%d %d\n",x[0],x[1]);

    int p[10] = {-12,4,2,1,5,7,-8,6,9,-3};
    sort(p,0,9);

    int i;
    printf("\n");
    for(i=0;i<10;i++)
        printf("%d ",p[i]);
    printf("\n");
    getch();
    return 1;
}
