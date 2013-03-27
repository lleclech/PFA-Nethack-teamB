#ifndef __TITLE_H__
#define __TITLE_H__

#define TITLE_FREE(x)	{ if(x != NULL) { title__free(x); x = NULL; } }

struct Title {
	char* text;		// NULL by default
	/*
	int x;
	*/
};

void title__init(struct Title* title);

void title__uninit(struct Title* title);

struct Title* title__malloc();

void title__free(struct Title* title);

void title__print(struct Title* title, const char* subtitle);

#endif /* __TITLE_H__ */