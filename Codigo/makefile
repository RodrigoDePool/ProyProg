all:  main

main: main.o world.o space.o interface.o rectangles.o menu.o
	gcc -o main $^
	
world.o: world.c world.h
	gcc -c -g world.c

space.o: space.c space.h
	gcc -c -g space.c

interface.o: interface.c interface.h
	gcc -c -g interface.c

rectangles.o: rectangles.c rectangles.h
	gcc -c -g rectangles.c

main.o: main.c
	gcc -c $^
	
menu.o: menu.c menu.h
	gcc -c menu.c

clean:
	rm -f *.o 