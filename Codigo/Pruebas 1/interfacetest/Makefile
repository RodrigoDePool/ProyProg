all: interfacetest

interfacetest: interfacetest.o interface.o rectangles.o
	gcc -o interfacetest interfacetest.o interface.o rectangles.o


interfacetest.o: interfacetest.c interface.h
	gcc -c interfacetest.c

interface.o: ../../interface.c interface.h
	gcc -c ../../interface.c

rectangles.o: ../../rectangles.c rectangles.h
	gcc -c ../../rectangles.c

clean:
	rm *.o
