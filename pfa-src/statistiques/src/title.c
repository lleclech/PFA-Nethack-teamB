#include "title.h"

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

void title__init(struct Title* title)
{
	title->text = NULL;
}

void title__uninit(struct Title* title)
{
	SAFE_FREE(title->text);
}

struct Title* title__malloc()
{
	struct Title* title = (struct Title*)malloc(sizeof(struct Title));
	if(title != NULL)
		title__init(title);
	return title;
}

void title__free(struct Title* title)
{
	title__uninit(title);
	free(title);
}

void title__print(struct Title* title, const char* subtitle)
{
	ATTRIBUTE_BEGIN(subtitle);
	if(title->text != NULL)
		printf("text:'%s',", title->text);
	ATTRIBUTE_END;
}