#include "serie.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

const char* serie_type_str[] = {
  "line", "spline", "column"
};

void serie__init_data(struct Serie* serie, unsigned int datatype, unsigned nb)
{
  serie->datatype = datatype;
  serie->nbData = nb;
  if(nb > 0)
  {
    switch(serie->datatype)
	  {
	  case SERIE_DATATYPE_INT:
		  serie->data_int = STAT_MALLOC(int, nb);
		  break;
    case SERIE_DATATYPE_FLOAT:
      serie->data_float = STAT_MALLOC(float, nb);
      break;
	  }
  }
  else
  {
    switch(serie->datatype)
	  {
	  case SERIE_DATATYPE_INT:
		  serie->data_int = NULL;
		  break;
    case SERIE_DATATYPE_FLOAT:
      serie->data_float = NULL;
      break;
	  }
  } 
}

void serie__init(struct Serie* serie)
{
	serie->name = NULL;
  serie->type = -1;
  serie->axis = -1;
	serie->nbData = 0;
	serie->datatype = SERIE_DATATYPE_INT;
	serie->data_int = NULL;
}

void serie__uninit_data(struct Serie* serie)
{
	switch(serie->datatype)
	{
	case SERIE_DATATYPE_INT:
		SAFE_FREE(serie->data_int);
		break;
  case SERIE_DATATYPE_FLOAT:
    SAFE_FREE(serie->data_float);
    break;
	}
}

void serie__uninit(struct Serie* serie)
{
	SAFE_FREE(serie->name);
  serie->type = -1;
  serie->axis = -1;
  serie__uninit_data(serie);
}

struct Serie* serie__malloc()
{
	struct Serie* serie = STAT_MALLOC_1(struct Serie);
	if(serie != NULL)
		serie__init(serie);
	return serie;
}

void serie__free(struct Serie* serie)
{
	serie__uninit(serie);
	free(serie);
}

void serie__fprint(FILE* STAT_FP, const struct Serie* serie, unsigned int nb)
{
  unsigned int i, j;
  SEQUENCE_BEGIN("series");
  for(i = 0; i < nb; ++i, ++serie)
  {
    if(i > 0)
      STAT_PUTC(',');
    STAT_PUTC('{');
    if(serie->name != NULL)
      STAT_PRINTF("name:'%s',", serie->name);
    if(serie->type != SERIE_TYPE_NON)
      STAT_PRINTF("type:'%s',", serie_type_str[serie->type]);
    if(serie->axis != -1)
      STAT_PRINTF("yAxis:%d,", serie->axis);

    STAT_PRINTF("data:[");
		for(j = 0; j < serie->nbData; ++j)
		{
			if(j > 0)
				STAT_PUTC(',');
			switch(serie->datatype)
			{
			case SERIE_DATATYPE_INT:
				STAT_PRINTF("%d", serie->data_int[j]);
				break;
      case SERIE_DATATYPE_FLOAT:
        STAT_PRINTF("%f", serie->data_float[j]);
        break;
			}
		}
    STAT_PRINTF("]}");
  }
  SEQUENCE_END;
}
