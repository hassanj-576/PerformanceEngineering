all: matrixPar
matrixPar: matrixPar.c
		gcc -o matrixPar -O2 -ftree-vectorize matrixPar.c -lrt -fopenmp  -std=gnu99
clean:
		rm  matrixPar