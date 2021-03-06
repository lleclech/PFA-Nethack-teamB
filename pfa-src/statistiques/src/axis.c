#include "axis.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

void axis__init(struct Axis* axis)
{
	title__init(&(axis->title));
  axis__init_category(axis, CATEGORY_INT, 0);
}

void axis__uninit(struct Axis* axis)
{
	title__uninit(&(axis->title));
	axis__uninit_category(axis);
}

void axis__init_category(struct Axis* axis, 
                         unsigned int categorytype, 
                         unsigned int nbCategories)
{
  axis->categorytype = categorytype;
  axis->nbCategories = nbCategories;
  axis->category_int = NULL;

  if(nbCategories > 0)
  {
    switch(categorytype)
    {
    case CATEGORY_INT:
      axis->category_int = STAT_MALLOC(int, nbCategories);
      break;
    case CATEGORY_STR:
      axis->category_str = STAT_MALLOC(char*, nbCategories);
      {
        unsigned int i = 0;
        for(; i < nbCategories; ++i)
          axis->category_str[i] = NULL;
      }
      break;
    }
  }
}

void axis__uninit_category(struct Axis* axis)
{
  switch(axis->categorytype)
	{
	case CATEGORY_INT:
		SAFE_FREE(axis->category_int);
		break;
	case CATEGORY_STR:
    {
      unsigned int i = 0;
      for(; i < axis->nbCategories; ++i)
        SAFE_FREE(axis->category_str[i]);
    }
		SAFE_FREE(axis->category_str);
		break;
	}

  axis->categorytype = CATEGORY_INT;
  axis->nbCategories = 0;
}

struct Axis* axis__malloc()
{
	struct Axis* axis = STAT_MALLOC_1(struct Axis);
	if(axis != NULL)
		axis__init(axis);
	return axis;
}

void axis__free(struct Axis* axis)
{
	axis__uninit(axis);	
	free(axis);
}


void axis__fprint(FILE* STAT_FP, const struct Axis* axis, unsigned int ax, unsigned int nb)
{
	unsigned int i, j;
  const char* name;

  if(ax == AXIS_X)
    name = "xAxis";
  else if(ax == AXIS_Y)
    name = "yAxis";
  else
    return;

  SEQUENCE_BEGIN(name);
  
  for(i = 0; i < nb; ++i, ++axis)
  {
    if(i > 0)
      STAT_PUTC(',');

    STAT_PUTC('{');

    if(axis->nbCategories > 0)
    {
      SEQUENCE_BEGIN("categories");
    
      for(j = 0; j < axis->nbCategories; ++j)
      {
        if(j > 0)
          STAT_PUTC(',');
        switch(axis->categorytype)
        {
        case CATEGORY_INT:
			  	STAT_PRINTF("%d", axis->category_int[j]);
			  	break;
			  case CATEGORY_STR:
			  	STAT_PRINTF("'%s'", axis->category_str[j]);
			  	break;
        }
      }
      SEQUENCE_END;
    }

    title__fprint(STAT_FP, &(axis->title), "title");

    STAT_PUTC('}');
  }

  SEQUENCE_END;
}
