#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"

int main(int argc, char *argv[])
{
  IS is;
  int nlines;
  printf("check number of line in the given filename...\n");
  is = make_inputstruct(argv[1], "p");; 
  if (is == NULL)
  {
    //perror(CatThis);
    exit(1);
  }
  
  nlines = 0;
  while (get_line(is) >= 0)
    nlines++;

  printf("# lines in %s: %d\n", argv[1], nlines);
  exit(0);
}