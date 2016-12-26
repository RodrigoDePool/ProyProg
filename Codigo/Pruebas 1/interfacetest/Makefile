all: interfacetest interfacetestVal

interfacetest: interfacetest.o interface.o rectangles.o
	gcc -o interfacetest interfacetest.o interface.o rectangles.o

imaptest: imaptest.o interface.o rectangles.o
	gcc -o imaptest imaptest.o interface.o rectangles.o

interfacetestVal: interfacetestVal.o interface.o rectangles.o
	gcc -o interfacetestVal interfacetestVal.o interface.o rectangles.o

interfacetest.o: interfacetest.c ../../interface.h
	gcc -c -g interfacetest.c

imaptest.o: imaptest.c ../../interface.h
	gcc -c -g imaptest.c

interfacetestVal.o: interfacetestVal.c ../../interface.h
	gcc -c -g interfacestestVal.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm -f *.o interfacetest interfacetestVal
