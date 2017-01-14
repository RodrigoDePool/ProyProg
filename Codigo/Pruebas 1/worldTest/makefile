worldtest: worldtest.o world.o interface.o space.o rectangles.o
	gcc -o worldtest worldtest.o world.o interface.o space.o rectangles.o

worldtest.o: worldtest.c ../../world.h
	gcc -c -g worldtest.c

world.o: ../../world.c ../../world.h
	gcc -c -g ../../world.c

space.o: ../../space.c ../../space.h
	gcc -c -g ../../space.c

interface.o: ../../interface.c ../../interface.h
	gcc -c -g ../../interface.c

rectangles.o: ../../rectangles.c ../../rectangles.h
	gcc -c -g ../../rectangles.c


clean:
	rm -f *.o worldtest world_new.txt
