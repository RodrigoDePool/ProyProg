all: coptest

coptest: coptest.o cop.o
	gcc -o coptest coptest.o cop.o

coptest.o: coptest.c
	gcc -c -std=c99 -g coptest.c

cop.o: cop.c cop.h types.h
	gcc -c -std=c99 -g cop.c

clean:
	rm -f *.o coptest *~
