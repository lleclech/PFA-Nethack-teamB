CC=gcc

CFLAGS=-Wall -Wextra
LFLAGS=
PFAOBJ = bot_handler.o middle_man.o interface_mm.o db_manager.o math_tool.o prmath.o
INCLUDE = $(wildcard *.h) 
all: test $(PFAOBJ) 

test: test_bot_handler.o bot_handler.o
	${CC} -o $@ $^ ${LFLAGS}

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $<

run_test: test
	@./test

run_valgrind: test
	valgrind ./test

clean:
	@rm -f *~ *.o test
