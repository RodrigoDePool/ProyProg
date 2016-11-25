all: p2_e3 clean

p2_e3: stack-pointer.o point.o p2_e3.o maze.o elestack-point.o
	gcc -g -Wall -ansi -pedantic -o p2_e4 stack-pointer.o p2_e3.o maze.o point.o elestack-point.o

point.o: point.h types.h point.c
	gcc -g -Wall -ansi -pedantic -c point.c

elestack-point.o: elestack-point.c elestack.h point.h types.h
	gcc -g -Wall -ansi -pedantic -c elestack-point.c		

stack-pointer.o: stack-pointer.c point.h stack.h types.h elestack.h
	gcc -g -Wall -ansi -pedantic -c stack-pointer.c

maze.o: Maze.h types.h point.h maze.c 
	gcc -g -Wall -ansi -pedantic -c maze.c

p2_e3.o: p2_e3.c stack.h point.h types.h Maze.h elestack.h
	gcc -g -Wall -ansi -pedantic -c p2_e3.c

clean:
	rm *.o
