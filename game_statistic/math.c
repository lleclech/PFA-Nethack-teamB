#include "math_tool.h"

double get_mean(struct List_Nbrs * l)
{
  int i = 0;
  double sum = 0;

  for (i = 0; i < l->nb_elt; i++)
    {
      sum += l->nbrs[i];
    }

  return sum/l->nb_elt;
}

int get_median(struct List_Nbrs * l)
{
  return l->nbrs[l->nb_elt];
}

double get_variance(struct List_Nbrs * l)
{
  int i = 0;
  double a = 0;
  double sum = 0;
  double mean = get_mean(l);

  for (i = 0; i < l->nb_elt; i++)
    {
      a = l->nbrs[i] - mean;
      a *= a;
      sum += a;
    }

  return sum/l->nb_elt;
}

double get_std_deviation(struct List_Nbrs * l)
{
    return sqrt(get_variance(l));
}
