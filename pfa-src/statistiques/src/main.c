#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "str.h"
#include "axis.h"
#include "highchart.h"
#include "html.h"

#define CONTAINER_PREFIX "container"

void test()
{
	unsigned int i, j;
	char buffer[1024];

	unsigned int nCharts = CHART_TYPE_COUNT;
	struct Highchart highcharts[CHART_TYPE_COUNT];

	struct Highchart* highchart;
	for(i = 0; i < nCharts; ++i)
		highchart__init(highcharts + i);

	// LINE
	highchart = highcharts + CHART_TYPE_LINE;
	sprintf(buffer, "%s%u", CONTAINER_PREFIX, CHART_TYPE_LINE);
	highchart->chart.renderTo = str__dup(buffer);
	highchart->title.text = str__dup("line-title");
	highchart->subtitle.text = str__dup("line-subtitle");
	highchart->xAxis.title.text = str__dup("line-xAxis-title");

	highchart->xAxis.nbCategories = 10;
	highchart->xAxis.categorytype = CATEGORY_STR;
	highchart->xAxis.category_str = (char**)malloc(sizeof(char*) * highchart->xAxis.nbCategories);
	for(i = 0; i < highchart->xAxis.nbCategories; ++i)
	{
		highchart->xAxis.category_str[i] = (char*)malloc(10);
		sprintf(highchart->xAxis.category_str[i], "x%u", i);
	}

	highchart->yAxis.title.text = str__dup("line-yAxis-title");
	highchart->yAxis.nbCategories = 0;

  highchart->plotoptions.line_dataLabels_enabled = 1;
  highchart->plotoptions.line_enableMouseTracking = 0;

	highchart->nSeries = 4;
	highchart->series = (struct Serie*)malloc(sizeof(struct Serie) * highchart->nSeries);
	for(i = 0; i < highchart->nSeries; ++i)
	{
		struct Serie* serie = highchart->series + i;
		serie->name = (char*)malloc(30);
		sprintf(serie->name, "line-series-data-%u", i);
		serie->datatype = SERIE_DATATYPE_INT;
		serie->nbData = highchart->xAxis.nbCategories;
		serie->data_int = (int*)malloc(sizeof(int) * serie->nbData);
		for(j = 0; j < serie->nbData; ++j)
			serie->data_int[j] = rand() % 100;
	}
	highchart->label = 1;

  // BAR
  highchart = highcharts + CHART_TYPE_BAR;
  sprintf(buffer, "%s%u", CONTAINER_PREFIX, CHART_TYPE_BAR);
  highchart->chart.renderTo = str__dup(buffer);
  highchart->chart.type = CHART_TYPE_BAR;
  highchart->title.text = str__dup("bar-title");
  highchart->subtitle.text = str__dup("bar-subtitle");
  highchart->xAxis.title.text = str__dup("bar-xAxis-title");

  highchart->xAxis.nbCategories = 5;
  highchart->xAxis.categorytype = CATEGORY_STR;
  highchart->xAxis.category_str = (char**)malloc(sizeof(char*) * highchart->xAxis.nbCategories);
  for(i = 0; i < highchart->xAxis.nbCategories; ++i)
	{
		highchart->xAxis.category_str[i] = (char*)malloc(10);
		sprintf(highchart->xAxis.category_str[i], "x%u", i);
	}
  
  highchart->yAxis.title.text = str__dup("bar-yAxis-title");

  highchart->plotoptions.series_stacking = STACKING_NORMAL;

  highchart->nSeries = 3;
  highchart->series = (struct Serie*)malloc(sizeof(struct Serie) * highchart->nSeries);
  for(i = 0; i < highchart->nSeries; ++i)
	{
		struct Serie* serie = highchart->series + i;
		serie->name = (char*)malloc(30);
		sprintf(serie->name, "bar-series-data-%u", i);

		serie->datatype = SERIE_DATATYPE_INT;
		serie->nbData = highchart->xAxis.nbCategories;
		serie->data_int = (int*)malloc(sizeof(int) * serie->nbData);
		for(j = 0; j < serie->nbData; ++j)
			serie->data_int[j] = rand() % 100;
	}
  highchart->label = 1;

  // print
	print_html("text", CHART_TYPE_COUNT, highcharts);

	for(i = 0; i < nCharts; ++i)
		highchart__uninit(highcharts + i);
}

int main(int argc, char** argv)
{
  (void)argc;
  (void)argv;
	
	test();
	return 0;
}
