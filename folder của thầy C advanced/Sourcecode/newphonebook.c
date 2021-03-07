#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

void addentry(const JRB b, const void* key, const void* value)
{
    jrb_insert_str(b, strdup(key), new_jval_v(value));
}

int main()
{
  JRB b;
  JRB bn;

  b = make_jrb();
  long number = 123567567;
  char name[] = "Ng Van A";
  addentry(b,name,&number);

  long number1 = 2345678;
  char name1[] = "Ng Van B";
  addentry(b,name1,&number1);

  long number2 = 345657876;
  char name2[] = "Ng Van C";
  addentry(b,name2,&number2);
  //jrb_insert_str(b, strdup(name), new_jval_v((number)));
  jrb_traverse(bn, b) {
    printf("%s %ld\n", jval_s(bn->key), *(long*)jval_v(bn->val));
  }


  exit(0);
}
