//su dung jrb (red black tree)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"

void addentry(const JRB b, const void *key, const void *value)
{
    jrb_insert_str(b, strdup(key), new_jval_v(value));
}

void ReadFile(FILE *fp, JRB b)
{

    while (!feof(fp))
    {
        char *name;
        name = malloc(sizeof(char) * 50);
        long *pn;
        pn = malloc(sizeof(long));
        fscanf(fp, "%ld %[^\n]s\n", pn, name);
        // root = insert(root,key,value);
        addentry(b, name, pn);
        printf("%20s %15ld\n", name, *pn);
        free(name);
        free(pn);
    }
    return;
}

void PrintFile(FILE *fp, JRB ByName, JRB ByNumber)
{
    JRB bn;
    int yn;

    if (fp == NULL)
    {
        printf("File not found.");
        exit(1);
    }
    else
    {
        printf("output theo key hay number (1/0): ");
        scanf("%d", &yn);
        if (yn == 1)
        {
            jrb_traverse(bn, ByName)
            {
                fprintf(fp, "%20s %15ld\n", jval_s(bn->key), *(long *)jval_v(bn->val));
            }
        }
        else if (yn == 0)
        {
            jrb_traverse(bn, ByNumber)
            {
                fprintf(fp, "%20s %15ld\n", jval_s(bn->val), *(long *)jval_v(bn->key));
            }
        }
        else
        {
            printf("\nNot printed.\n");
        }
    }
}

