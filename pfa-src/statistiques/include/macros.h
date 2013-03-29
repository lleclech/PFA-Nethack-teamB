#ifndef __MACROS_H__
#define __MACROS_H__

#define ATTRIBUTE_BEGIN(x)	fprintf(fp, "%s:{", x)
#define ATTRIBUTE_END		fprintf(fp, "},")

#define SEQUENCE_BEGIN(x)	fprintf(fp, "%s:[", x)
#define SEQUENCE_END		fprintf(fp, "],")

#define SAFE_FREE(x)	{ if(x != NULL) { free(x); x = NULL; } }

#define BOOL_STR(x)   ((x) ? "true" : "false")

#define STAT_MALLOC_1(t)  ((t*)malloc(sizeof(t)))
#define STAT_MALLOC(t, n) ((t*)malloc(sizeof(t) * (n)))

#define STAT_FP fp
#define STAT_PUTC(c) fputc((c), fp)
#ifdef WIN32
#define STAT_PRINTF(...) fprintf(fp, __VA_ARGS__)
#else
#define STAT_PRINTF(args...) fprintf(fp, ##args)
#endif

#endif /* __MACROS_H__ */