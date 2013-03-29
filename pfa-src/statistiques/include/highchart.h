#ifndef __HIGHCHART_H__
#define __HIGHCHART_H__

#include <stdio.h>

#include "axis.h"
#include "serie.h"
#include "title.h"
#include "chart.h"
#include "plotoptions.h"

#define HIGHCHART_FREE(x)	{ if(x != NULL) { highchart__free(x); x = NULL; } }

struct Highchart {
	struct Chart chart;
	struct Title title;
	struct Title subtitle;

  // axis
  unsigned int nXAxis;
	struct Axis* xAxis;
  unsigned int nYAxis;
	struct Axis* yAxis;

	struct PlotOptions plotoptions;
  // series
	unsigned int nSeries;
	struct Serie* series;
};

void highchart__init(struct Highchart* highchart);

void highchart__uninit(struct Highchart* highchart);

struct Highchart* highchart__malloc();

void highchart__free(struct Highchart* highchart);

void highchart__fprint(FILE* fp, const struct Highchart* highchart);

void highchart__set_render_target(struct Highchart* highchart, const char* target);

void highchart__set_title(struct Highchart* highchart, const char* title);

void highchart__set_subtitle(struct Highchart* highchart, const char* subtitle);

void highchart__init_axis(struct Highchart* highchart,
                          unsigned int axis,
                          unsigned int nb);

void highchart__uninit_axis(struct Highchart* highchart, 
                            unsigned int axis);

struct Axis* highchart__get_axis(struct Highchart* highchart, 
                                 unsigned int axis,
                                 unsigned int ind);

void highchart__set_axis_title(struct Highchart* highchart, 
                               unsigned int axis, 
                               unsigned int ind,
                               const char* title);

void highchart__set_axis_category(struct Highchart* highchart, 
                                  unsigned int axis, 
                                  unsigned int ind,
                                  unsigned int categorytype, 
                                  unsigned int nbCategories);


void highchart__uninit_series(struct Highchart* highchart);

void highchart__set_series(struct Highchart* highchart, unsigned int nSeries);

void highchart__set_serie(struct Highchart* highchart, 
                          int type,
                          int axis,
                          unsigned int serie, 
                          unsigned int datatype, 
                          unsigned int nbData);

void highchart__set_serie_name(struct Highchart* highchart, int serie, const char* name);

void highchart__set_plotoption(struct Highchart* highchart, int option, int enable);

#endif /* __HIGHCHART_H__ */
