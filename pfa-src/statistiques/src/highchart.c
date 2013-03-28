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
	axis__init(&(highchart->xAxis));
	axis__init(&(highchart->yAxis));
  plotOptions__init(&(highchart->plotoptions), &(highchart->chart));
	highchart->nSeries = 0;
	highchart->series = NULL;
}

void highchart__uninit(struct Highchart* highchart)
{
	chart__uninit(&(highchart->chart));
	title__uninit(&(highchart->title));
	title__uninit(&(highchart->subtitle));
	axis__uninit(&(highchart->xAxis));
	axis__uninit(&(highchart->yAxis));
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
	unsigned int i, j;

	STAT_PRINTF("=new Highcharts.Chart({");

	chart__fprint(fp, &(highchart->chart));
	title__fprint(fp, &(highchart->title), "title");
	title__fprint(fp, &(highchart->subtitle), "subtitle");
	axis__fprint(fp, &(highchart->xAxis), "xAxis");
	axis__fprint(fp, &(highchart->yAxis), "yAxis");
  plotOptions__fprint(fp, &(highchart->plotoptions));

	// series
	SEQUENCE_BEGIN("series");
	for(i = 0; i < highchart->nSeries; ++i)
	{
		struct Serie* serie = highchart->series + i;
		if(i > 0)
			STAT_PUTC(',');
		STAT_PUTC('{');
		if (serie->name != NULL)
			STAT_PRINTF("name:'%s',", serie->name);
		STAT_PRINTF("data:[");
		for(j = 0; j < serie->nbData; ++j)
		{
			if(j > 0)
				STAT_PUTC(',');
			switch(serie->datatype)
			{
			case SERIE_DATATYPE_INT:
				STAT_PRINTF("%d", serie->data_int[j]);
				break;
			}
		}
    STAT_PRINTF("]}");
	}
	SEQUENCE_END;

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

struct Axis* highchart__get_axis(struct Highchart* highchart, unsigned int axis)
{
  struct Axis* a = NULL;
  switch(axis)
  {
  case AXIS_X:
    a = &(highchart->xAxis);
    break;
  case AXIS_Y:
    a = &(highchart->yAxis);
    break;
  }
  return a;
}

void highchart__set_axis_title(struct Highchart* highchart, unsigned int axis, const char* title)
{
  struct Axis* a = highchart__get_axis(highchart, axis);
  SAFE_FREE(a->title.text);
  a->title.text = str__dup(title);
}

void highchart__set_axis_category(struct Highchart* highchart, 
                                  unsigned int axis, 
                                  unsigned int categorytype, 
                                  unsigned int nbCategories)
{
  struct Axis* a = highchart__get_axis(highchart, axis);
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

void highchart__set_serie(struct Highchart* highchart, int serie, int datatype, int nbData)
{
  struct Serie* s = &(highchart->series[serie]);
  switch(s->datatype)
  {
  case SERIE_DATATYPE_INT:
    SAFE_FREE(s->data_int);
    break;
  }

  s->datatype = datatype;
  s->nbData = nbData;
  
  switch(s->datatype)
  {
  case SERIE_DATATYPE_INT:
    s->data_int = STAT_MALLOC(int, nbData);
    break;
  }
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