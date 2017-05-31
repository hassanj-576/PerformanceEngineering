all: main 

main: main.c
		gcc -o main -O2 main.c
