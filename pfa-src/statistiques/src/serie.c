#include "serie.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

void serie__init(struct Serie* serie)
{
	serie->name = NULL;
	serie->nbData = 0;
	serie->datatype = SERIE_DATATYPE_INT;
	serie->data_int = NULL;
}

void serie__uninit(struct Serie* serie)
{
	SAFE_FREE(serie->name);
	switch(serie->datatype)
	{
	case SERIE_DATATYPE_INT:
		SAFE_FREE(serie->data_int);
		break;
	}
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