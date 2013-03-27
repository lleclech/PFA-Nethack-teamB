#include "../pfa-src/math_tool.h"

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

/*
 *  Store one column from one table in global variable MATH_LIST
 *  arguments :
 *  void * db = pointer to the database
 *  char * table_name
 *    may be generated from a struct AllData * with function "get_table_name()"
 *    or be "table_bot_Explorer_1_mod_SEARCH_DOORS_1"
 *  char * data
 *    may be "DAY", "MONTH", "YEAR", "DOORLVL", "DOORDISC" or "STEPS"
 */
void store_in_table(void * db, char * table_name, char * data)
{
  destroy_list_nbrs(MATH_LIST);
  MATH_LIST = create_list_nbrs();
  
  search_DB(db, table_name, data, math_callback);
}

int get_mean_on_table(void * db, char * table_name, char * data)
{
    destroy_list_nbrs(MATH_LIST);
    MATH_LIST = create_list_nbrs();

    search_DB(db, table_name, data, math_callback);

    int mean = get_mean(MATH_LIST);

    return mean;
}

int get_median_on_table(void * db, char * table_name, char * data)
{
    destroy_list_nbrs(MATH_LIST);
    MATH_LIST = create_list_nbrs();

    search_DB(db, table_name, data, math_callback);

    int median = get_median(MATH_LIST);

    return median;
}

int get_variance_on_table(void * db, char * table_name, char * data)
{
    destroy_list_nbrs(MATH_LIST);
    MATH_LIST = create_list_nbrs();

    search_DB(db, table_name, data, math_callback);

    int variance = get_variance(MATH_LIST);

    return variance;
}

int get_std_deviation_on_table(void * db, char * table_name, char * data)
{
    destroy_list_nbrs(MATH_LIST);
    MATH_LIST = create_list_nbrs();

    search_DB(db, table_name, data, math_callback);

    int std_deviation = get_std_deviation(MATH_LIST);

    return std_deviation;
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
