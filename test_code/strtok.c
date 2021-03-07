#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char string[50] = "m1 = s1 s2 s5 s7";
    // Extract the first token
    char *token = strtok(string, "=");
    // loop through the string to extract all other tokens
    printf("%s\n", token);
    while (token != NULL)
    {
        if (token[0] == 's')
        {
            printf(" %s\n", token); //printing each token
            printf(" %d\n", atoi(token + 1));
        }
        token = strtok(NULL, " ");
    }
    return 0;
}