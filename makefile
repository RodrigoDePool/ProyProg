all:  main clean

main: main.o world.o space.o interface.o rectangles.o menu.o #game.o
	gcc -o main $^
	
world.o: Codigo/world.c Codigo/world.h
	gcc -c -g Codigo/world.c

space.o: Codigo/space.c Codigo/space.h
	gcc -c -g Codigo/space.c

interface.o: Codigo/interface.c Codigo/interface.h
	gcc -c -g Codigo/interface.c

rectangles.o: Codigo/rectangles.c Codigo/rectangles.h
	gcc -c -g Codigo/rectangles.c

main.o: Codigo/main.c
	gcc -c $^
	
menu.o: Codigo/menu.c Codigo/menu.h
	gcc -c Codigo/menu.c

#game.o: Codigo/game.c Codigo/game.h
#	gcc -c Codigo/game.c

clean:
	rm -f *.o 