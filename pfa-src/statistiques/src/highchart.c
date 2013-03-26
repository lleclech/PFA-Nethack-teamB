#include "highchart.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

void highchart__init(struct Highchart* highchart)
{
	chart__init(&(highchart->chart));
	title__init(&(highchart->title));
	title__init(&(highchart->subtitle));
	axis__init(&(highchart->xAxis));
	axis__init(&(highchart->yAxis));
  plotOptions__init(&(highchart->plotoptions));
	highchart->label = 0;
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
	SAFE_FREE(highchart->series);
}

struct Highchart* highchart__malloc()
{
	struct Highchart* highchart = (struct Highchart*)malloc(sizeof(struct Highchart));
	if(highchart != NULL)
		highchart__init(highchart);
	return highchart;
}

void highchart__free(struct Highchart* highchart)
{
	highchart__uninit(highchart);
	free(highchart);
}

void highchart__print(struct Highchart* highchart)
{
	unsigned int i, j;

	printf("=new Highcharts.Chart({");

	chart__print(&(highchart->chart));
	title__print(&(highchart->title), "title");
	title__print(&(highchart->subtitle), "subtitle");
	axis__print(&(highchart->xAxis), "xAxis");
	axis__print(&(highchart->yAxis), "yAxis");
  plotOptions__print(&(highchart->plotoptions));

	// series
	SEQUENCE_BEGIN("series");
	for(i = 0; i < highchart->nSeries; ++i)
	{
		struct Serie* serie = highchart->series + i;
		if(i > 0)
			putchar(',');
		printf("{");
		if (serie->name != NULL)
			printf("name:'%s',", serie->name);
		printf("data:[");
		for(j = 0; j < serie->nbData; ++j)
		{
			if(j > 0)
				putchar(',');
			switch(serie->datatype)
			{
			case SERIE_DATATYPE_INT:
				printf("%d", serie->data_int[j]);
				break;
			}
		}
		printf("]");
		printf("}");
	}
	SEQUENCE_END;

	printf("});");
}