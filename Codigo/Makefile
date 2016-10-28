all: space.o object.o player.o world.o

world.o: world.c world.h player.h object.h space.h types.h
	gcc -c -g -pedantic -Wall world.c

player.o: player.c player.h types.h
	gcc -c -g -pedantic -Wall player.c

object.o: object.c object.h types.h
	gcc -c -g -pedantic -Wall object.c

space.o: space.c space.h types.h
	gcc -c -g -pedantic -Wall space.c



clean:
	rm -f *.o *.exe
