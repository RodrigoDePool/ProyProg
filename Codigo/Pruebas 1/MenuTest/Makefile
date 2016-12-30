all:menutest clean
	
menutest: menutest.o interface.o rectangles.o menu.o
	gcc -o menutest menutest.o interface.o rectangles.o menu.o

menutest.o: menutest.c ../../menu.h
	gcc -c menutest.c

interface.o: ../../interface.c ../../interface.h
	gcc -c ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c ../../rectangles.c

menu.o: ../../menu.c ../../menu.h
	gcc -c ../../menu.c
	
clean:
	mv menutest ../../menutest
	rm *.o