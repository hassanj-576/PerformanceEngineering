all: matrix matrixvec optimatrix optimatrixvec optimatrix2 optimatrixvec2 matrixPar

matrix: matrix.c
		gcc-7 -o matrix -O2 matrix.c  -std=gnu99

matrixvec: matrix.c
		gcc-7 -o matrixvec -O2 -ftree-vectorize matrix.c  -std=gnu99

optimatrix : matrix2.c
		gcc-7 -o optimatrix -O2 matrix2.c   -std=gnu99

optimatrixvec: matrix2.c
		gcc-7 -o optimatrixvec -O2 -ftree-vectorize matrix2.c   -std=gnu99

optimatrix2 : matrix3.c
		gcc-7 -o optimatrix2 -O2 matrix3.c   -std=gnu99

optimatrixvec2: matrix3.c
		gcc-7 -o optimatrixvec2 -O2 -ftree-vectorize matrix3.c   -std=gnu99

matrixPar: matrixPar.c
		gcc-7 -o matrixPar -O2 -ftree-vectorize matrixPar.c  -fopenmp  -std=gnu99
clean:
		rm  matrix matrixvec optimatrix optimatrixvec optimatrix2 optimatrixvec2 matrixPar