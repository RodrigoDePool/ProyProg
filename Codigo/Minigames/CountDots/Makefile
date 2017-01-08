all: testCount

testCount: testCount.o countdots.o interface.o rectangles.o
	gcc -o testCount testCount.o countdots.o  interface.o rectangles.o -lpthread
	
testCount.o: testCount.c countdots.h
	gcc -c -g testCount.c

countdotso: countdots.c countdots.h
	gcc -c -g countdots.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm *.o