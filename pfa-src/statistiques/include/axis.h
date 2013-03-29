#ifndef __AXIS_H__
#define __AXIS_H__

#include "title.h"

#define AXIS_FREE(x)	{ if(x != NULL) { axis__free(x); x = NULL; } }

#define CATEGORY_INT 0
#define CATEGORY_STR 1

#define AXIS_X 0
#define AXIS_Y 1

struct Axis {
	//int reversed;
	struct Title title;
	unsigned int nbCategories;
	unsigned int categorytype;
	union{
		int* category_int;
		char** category_str;
	};
};

void axis__init(struct Axis* axis);

void axis__uninit(struct Axis* axis);

void axis__init_category(struct Axis* axis, 
                         unsigned int categorytype, 
                         unsigned int nbCategories);

void axis__uninit_category(struct Axis* axis);

struct Axis* axis__malloc();

void axis__free(struct Axis* axis);

void axis__fprint(FILE* fp, const struct Axis* axis, unsigned int ax, unsigned int nb);

#endif /* __AXIS_H__ */
