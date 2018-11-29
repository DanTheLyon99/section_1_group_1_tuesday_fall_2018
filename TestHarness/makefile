all: run test
clean:
	-rm *.o $(objects)
run: test.o
	gcc -Wall -ansi -pedantic -std=c99 -o run test.o
test: test.c
		gcc -Wall -ansi -pedantic -std=c99 -o test.o -c test.c
