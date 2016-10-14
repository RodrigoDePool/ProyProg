CC = gcc -pedantic
CFLAGS = -Wall -g

testSpace.o : testSpace.c space.h space.c types.h
	$(CC) $(CFLAGS) -c  testSpace.c

space.o : space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c

testSpace : testSpace.o space.o types.h
	$(CC) $(CFLAGS) -o testSpace testSpace.o space.o

clean : rm -f *.o mainPruebasSpace
