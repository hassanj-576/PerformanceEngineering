all: main 
main: main.c
	gcc -o main -O2 -ftree-vectorize main.c -lrt -std=c99 -fopenmp
clean:
		rm  main
