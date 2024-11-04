CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
LFLAGS = -fopenmp

all: forkJoin spmd arraySPMD

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)


clean:
	rm -f forkJoin
	rm -f spmd
	rm -f arraySPMD

