#include "axis.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

void axis__init(struct Axis* axis)
{
	title__init(&(axis->title));
	axis->nbCategories = CATEGORY_INT;
	axis->category_int = NULL;
}

void axis__uninit(struct Axis* axis)
{
	title__uninit(&(axis->title));
	switch(axis->categorytype)
	{
	case CATEGORY_INT:
		SAFE_FREE(axis->category_int);
		break;
	case CATEGORY_STR:
		SAFE_FREE(axis->category_str);
		break;
	}
}

struct Axis* axis__malloc()
{
	struct Axis* axis = (struct Axis*)malloc(sizeof(struct Axis));
	if(axis != NULL)
		axis__init(axis);
	return axis;
}

void axis__free(struct Axis* axis)
{
	axis__uninit(axis);	
	free(axis);
}


void axis__print(struct Axis* axis, const char* name)
{
	unsigned int i;
	ATTRIBUTE_BEGIN(name);
	title__print(&(axis->title), "title");

	if(axis->nbCategories > 0)
	{
		SEQUENCE_BEGIN("categories");
		for (i = 0; i < axis->nbCategories; ++i)
		{
			if(i > 0)
				putchar(',');
			switch(axis->categorytype)
			{
			case CATEGORY_INT:
				printf("%d", axis->category_int[i]);
				break;
			case CATEGORY_STR:
				printf("'%s'", axis->category_str[i]);
				break;
			}
		}
		SEQUENCE_END;
	}
	ATTRIBUTE_END;
}