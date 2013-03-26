#include "plotoptions.h"
#include <stdio.h>
#include "macros.h"

const char* plotoptions_series_stacking_str[STACKING_COUNT] = {
  "normal"
};

void plotOptions__init(struct PlotOptions* plotOptions)
{
  plotOptions->line_dataLabels_enabled = PLOTOPTIONS_UNSET;
  plotOptions->line_enableMouseTracking = PLOTOPTIONS_UNSET;
  plotOptions->series_stacking = PLOTOPTIONS_UNSET;
  
}

void plotOptions__uninit(struct PlotOptions* plotOptions)
{
}

void plotOptions__print(struct PlotOptions* plotOptions)
{
  ATTRIBUTE_BEGIN("plotOptions");
  
  ATTRIBUTE_BEGIN("line");
  ATTRIBUTE_BEGIN("dataLabels");
  if(plotOptions->line_dataLabels_enabled != PLOTOPTIONS_UNSET)
  {
    printf("enabled:%s,", BOOL_STR(plotOptions->line_dataLabels_enabled));
  }
  ATTRIBUTE_END;
  if(plotOptions->line_enableMouseTracking != PLOTOPTIONS_UNSET)
  {
    printf("enableMouseTracking:%s,", BOOL_STR(plotOptions->line_enableMouseTracking));
  }
  ATTRIBUTE_END;

  ATTRIBUTE_BEGIN("series");
  if(plotOptions->series_stacking != PLOTOPTIONS_UNSET)
  {
    printf("stacking: '%s',", plotoptions_series_stacking_str[plotOptions->series_stacking]);
  }
  ATTRIBUTE_END;

  ATTRIBUTE_END;
}