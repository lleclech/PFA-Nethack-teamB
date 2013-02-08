#include "math_tool.h"

struct List_Nbrs * create_list_nbrs(void)
{
    struct List_Nbrs * l = malloc(sizeof(struct List_Nbrs));

    l->nb_elt = 1;
    l->nbrs = malloc(sizeof(int));

    return l;
}

int add_nb_to_list(int a, struct List_Nbrs * l)
{
    int i = 0;
    int * new_nbrs = malloc((l->nb_elt + 1)*sizeof(int));

    for (i = 0; i < l->nb_elt; i++)
    {
        new_nbrs[i] = l->nbrs[i];
    }
    new_nbrs[l->nb_elt] = a;
    l->nb_elt ++;

    free(l->nbrs);
    l->nbrs = new_nbrs;

    return EXIT_SUCCESS;
}

int destroy_list_nbrs(struct List_Nbrs * l)
{
  free(l->nbrs);
  free(l);

  return EXIT_SUCCESS;
}
