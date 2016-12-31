all: snaketest

snaketest: snaketest.o snake.o interface.o rectangles.o
	gcc -o snaketest snaketest.o snake.o interface.o rectangles.o -pthread
snaketest.o: snaketest.c
	gcc -c -g snaketest.c
snake.o: snake.c snake.h
	gcc -c -g -Wall snake.c -lpthread

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm *.o
