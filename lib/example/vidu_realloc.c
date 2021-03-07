#include "conio.h"
#include "stdio.h"

typedef struct _PhoneEntry{
    int phonenumber;
} PhoneEntry;

typedef struct _PhoneBook{
PhoneEntry * entries;
int total;
int size;
} PhoneBook;



int main()
{
    int n = 2;
    PhoneBook* pb = (PhoneBook *) malloc(sizeof(PhoneBook));
    pb->total = 100;
    pb->size = n;
    pb->entries = (PhoneEntry *) malloc(n*sizeof(PhoneEntry));
    (pb->entries)->phonenumber =  1000;
    (pb->entries+1)->phonenumber =  200;
    int i;
    for(i=0;i<n;i++)
    printf("%d\n",(pb->entries+i)->phonenumber);

    //tang so phan tu cua phoneentries bang ham realloc, gan lai n = n+1
    n = n+1;
    pb->entries = realloc(pb->entries,n*sizeof(PhoneEntry));
    (pb->entries+2)->phonenumber = 345;
    for(i=0;i<n;i++)
    printf("%d\n",(pb->entries+i)->phonenumber);

    getch();
    return 1;
}
