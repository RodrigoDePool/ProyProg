worldtest: worldtest.o world.o object.o interface.o space.o rectangles.o lineread.o
	gcc -o worldtest worldtest.o world.o object.o interface.o space.o rectangles.o lineread.o

worldtest.o: worldtest.c ../../world.h
	gcc -c -g worldtest.c

world.o: ../../world.c ../../world.h
	gcc -c -g ../../world.c

object.o: ../../object.c ../../object.h
	gcc -c -g ../../object.c

space.o: ../../space.c ../../space.h
	gcc -c -g ../../space.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c

lineread.o: ../../lineread.c ../../lineread.h
	gcc -c -g ../../lineread.c

clean:
	rm -f *.o worldtest