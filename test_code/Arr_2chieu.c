#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    char** arrStr;
    arrStr = malloc(sizeof(char*)*50);
    arrStr[0] = malloc(sizeof(char)*50);
    arrStr[1] = malloc(sizeof(char)*50);
    strcpy(arrStr[0], "hello");
    strcpy(arrStr[1], "hello");
    printf("%s\n", arrStr[0]);
    printf("%s\n", arrStr[1]);
    

    int** arrInt;
    arrInt = malloc(sizeof(int*)*50);
    for (int i = 0; i < 50; i++)
    {

        arrInt[i]= malloc(sizeof(int)*50);
        for(int j =0; j < 50; j++)
        {
            arrInt[i][j] = 0;
        }
    }
    
    for (int i = 0; i < 10; i++)
    {
        for(int j =0; j < 10; j++)
        {
        printf("%d ", arrInt[i][j]);
        }
        printf("\n");
    }

    char tmp[20];
    printf("Enter string: ");
    scanf("%[^\n]s%*c", tmp);
    
    printf("\n%s\n", tmp);

    free(arrStr);
    free(arrInt);
    return 0;
}