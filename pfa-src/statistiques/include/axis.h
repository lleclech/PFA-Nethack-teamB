#ifndef __AXIS_H__
#define __AXIS_H__

#include "title.h"

#define AXIS_FREE(x)	{ if(x != NULL) { axis__free(x); x = NULL; } }

#define CATEGORY_INT 0
#define CATEGORY_STR 1

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

struct Axis* axis__malloc();

void axis__free(struct Axis* axis);

void axis__print(struct Axis* axis, const char* name);

#endif /* __AXIS_H__ */
