all: test

test: interface_mm.o test_interface_mm.o
	gcc -o test interface_mm.o test_interface_mm.o

interface_mm.o: interface_mm.c interface_mm.h

test_interface_mm.o: test_interface_mm.c interface_mm.h

clean:
	rm -rf *.o && rm -rf *~

mrproper: clean
	rm -rf unnamed-project