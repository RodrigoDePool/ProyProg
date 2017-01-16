all: exeAn1

exeAn1: an1test.o animations.o interface.o rectangles.o
	gcc -o exeAn1 an1test.o animations.o interface.o rectangles.o -pthread
an1test.o: an1test.c
	gcc -c -g an1test.c
animations.o: animations.c animations.h
	gcc -c -g -Wall animations.c -lpthread

interface.o: ../interface.c ../interface.h
	gcc -c -g ../interface.c

rectangles.o: ../rectangles.c ../rectangles.h
	gcc -c -g ../rectangles.c

clean:
	rm *.o
