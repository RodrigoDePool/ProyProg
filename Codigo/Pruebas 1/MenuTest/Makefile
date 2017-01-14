all:menutest clean
	
menutest: menutest.o interface.o rectangles.o menu.o  object.o space.o world.o lineread.o
	gcc -o menutest menutest.o interface.o rectangles.o menu.o world.o object.o space.o lineread.o

menutest.o: menutest.c ../../menu.h
	gcc -c menutest.c

interface.o: ../../interface.c ../../interface.h
	gcc -c ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c ../../rectangles.c

menu.o: ../../menu.c ../../menu.h
	gcc -c ../../menu.c

world.o: ../../world.c ../../world.h
	gcc -c ../../world.c
	
object.o: ../../object.c ../../object.h
	gcc -c ../../object.c
	
space.o: ../../space.c ../../space.h
	gcc -c ../../space.c	
	
lineread.o: ../../lineread.c ../../lineread.h
	gcc -c ../../lineread.c
		
clean:
	mv menutest ../../menutest
	rm *.o