#ifndef __SERIE_H__
#define __SERIE_H__

#define SERIE_FREE(x)	{ if(x != NULL) { serie__free(x); x = NULL; } }

#define SERIE_DATATYPE_INT 0

struct Serie
{
	char* name;
	unsigned int nbData;
	unsigned int datatype;
	union {
		int* data_int;
	};
};

void serie__init(struct Serie* serie);

void serie__uninit(struct Serie* serie);

struct Serie* serie__malloc();

void serie__free(struct Serie* serie);

#endif