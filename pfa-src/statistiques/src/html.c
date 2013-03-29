#include "html.h"

#include <stdio.h>

#include "macros.h"

#define VARIABLE_PREFIX  "chart"

void fprint_jssrc(FILE* STAT_FP, const char* js)
{
	STAT_PRINTF("<script type=\"text/javascript\" src=\"%s\"></script>", js);
}

void fprint_common_head(FILE* STAT_FP, const char* title)
{
	STAT_PRINTF("<!DOCTYPE HTML><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><title>%s</title>", title);
	fprint_jssrc(fp, "js/jquery-1.8.3.min.js");
	STAT_PRINTF("<script type=\"text/javascript\">$(function() {");
}

void fprint_common_body(FILE* STAT_FP)
{
	STAT_PRINTF("});</script></head><body>");
	fprint_jssrc(fp, "js/Highcharts-2.3.3/highcharts.js");
	fprint_jssrc(fp, "js/Highcharts-2.3.3/modules/exporting.js");
}

void fprint_common_foot(FILE* STAT_FP)
{
	STAT_PRINTF("</body></html>");
}

void fprint_js_declarations(FILE* STAT_FP, unsigned int nCharts)
{
	unsigned int i;
	for(i = 0; i < nCharts; ++i)
		STAT_PRINTF("var %s%u;", VARIABLE_PREFIX, i);
}

void fprint_js_definitions(FILE* STAT_FP, unsigned int nCharts, const struct Highchart* highcharts)
{
	unsigned int i;
	for(i = 0; i < nCharts; ++i)
	{
		STAT_PRINTF("%s%u", VARIABLE_PREFIX, i);
		highchart__fprint(fp, highcharts + i);
	}
}

void fprint_javascript(FILE* STAT_FP, unsigned int nCharts, const struct Highchart* highcharts)
{
	fprint_js_declarations(fp, nCharts);
	STAT_PRINTF("$(document).ready(function(){");
	fprint_js_definitions(fp, nCharts, highcharts);
	STAT_PRINTF("});");
}

void fprint_containers(FILE* STAT_FP, unsigned int nCharts, const struct Highchart* highcharts)
{
	unsigned int i;
	for(i = 0; i < nCharts; ++i)
		STAT_PRINTF("<div id=\"%s\" style=\"min-width: 400px; height: 400px; margin: 0 auto\"></div>", 
		  highcharts[i].chart.renderTo);
}

void fprint_html(FILE* STAT_FP, 
                 const char* title, 
                 unsigned int nCharts, 
                 const struct Highchart* highcharts)
{
	fprint_common_head(fp, title);
	fprint_javascript(fp, nCharts, highcharts);
	fprint_common_body(fp);
	fprint_containers(fp, nCharts, highcharts);
	fprint_common_foot(fp);
}