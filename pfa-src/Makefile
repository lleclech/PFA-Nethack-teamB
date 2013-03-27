CC=gcc

INCLUDE = ../nh-setup/nethack-3.4.3/include/
CFLAGS=-Wall -Wextra -I $(INCLUDE)
LFLAGS=
NHDIR= ../nh-setup/nethack-3.4.3
all: pfa test 

export PFADIR=../../pfa-src
export PFAOBJ=bot_handler.o middle_man.o interface_mm.o math_tool.o prmath.o db_manager.o

test: test_bot_handler.o bot_handler.o $(wildcard *.h)
	${CC} -o $@ $^ ${LFLAGS}

pfa: $(PFAOBJ) 
	@( mv $(PFAOBJ) $(NHDIR)/src; cd $(NHDIR); $(MAKE) && $(MAKE) install)

makedefs:
	@( cd $(NHDIR); cd util ; \
		$(MAKE) makedefs ../include/onames.h ../include/pm.h ../src/monstr.c ../include/vis_tab.h ../src/tile.c)

%.o: %.c $(wildcard *.h) makedefs
	$(CC) $(CFLAGS) -c $< 

run_test: test
	@./test

run_valgrind: test
	valgrind ./test

clean:
	@rm -f *~ *.o test
