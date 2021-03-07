#include <stdio.h>
#include <stdlib.h>

// int main()
// {
    // int n;
    // printf("Enter number of input: ");
    // scanf("%d%*c", &n);

    // int *a = (int *)malloc(sizeof(int) * n);

    //     for (int i = 0; i < n; i++)
    // {
    //     printf("enter %d: ", i+1);
    //     scanf("%d", a+i);
    //     printf("%d\n", *(a + i));
    // }

    // free(a);


void allocate_mem(int ***mt, int m, int n){
    //#Allocate memory for the matrix

    for (int i = 0; i < m; i++){
        *(mt+i) = (int**)malloc(sizeof(int*)*m);
        for (int j = 0; j < n; j++){
            *(*(mt+i)+j) = (int*)malloc(sizeof(int)*n);
        }
    }
}


void input(int **mt, const int m, const int n){
    //#Input elements of the matrix
    printf("day la m %d day la n %d\n", m, n);
    printf("Input the matrix: \n");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("Enter a[%d][%d]: ", i,j);
            scanf("%d", *(mt+i)+j);
        }
    }
}

void output(int **mt, int m, int n){
    //# Print all elements of the matrix
    
    printf("The matrix is: ");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("\t%d", *(*(mt+i)+j));
            if (j == (n-1)){
                printf("\n");
            }
        }
    }
}

int process(int **mt, int m, int n){
    int tong = 0;
    //# Calculate the sum of all even elements in the matrix
    
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (*(*(mt+i)+j) % 2 == 0){
                tong += *(*(mt+i)+j);
            }
        }
    }
    
    return tong;
}

void free_mem(int **mt, int m, int n){
    //# Free memory
    
    free(mt);
}

int main(){
    int m, n, **mt;
    printf("Enter m, n = ");
    scanf("%d%d", &m, &n);
    //printf("%d %d", m, n);
    allocate_mem(&mt, m, n);
    input(mt, m, n);
    output(mt, m, n);
    printf("The sum of all even elements is %d", process(mt, m, n));
    free_mem(mt, m, n);
    return 0;
}
