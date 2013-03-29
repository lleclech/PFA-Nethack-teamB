#include "plotoptions.h"
#include <stdio.h>
#include "macros.h"

const char* plotoptions_series_stacking_str[STACKING_COUNT] = {
  "normal"
};

void plotOptions__init(struct PlotOptions* plotOptions, struct Chart* chart)
{
  plotOptions->dataLabels_enabled = PLOTOPTIONS_UNSET;
  plotOptions->enableMouseTracking = PLOTOPTIONS_UNSET;
  plotOptions->series_stacking = PLOTOPTIONS_UNSET;
  plotOptions->chart = chart;
}

void plotOptions__uninit(struct PlotOptions* plotOptions)
{
  plotOptions->chart = NULL;
}

void plotOptions__fprint(FILE* STAT_FP, const struct PlotOptions* plotOptions)
{
  ATTRIBUTE_BEGIN("plotOptions");
  
  if(plotOptions->chart != NULL)
  {
    ATTRIBUTE_BEGIN(chart_type_str[plotOptions->chart->type]);
    
    ATTRIBUTE_BEGIN("dataLabels");
    if(plotOptions->dataLabels_enabled != PLOTOPTIONS_UNSET)
      STAT_PRINTF("enabled:%s,", BOOL_STR(plotOptions->dataLabels_enabled));
    ATTRIBUTE_END;

    if(plotOptions->enableMouseTracking != PLOTOPTIONS_UNSET)
      STAT_PRINTF("enableMouseTracking:%s,", BOOL_STR(plotOptions->enableMouseTracking));

    ATTRIBUTE_END;
  }

  ATTRIBUTE_BEGIN("series");
  if(plotOptions->series_stacking != PLOTOPTIONS_UNSET)
    STAT_PRINTF("stacking: '%s',", plotoptions_series_stacking_str[plotOptions->series_stacking]);
  ATTRIBUTE_END;

  ATTRIBUTE_END;
}