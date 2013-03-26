#ifndef __PLOTOPTIONS_H__
#define __PLOTOPTIONS_H__

#define PLOTOPTIONS_UNSET -1

#define STACKING_NORMAL 0
#define STACKING_COUNT  1

struct PlotOptions {
  int line_dataLabels_enabled;
  int line_enableMouseTracking;


	int series_stacking;
};

void plotOptions__init(struct PlotOptions* plotOptions);

void plotOptions__uninit(struct PlotOptions* plotOptions);

void plotOptions__print(struct PlotOptions* plotOptions);

#endif

