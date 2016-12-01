all: coptest

coptest: coptest.o cop.o
	gcc -o coptest coptest.o cop.o

coptest.o: coptest.c
	gcc -c -g -Wall coptest.c

cop.o: cop.c cop.h types.h
	gcc -c -g -Wall cop.c

clean:
	rm -f *.o core
