all: main

main: main.o interface.o rectangles.o
	gcc -o main main.o interface.o rectangles.o

main.o: main.c ../../interface.h
	gcc -c -g main.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm -f *.o main
