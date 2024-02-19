CC=g++
CFLAGS = -c -Wall

all: hw1shell

prog: hw1shell.o
	$(CC) hw1shell.o -o hw1shell

hw1shell.o: hw1shell.c
	$(CC) $(CFLAGS) hw1shell.c

clean:
	rm -rd *.o
	rm hw1shell
