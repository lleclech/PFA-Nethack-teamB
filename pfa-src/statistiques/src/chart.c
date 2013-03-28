#include "chart.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

const char* chart_type_str[CHART_TYPE_COUNT] = {
	"line", "bar"
};

void chart__init(struct Chart* chart)
{
	chart->renderTo = NULL;
	chart->type = CHART_TYPE_LINE;
	chart->inverted = 0;
}

void chart__uninit(struct Chart* chart)
{
	SAFE_FREE(chart->renderTo);
}

struct Chart* chart__malloc()
{
	struct Chart* chart = STAT_MALLOC_1(struct Chart);
	if(chart != NULL)
		chart__init(chart);
	return chart;
}

void chart__free(struct Chart* chart)
{
	chart__uninit(chart);
	free(chart);
}

void chart__fprint(FILE* STAT_FP, const struct Chart* chart)
{
	unsigned int type = chart->type;
	ATTRIBUTE_BEGIN("chart");
  STAT_PRINTF("renderTo:'%s',", chart->renderTo);
	if(type < CHART_TYPE_COUNT)
		STAT_PRINTF("type:'%s',", chart_type_str[type]);
	if(chart->inverted)
		STAT_PRINTF("inverted:true,");
	ATTRIBUTE_END;
}
