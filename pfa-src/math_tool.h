#ifndef MATH_TOOL_H
#define MATH_TOOL_H

#include <stdio.h>
#include <stdlib.h>

#include "../pfa-src/db_manager.h"
#include "../pfa-src/prmath.h"

struct List_Nbrs
{
  int * nbrs;
  int nb_elt;
};

struct List_Nbrs * create_list_nbrs(void);
int add_nb_to_list(int, struct List_Nbrs *);
int destroy_list_nbrs(struct List_Nbrs *);
int math_callback(void*, int, char **, char **);
int get_mean_on_table(void *, char *, char *);
int get_median_on_table(void *, char *, char *);
int get_variance_on_table(void *, char *, char *);
int get_std_deviation_on_table(void *, char *, char *);
void debug_display_list(struct List_Nbrs *);

#endif
