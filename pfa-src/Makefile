CC=gcc

NHDIR= ../nh-setup/nethack-3.4.3
INCLUDE = $(NHDIR)/include/
CFLAGS=-Wall -Wextra -I $(INCLUDE)
LFLAGS=
all: pfa test bot_rw bot_sp

export PFADIR=../../pfa-src
export PFAOBJ=bot_handler.o middle_man.o interface_mm.o math_tool.o prmath.o db_manager.o

pfa: $(PFAOBJ) 
	@( mv $(PFAOBJ) $(NHDIR)/src; cd $(NHDIR); $(MAKE) && $(MAKE) install)

bot_sp:
	$0 java_starter_package/build.sh
bot_rw:
	$0 java_rand_walk/build.sh

makedefs:
	@( cd $(NHDIR); cd util ; \
		$(MAKE) makedefs ../include/onames.h ../include/pm.h ../src/monstr.c ../include/vis_tab.h ../src/tile.c)

%.o: %.c $(wildcard *.h) makedefs
	$(CC) $(CFLAGS) -c $< 

clean:
	@rm -f *~ *.o test
