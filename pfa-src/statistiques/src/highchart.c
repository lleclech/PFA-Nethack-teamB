#include "highchart.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "str.h"

void highchart__init(struct Highchart* highchart)
{
	chart__init(&(highchart->chart));
	title__init(&(highchart->title));
	title__init(&(highchart->subtitle));

  highchart__init_axis(highchart, AXIS_X, 0);
  highchart__init_axis(highchart, AXIS_Y, 0);

  plotOptions__init(&(highchart->plotoptions), &(highchart->chart));
	highchart->nSeries = 0;
	highchart->series = NULL;
}

void highchart__init_axis(struct Highchart* highchart,
                          unsigned int axis,
                          unsigned int nb)
{
  unsigned int i;
  if(axis == AXIS_X)
  {
    highchart->nXAxis = nb;
    if(nb > 0)
    {
      highchart->xAxis = STAT_MALLOC(struct Axis, nb);
      for(i = 0; i < nb; ++i)
        axis__init(highchart->xAxis + i);
    }
    else
      highchart->xAxis = NULL;
  }
  else if(axis == AXIS_Y)
  {
    highchart->nYAxis = nb;
    if(nb > 0)
    {
      highchart->yAxis = STAT_MALLOC(struct Axis, nb);
      for(i = 0; i < nb; ++i)
        axis__init(highchart->yAxis + i);
    }
    else
      highchart->yAxis = NULL;
  }
}

void highchart__uninit_axis(struct Highchart* highchart, unsigned int axis)
{
  unsigned int i;
  if(axis == AXIS_X)
  {
    if(highchart->nXAxis > 0)
    {
      for(i = 0; i < highchart->nXAxis; ++i)
  	    axis__uninit(highchart->xAxis + i);
      SAFE_FREE(highchart->xAxis);
      highchart->nXAxis = 0;
    }
  }
  else if(axis == AXIS_Y)
  {
    if(highchart->nYAxis > 0)
    {
      for(i = 0; i < highchart->nYAxis; ++i)
  	    axis__uninit(highchart->yAxis + i);
      SAFE_FREE(highchart->yAxis);
      highchart->nYAxis = 0;
    }
  }
}

void highchart__uninit(struct Highchart* highchart)
{
  
	chart__uninit(&(highchart->chart));
	title__uninit(&(highchart->title));
	title__uninit(&(highchart->subtitle));

  highchart__uninit_axis(highchart, AXIS_X);
  highchart__uninit_axis(highchart, AXIS_Y);
  
  plotOptions__uninit(&(highchart->plotoptions));
  highchart__uninit_series(highchart);
}

struct Highchart* highchart__malloc()
{
	struct Highchart* highchart = STAT_MALLOC_1(struct Highchart);
	if(highchart != NULL)
		highchart__init(highchart);
	return highchart;
}

void highchart__free(struct Highchart* highchart)
{
	highchart__uninit(highchart);
	free(highchart);
}

void highchart__fprint(FILE* STAT_FP, const struct Highchart* highchart)
{
	STAT_PRINTF("=new Highcharts.Chart({");

	chart__fprint(STAT_FP, &(highchart->chart));
	title__fprint(STAT_FP, &(highchart->title), "title");
	title__fprint(STAT_FP, &(highchart->subtitle), "subtitle");

  axis__fprint(STAT_FP, highchart->xAxis, AXIS_X, highchart->nXAxis);
	axis__fprint(STAT_FP, highchart->yAxis, AXIS_Y, highchart->nYAxis);

  plotOptions__fprint(STAT_FP, &(highchart->plotoptions));

  serie__fprint(STAT_FP, highchart->series, highchart->nSeries);

	STAT_PRINTF("});");
}

void highchart__set_render_target(struct Highchart* highchart, const char* target)
{
  SAFE_FREE(highchart->chart.renderTo);
  highchart->chart.renderTo = str__dup(target);
}

void highchart__set_title(struct Highchart* highchart, const char* title)
{
  SAFE_FREE(highchart->title.text);
  highchart->title.text = str__dup(title);
}

void highchart__set_subtitle(struct Highchart* highchart, const char* subtitle)
{
  SAFE_FREE(highchart->subtitle.text);
  highchart->subtitle.text = str__dup(subtitle);
}

struct Axis* highchart__get_axis(struct Highchart* highchart, 
                                 unsigned int axis,
                                 unsigned int ind)
{
  struct Axis* a = NULL;
  switch(axis)
  {
  case AXIS_X:
    if(ind < highchart->nXAxis)
      a = highchart->xAxis + ind;
    break;
  case AXIS_Y:
    if(ind < highchart->nYAxis)
      a = highchart->yAxis + ind;
    break;
  }
  return a;
}

void highchart__set_axis_title(struct Highchart* highchart, 
                               unsigned int axis, 
                               unsigned int ind,
                               const char* title)
{
  struct Axis* a = highchart__get_axis(highchart, axis, ind);
  SAFE_FREE(a->title.text);
  a->title.text = str__dup(title);
}

void highchart__set_axis_category(struct Highchart* highchart, 
                                  unsigned int axis, 
                                  unsigned int ind,
                                  unsigned int categorytype, 
                                  unsigned int nbCategories)
{
  struct Axis* a = highchart__get_axis(highchart, axis, ind);
  axis__uninit_category(a);
  axis__init_category(a, categorytype, nbCategories);
}

void highchart__uninit_series(struct Highchart* highchart)
{
  unsigned int i = 0;
  for(; i < highchart->nSeries; ++i)
    serie__uninit(highchart->series + i);
  SAFE_FREE(highchart->series);
  highchart->nSeries = 0;
}

void highchart__set_series(struct Highchart* highchart, unsigned int nSeries)
{
  highchart__uninit_series(highchart);

  highchart->nSeries = nSeries;
  if(nSeries > 0)
  {
    unsigned int i = 0;
    highchart->series = STAT_MALLOC(struct Serie, nSeries);
    for(; i < nSeries; ++i)
      serie__init(highchart->series + i);
  }
}

void highchart__set_serie(struct Highchart* highchart, 
                          int type,
                          int axis,
                          unsigned int serie, 
                          unsigned int datatype, 
                          unsigned int nbData)
{
  struct Serie* s = &(highchart->series[serie]);
  serie__uninit_data(s);

  s->type = type;
  s->axis = axis;
  
  serie__init_data(s, datatype, nbData);
}

void highchart__set_serie_name(struct Highchart* highchart, int serie, const char* name)
{
  SAFE_FREE(highchart->series[serie].name);
  highchart->series[serie].name = str__dup(name);
}

void highchart__set_plotoption(struct Highchart* highchart, int option, int enable)
{
  switch(option)
  {
  case PLOTOPTIONS_DATALABELS:
    highchart->plotoptions.dataLabels_enabled = enable;
    break;
  case PLOTOPTIONS_MOUSETRACKING:
    highchart->plotoptions.enableMouseTracking = enable;
    break;
  }
}