int main()
{

    FILE *fp;
    FILE *fp1;
    int choice;
    int choice2;
    int choice3;
    JRB b;
    JRB bn;
    JRB ByNumber;
    char c;

    b = make_jrb();
    ByNumber = make_jrb();

    do
    {

        printf("\nWelcome to phonebook 404.\n 1. input from file\n 2. sub menu 2\n");
        printf("\nOption: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fp = fopen("phonenumber.txt", "r+");
            if (fp == NULL)
            {
                printf("File not found.");
                exit(1);
            }
            ReadFile(fp, b);
            fclose(fp);
            printf("\n");
            break;
        case 2:
            do
            {

                printf("\nday la menu 2:\n\n1. delete entire database, create new phonebook\n2. Enter new entry and replace its number if needed\n3. Show exist data\n4. update following name's number\n5. delete following name & number\n6. re-arrange phonebook by name\n7. re-arrange phonebook by number\n8. sub menu 3\n9. output .txt file with new order\n10. quit\n\nOption: ");
                scanf("%d", &choice2);
                switch (choice2)
                {
                case 1:

                    jrb_free_tree(b);
                    b = make_jrb();
                    printf("all database deleted.\n");
                    int n;
                    char **name;
                    long tmpnumber;
                    printf("Enter n new number of phonebook: ");
                    scanf("%d", &n);
                    name = malloc(sizeof(char *) * n);
                    for (int i = 0; i < n; i++)
                    {
                        JRB check;
                        name[i] = malloc(sizeof(char) * 50);
                        printf("Enter new entry's name number %d:", i + 1);
                        c = getchar();
                        gets(name[i]);
                        printf("Enter entry %d's number: ", i + 1);
                        scanf("%ld", &tmpnumber);
                        check = jrb_find_str(b, name[i]);
                        if (check == NULL)
                        {
                            addentry(b, name[i], &tmpnumber);
                            free(name[i]);
                        }
                        else
                        {
                            printf("\nExist!! Entry is not added.\n");
                        }
                    }
                    free(name);
                    break;

                case 2:
                    printf("\n");
                    JRB tmp; //this is for funt 2.2
                    int yn;  // dieu kien thu
                    char *name1;
                    long tmpnumber1;
                    name1 = malloc(sizeof(char) * 50);
                    printf("Enter entry's name: ");
                    c = getchar();
                    gets(name1);
                    printf("Enter entry number: ");
                    scanf("%ld", &tmpnumber1);
                    tmp = jrb_find_str(b, name1);
                    if (tmp != NULL)
                    {
                        printf("name existed, overwritting ? (1/0): ");
                        scanf("%d", &yn);
                        if (yn == 1)
                        {
                            tmp->val = new_jval_v(&tmpnumber1);
                            printf("\n");
                        }
                    }
                    else
                    {
                        printf("added new entry.\n");
                        addentry(b, name1, &tmpnumber1);
                    }
                    free(name1);
                    break;
                case 3:
                    printf("\n");
                    jrb_traverse(bn, b)
                    {
                        printf("%20s %15ld\n", jval_s(bn->key), *(long *)jval_v(bn->val));
                    }
                    printf("\n");
                    break;
                case 4:
                    printf("\n");
                    char *name2;
                    JRB tmp1;
                    name2 = malloc(sizeof(char) * 50);
                    printf("Enter entry's name: ");
                    c = getchar();
                    gets(name2);
                    tmp1 = jrb_find_str(b, name2);

                    if (tmp1 != NULL)
                    {
                        long tmpbnumber2;
                        printf("Found!! Enter new number: ");
                        scanf("%ld", &tmpbnumber2);
                        tmp1->val = new_jval_v(&tmpbnumber2);
                        printf("Updated.\n");
                    }
                    else
                    {
                        printf("Not found.");
                    }
                    free(name2);
                    break;
                case 5:

                    printf("\n");
                    char *name3;
                    JRB tmp2;
                    name3 = malloc(sizeof(char) * 50);
                    printf("Enter entry's name: ");
                    c = getchar();
                    gets(name3);
                    tmp2 = jrb_find_str(b, name3);

                    if (tmp2 != NULL)
                    {
                        jrb_delete_node(tmp2);
                        printf("\nDone.\n");
                    }
                    else
                    {
                        printf("\nnot exist.\n");
                    }
                    free(name3);
                    break;
                case 6: //em khong hieu ham nay lam gi cho lam, tai khi cho vao cay thi no da theo thu tu roi
                    printf("\n");
                    jrb_traverse(bn, b)
                    {
                        printf("%20s %15ld\n", jval_s(bn->key), *(long *)jval_v(bn->val));
                    }
                    break;
                case 7:
                    printf("\n");
                    JRB ByNumber2;
                    jrb_traverse(bn, b)
                    {
                        printf("%20s %15ld\n", jval_s(bn->key), *(long *)jval_v(bn->val));
                        jrb_insert_str(ByNumber, jval_s(bn->val), bn->key);
                    }
                    printf("\nRe-arrange...\n\n");
                    jrb_traverse(ByNumber2, ByNumber)
                    {
                        printf("%20s %15ld\n", jval_s(ByNumber2->val), *(long *)jval_v(ByNumber2->key));
                    }
                    printf("\n");
                    break;
                case 8:
                    printf("\nSub menu 3\n1. Search by name.\n2. Search by number.\n3. Back to sub menu 2\n");
                    do
                    {
                        printf("\nOption: ");
                        scanf("%d", &choice3);
                        switch (choice3)
                        {
                        case 1:
                            printf("\n");
                            int yn1;
                            JRB tmp3;
                            do
                            {
                                char name4[50];
                                printf("Find name: ");
                                c = getchar();
                                gets(name4);
                                tmp3 = jrb_find_str(b, name4);
                                if (tmp3 != NULL)
                                {
                                    printf("%20s %15ld\n", jval_s(tmp3->key), *(long *)jval_v(tmp3->val));
                                }
                                else
                                {
                                    printf("Not found.\n");
                                }
                                printf("\nFind again (1/0): ");
                                scanf("%d", &yn1);
                            } while (yn1 != 0);
                            break;
                        case 2:
                            printf("\n");
                            int yn2;
                            JRB tmp4;
                            do
                            {
                                char *tmpnumber;
                                double tmpnumber;
                                printf("Find by number: ");
                                scanf("%lf", &tmpnumber);
                                tmp4 = jrb_find_str(ByNumber, tmpnumber);
                                if (tmp4 != NULL)
                                {
                                    printf("%20s %15ld\n", jval_s(tmp4->val), *(long *)jval_v(tmp4->key));
                                }
                                else
                                {
                                    printf("Not found.\n");
                                }
                                printf("\nFind again (1/0): ");
                                scanf("%d", &yn2);

                            } while (yn2 != 0);
                            break;
                        default:
                            break;
                        }
                    } while (choice3 != 3);

                    break;
                case 9:
                    printf("\n");

                    fp1 = fopen("output.txt", "w+");
                    PrintFile(fp1, b, ByNumber);
                    fclose(fp1);
                    break;
                case 10:
                    return 0;
                default:
                    break;
                }
            } while (choice2 != 10);

        default:
            break;
        }

    } while (choice != 10);

    jrb_free_tree(b);
    jrb_free_tree(ByNumber);

    return 0;
}