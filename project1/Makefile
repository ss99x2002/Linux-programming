CC=gcc
CFLAGS=-O

smallsh : main.o smallsh.o
	gcc -o smallsh main.o smallsh.o

main.o : main.c
	gcc -c -o main.o main.c
smallsh.o : smallsh.c
	gcc -c -o smallsh.o smallsh.c
clean:
	rm -f *.o smallsh
