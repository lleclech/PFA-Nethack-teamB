#ifndef __HIGHCHART_H__
#define __HIGHCHART_H__

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
	struct Axis xAxis;
	struct Axis yAxis;
	struct PlotOptions plotoptions;
	int label;
	unsigned int nSeries;
	struct Serie* series;
};

void highchart__init(struct Highchart* highchart);

void highchart__uninit(struct Highchart* highchart);

struct Highchart* highchart__malloc();

void highchart__free(struct Highchart* highchart);

void highchart__print(struct Highchart* highchart);

#endif /* __HIGHCHART_H__ */