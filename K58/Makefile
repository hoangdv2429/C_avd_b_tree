CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: K58

K58 : K58.o
	$(CC) -w K58.o Graph.c libfdr.a -o pr

K58.o: K58.c
	$(CC) -w $(CFLAGS) K58.c

clean:
	rm -f *.o *-
