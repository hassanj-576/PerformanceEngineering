all: main mainSimple main2 ec2 ec
main: main.c
	gcc -o main -O2 -ftree-vectorize main.c -lrt -std=c99 -fopenmp
mainSimple: mainSimple.c
	gcc -o mainSimple -O2 -ftree-vectorize mainSimple.c -lrt -std=c99 -fopenmp
main2: main2.c
	gcc -o main2 -O2 -ftree-vectorize main2.c -lrt -std=c99 -fopenmp

ec2: ecluid2.c
	gcc -o ec2 -O2 -ftree-vectorize ecluid2.c -lrt -std=c99 -fopenmp
ec: ecluid.c
	gcc -o ec -O2 -ftree-vectorize ecluid.c -lrt -std=c99 -fopenmp
clean:
		rm  main ec2 mainSimple main2
