#ifndef __HTML_H__
#define __HTML_H__

#include <stdio.h>

#include "highchart.h"

void fprint_html(FILE* fp, 
                 const char* title, 
                 unsigned int nCharts, 
                 const struct Highchart* highcharts);

#endif /* __HTML_H__ */