all: matrix matrixvec optimatrix optimatrixvec

matrix: matrix.c
		gcc -o matrix -O2 matrix.c -lrt

matrixvec: matrix.c
		gcc -o matrixvec -O2 -ftree-vectorize matrix.c -lrt

optimatrix : matrix2.c
		gcc -o optimatrix -O2 matrix2.c -lrt

optimatrixvec: matrix2.c
		gcc -o optimatrixvec -O2 -ftree-vectorize matrix2.c -lrt
