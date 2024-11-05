CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
LFLAGS = -fopenmp

all: forkJoin spmd arraySPMD private iterPatterns leaderWorker reduction

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)


clean:
	rm -f forkJoin
	rm -f spmd
	rm -f arraySPMD
	rm -f private
	rm -f iterPatterns
	rm -f leaderWorker
	rm -f reduction

