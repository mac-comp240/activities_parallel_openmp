CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
LFLAGS = -fopenmp

all: forkJoin spmd

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)


clean:
	rm -f forkJoin
	rm -f spmd

