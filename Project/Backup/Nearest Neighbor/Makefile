all: main ec2
main: main.c
	gcc -o main -O2 -ftree-vectorize main.c -lrt -std=c99 -fopenmp

ec2: ecluid2.c
	gcc -o ec2 -O2 -ftree-vectorize ecluid2.c -lrt -std=c99 -fopenmp
clean:
		rm  main ec2
