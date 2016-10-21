all: spacefromfile

spacefromfile: spacefromfile.o space.o
		gcc -o spacefromfile spacefromfile.o space.o


spacefromfile.o: spacefromfile.c
		gcc -c -g -pedantic -Wall spacefromfile.c
space.o: space.c space.h types.h
	gcc -c -g -pedantic -Wall space.c

clean:
	rm -f *.o *.exe

