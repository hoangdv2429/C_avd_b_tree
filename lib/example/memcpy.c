#include "conio.h"
#include "stdio.h"

void* memcpy(void* region1, const void* region2,size_t n) {
    const char* first = (const char*) region2;
    const char* last = ((const char*) region2) + n;
    char* result = (char*) region1;
    while (first != last) *result++ = *first++;
    return result;
}

int main()
{
    int x = 5;
    int *p = &x;
    int k;
    int *y = &k;
    memcpy(y,p,sizeof(int));
    printf("k=%d\n",k);
    getch();
    return 1;
}
