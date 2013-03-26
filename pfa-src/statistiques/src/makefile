CC=gcc
CFLAGS=-I../include -Wall -Wextra
EXE=statistiques
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, ${SRCS})

.phony: all clean

all: ${EXE}

${EXE}: ${OBJS}
	${CC} -o $@ $^

%.o : %.c
	${CC} -o $@ -c $< ${CFLAGS}

clean:
	-rm -f *.o ${EXE}
