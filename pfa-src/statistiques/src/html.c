#include "html.h"

#include <stdio.h>

#define VARIABLE_PREFIX  "chart"

void print_jssrc(const char* js)
{
	printf("<script type=\"text/javascript\" src=\"%s\"></script>", js);
}

void print_common_head(const char* title)
{
	printf("<!DOCTYPE HTML><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><title>%s</title>", title);
	print_jssrc("js/jquery-1.8.3.min.js");
	printf("<script type=\"text/javascript\">$(function() {");
}

void print_common_body()
{
	printf("});</script></head><body>");
	print_jssrc("js/Highcharts-2.3.3/highcharts.js");
	print_jssrc("js/Highcharts-2.3.3/modules/exporting.js");
}

void print_common_foot()
{
	printf("</body></html>");
}

void print_js_declarations(unsigned int nCharts)
{
	unsigned int i;
	for(i = 0; i < nCharts; ++i)
		printf("var %s%u;", VARIABLE_PREFIX, i);
}

void print_js_definitions(unsigned int nCharts, struct Highchart* highcharts)
{
	unsigned int i;
	for(i = 0; i < nCharts; ++i)
	{
		printf("%s%u", VARIABLE_PREFIX, i);
		highchart__print(highcharts + i);
	}
}

void print_javascript(unsigned int nCharts, struct Highchart* highcharts)
{
	print_js_declarations(nCharts);
	printf("$(document).ready(function(){");
	print_js_definitions(nCharts, highcharts);
	printf("});");
}

void print_containers(unsigned int nCharts, struct Highchart* highcharts)
{
	unsigned int i;
	for(i = 0; i < nCharts; ++i)
		printf("<div id=\"%s\" style=\"min-width: 400px; height: 400px; margin: 0 auto\"></div>", 
		highcharts[i].chart.renderTo);
}

void print_html(const char* title, unsigned int nCharts, struct Highchart* highcharts)
{
	print_common_head(title);
	print_javascript(nCharts, highcharts);
	print_common_body();
	print_containers(nCharts, highcharts);
	print_common_foot();
}