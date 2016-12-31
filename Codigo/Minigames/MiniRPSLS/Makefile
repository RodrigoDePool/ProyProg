all: RPSLStest

RPSLStest: RPSLStest.o interface.o miniRPSLS.o rectangles.o
	gcc -o RPSLStest RPSLStest.o interface.o miniRPSLS.o rectangles.o

RPSLStest.o: RPSLStest.c
	gcc -c -g RPSLStest.c

miniRPSLS.o: miniRPSLS.c miniRPSLS.h
	gcc -c -g miniRPSLS.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

clean:
	rm *.o
