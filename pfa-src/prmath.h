#ifndef PRMATH_H
#define PRMATH_H

#include <stdio.h>
#include <stdlib.h>
#undef yn
#include <math.h>

#include "../pfa-src/math_tool.h"

struct List_Nbrs;

double get_mean(struct List_Nbrs *);
int get_median(struct List_Nbrs *);
double get_variance(struct List_Nbrs *);
double get_std_deviation(struct List_Nbrs *);

#endif
