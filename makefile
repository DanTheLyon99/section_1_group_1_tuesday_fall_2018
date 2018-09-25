all: run main cells game scores
clean:
	-rm *.o $(objects)
run: main.o cells.o game.o scores.o
	gcc -Wall -ansi -pedantic -std=c99 -o run main.o cells.o game.o scores.o
main: main.c cells.h game.h
	gcc -Wall -ansi -pedantic -std=c99 -o main.o -c main.c
cells: cells.c cells.h game.h
	gcc -Wall -ansi -pedantic -std=c99 -o cells.o -c cells.c
game: game.c cells.h game.h
	gcc -Wall -ansi -pedantic -std=c99 -o game.o -c game.c
scores: scores.c cells.h game.h
	gcc -Wall -ansi -pedantic -std=c99 -o scores.o -c scores.c
