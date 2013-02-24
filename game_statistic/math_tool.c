#include "math_tool.h"

extern void * db;
extern struct List_Nbrs * MATH_LIST;

struct List_Nbrs * create_list_nbrs(void)
{
    struct List_Nbrs * l = malloc(sizeof(struct List_Nbrs));

    l->nb_elt = 0;
    l->nbrs = NULL;

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
  if (l != NULL)
  {
      free(l->nbrs);
  }

  free(l);
  l = NULL;

  return EXIT_SUCCESS;
}

int math_callback(void* NotUsed, int argc, char **argv, char **azColname)
{
    int i;
    int val;

    for(i = 0; i < argc; i++)
    {
        val = atoi(argv[i]);
        add_nb_to_list(val, MATH_LIST);
    }
    return 0;
}

int get_mean_on_table(char * table_name, char * data)
{
    destroy_list_nbrs(MATH_LIST);
    MATH_LIST = create_list_nbrs();

    search_DB(db, table_name, data, math_callback);

    int mean = get_mean(MATH_LIST);

    return mean;
}

void debug_display_list(struct List_Nbrs * l)
{
    int i = 0;
    printf("DEBUG DISPLAY LIST_NBRS\n");
    for (i = 0; i < l->nb_elt; i++)
    {
        printf("elt#%d = %d\n", i, l->nbrs[i]);
    }
}
