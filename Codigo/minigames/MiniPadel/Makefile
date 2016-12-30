all: padelPrueba

padelPrueba: padelPrueba.o miniPadel.o interface.o rectangles.o
	gcc -o padelPrueba padelPrueba.o miniPadel.o  interface.o rectangles.o -lpthread
	
padelPrueba.o: padelPrueba.c miniPadel.h
	gcc -c -g padelPrueba.c

miniPadelo: miniPadel.c miniPadel.h
	gcc -c -g miniPadel.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm -f *.o
