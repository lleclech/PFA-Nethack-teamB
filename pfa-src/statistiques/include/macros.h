#ifndef __MACROS_H__
#define __MACROS_H__

#define ATTRIBUTE_BEGIN(x)	printf("%s:{", x)
#define ATTRIBUTE_END		printf("},")

#define SEQUENCE_BEGIN(x)	printf("%s:[", x)
#define SEQUENCE_END		printf("],")

#define SAFE_FREE(x)	{ if(x != NULL) { free(x); x = NULL; } }

#define BOOL_STR(x)   ((x) ? "true" : "false")

#endif /* __MACROS_H__ */