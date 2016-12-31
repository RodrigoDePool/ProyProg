all: mazetest

mazetest: mazetest.o interface.o MiniMaze.o rectangles.o
	gcc -o mazetest mazetest.o interface.o MiniMaze.o rectangles.o

mazetest.o: mazetest.c
	gcc -c -g mazetest.c

MiniMaze.o: MiniMaze.c MiniMaze.h
	gcc -c -g MiniMaze.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm -f *.o mazetest *~
