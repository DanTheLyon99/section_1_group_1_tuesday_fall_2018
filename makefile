all: boggle run board_generator dictionary scoreboard word_checker
clean:
	-rm *.o $(objects) run
run: boggle.o board_generator.o dictionary.o scoreboard.o word_checker.o
	gcc -Wall -ansi -pedantic -std=c99 -o run boggle.o board_generator.o dictionary.o scoreboard.o word_checker.o
boggle: boggle.c
	gcc -Wall -ansi -pedantic -std=c99 -o boggle.o -c boggle.c
board_generator: board_generator.c board_generator.h
	gcc -Wall -ansi -pedantic -std=c99 -o board_generator.o -c board_generator.c
dictionary: dictionary.c dictionary.h
	gcc -Wall -ansi -pedantic -std=c99 -o dictionary.o -c dictionary.c
scoreboard: scoreboard.c scoreboard.h
	gcc -Wall -ansi -pedantic -std=c99 -o scoreboard.o -c scoreboard.c
word_checker: word_checker.c word_checker.h
	gcc -Wall -ansi -pedantic -std=c99 -o word_checker.o -c word_checker.c
