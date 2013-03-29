#ifndef __CHART_H__
#define __CHART_H__

#include <stdio.h>

#define CHART_FREE(x)	{ if(x != NULL) { chart__free(x); x = NULL; } }

#define CHART_TYPE_LINE   0
#define CHART_TYPE_BAR    1
#define CHART_TYPE_COUNT  2

const char* chart_type_str[CHART_TYPE_COUNT];

struct Chart {
	char* renderTo;
	unsigned int type;	// LINE by default
	int inverted;		// 0 by default

	/*
	int marginRight;
	int marginBottom;
	*/
};

void chart__init(struct Chart* chart);

void chart__uninit(struct Chart* chart);

struct Chart* chart__malloc();

void chart__free(struct Chart* chart);

void chart__fprint(FILE* fp, const struct Chart* chart);

#endif /* __CHART_H__ */