#ifndef MATH_TOOL_H
#define MATH_TOOL_H

#include <stdio.h>
#include <stdlib.h>

struct List_Nbrs
{
  int * nbrs;
  int nb_elt;
};

struct List_Nbrs * create_list_nbrs(void);
int add_nb_to_list(int, struct List_Nbrs *);
int destroy_list_nbrs(struct List_Nbrs *);

#endif
