#ifndef __SERIE_H__
#define __SERIE_H__

#define SERIE_FREE(x)	{ if(x != NULL) { serie__free(x); x = NULL; } }

#define SERIE_DATATYPE_INT   0
#define SERIE_DATATYPE_FLOAT 1

#define SERIE_TYPE_NON    -1
#define SERIE_TYPE_LINE    0
#define SERIE_TYPE_SPLINE  1
#define SERIE_TYPE_COLUMN  2

#include <stdio.h>

struct Serie
{
	char* name;
  int type;
  int axis;
	unsigned int nbData;
	unsigned int datatype;
	union {
		int* data_int;
    float* data_float;
	};
};

void serie__init(struct Serie* serie);

void serie__uninit(struct Serie* serie);

void serie__init_data(struct Serie* serie, unsigned int datatype, unsigned int nb);

void serie__uninit_data(struct Serie* serie);

struct Serie* serie__malloc();

void serie__free(struct Serie* serie);

void serie__fprint(FILE* fp, const struct Serie* serie, unsigned int nb);

#endif
