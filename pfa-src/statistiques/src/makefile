CC=gcc
CFLAGS=-I../include -Wall -Wextra
LDFLAGS=-lsqlite3 -lm
EXE=statistiques
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, ${SRCS})

.phony: all clean

all: ${EXE}

${EXE}: ${OBJS}
	${CC} -o $@ $^ $(LDFLAGS)

%.o : %.c
	${CC} -o $@ -c $< ${CFLAGS}

clean:
	-rm -f *.o ${EXE}
