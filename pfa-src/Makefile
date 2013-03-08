CC=gcc

INCLUDE = ../nh-setup/nethack-3.4.3/include/
CFLAGS=-Wall -Wextra -I $(INCLUDE)
LFLAGS=
all: pfa test 

test: test_bot_handler.o bot_handler.o $(wildcard *.h)
	${CC} -o $@ $^ ${LFLAGS}

makedefs:
	@( cd ../nh-setup/nethack-3.4.3/util ; \
		$(MAKE) makedefs ../include/onames.h ../include/pm.h ../src/monstr.c ../include/vis_tab.h ../src/tile.c)

%.o: %.c $(wildcard *.h) makedefs
	$(CC) $(CFLAGS) -c $< 

run_test: test
	@./test

run_valgrind: test
	valgrind ./test

clean:
	@rm -f *~ *.o test
