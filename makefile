all:  A4chapterRequiem clean

A4chapterRequiem: main.o world.o space.o interface.o rectangles.o menu.o animations.o  countdots.o MiniMaze.o miniPadel.o miniRPSLS.o qa.o snake.o  2048.o calculus.o game.o string.o tutorial.o
	gcc -o A4chapterRequiem $^ -lpthread
	
tutorial.o: Codigo/tutorial.c Codigo/tutorial.h
	gcc -c Codigo/tutorial.c

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

mainPruebas.o: Codigo/mainPruebas.c
	gcc -c $^

2048.o: Codigo/Minigames/2048/2048.c
	gcc -c $^
	
countdots.o: Codigo/Minigames/CountDots/countdots.c
	gcc -c $^

MiniMaze.o: Codigo/Minigames/MiniMaze/MiniMaze.c
	gcc -c $^

miniPadel.o: Codigo/Minigames/MiniPadel/miniPadel.c
	gcc -c $^

miniRPSLS.o: Codigo/Minigames/MiniRPSLS/miniRPSLS.c
	gcc -c $^

qa.o: Codigo/Minigames/preguntas/qa.c
	gcc -c $^

snake.o: Codigo/Minigames/snake/snake.c
	gcc -c $^

calculus.o: Codigo/Minigames/CalculoRapido/calculus.c
	gcc -c $^


animations.o: Codigo/Animations/animations.c
	gcc -c $^

menu.o: Codigo/menu.c Codigo/menu.h
	gcc -c Codigo/menu.c

game.o: Codigo/game.c Codigo/game.h
	gcc -c Codigo/game.c

string.o: Codigo/string.c Codigo/string.h
	gcc -c Codigo/string.c

clean:
	rm -f *.o 
