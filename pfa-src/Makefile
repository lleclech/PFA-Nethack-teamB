CC=gcc

INCLUDE = ../nh-setup/nethack-3.4.3/include/
CFLAGS=-Wall -Wextra -I $(INCLUDE)
LFLAGS=
all: test 

test: test_bot_handler.o bot_handler.o $(wildcard *.h)
	${CC} -o $@ $^ ${LFLAGS}

%.o: %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c $< 

run_test: test
	@./test

run_valgrind: test
	valgrind ./test

clean:
	@rm -f *~ *.o test
