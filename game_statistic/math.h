#ifndef MATH_H
#define MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../game_statistic/math_tool.h"

double get_mean(struct List_Nbrs *);
int get_median(struct List_Nbrs *);
double get_variance(struct List_Nbrs *);
double get_std_deviation(struct List_Nbrs *);

#endif
