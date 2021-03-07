#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char *argv[] )  
{
    int n;
    scanf("%d", &n);
    //printf(" day la %d", n);
    fflush(stdin);
    int *arr = malloc(sizeof(int)* n);
    char *input = malloc(sizeof(char)*50);
    fgets(input, 50, stdin);
    //printf("\n%s\n", input);

   char *token = strtok(input, " ");
    // loop through the string to extract all other tokens
    printf("%s\n", token);
    while (token != NULL)
    {
        
        printf(" %d\n", atoi(token));
        
        token = strtok(NULL, " ");
    }
    

    return 0;
}