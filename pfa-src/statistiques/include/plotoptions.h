#ifndef __PLOTOPTIONS_H__
#define __PLOTOPTIONS_H__

#include <stdio.h>

#include "chart.h"

#define PLOTOPTIONS_UNSET -1

#define STACKING_NORMAL 0
#define STACKING_COUNT  1

#define PLOTOPTIONS_DATALABELS    0
#define PLOTOPTIONS_MOUSETRACKING 1

struct PlotOptions {
  int dataLabels_enabled;
  int enableMouseTracking;
	int series_stacking;
  struct Chart* chart;
};

void plotOptions__init(struct PlotOptions* plotOptions, struct Chart* chart);

void plotOptions__uninit(struct PlotOptions* plotOptions);

void plotOptions__fprint(FILE* fp, const struct PlotOptions* plotOptions);

#endif

