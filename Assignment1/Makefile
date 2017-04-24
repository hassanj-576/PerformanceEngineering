all: matrix matrixvec optimatrix optimatrixvec optimatrix2 optimatrixvec2 matrixPar

matrix: matrix.c
		gcc -o matrix -O2 matrix.c -lrt -std=gnu99

matrixvec: matrix.c
		gcc -o matrixvec -O2 -ftree-vectorize matrix.c -lrt -std=gnu99

optimatrix : matrix2.c
		gcc -o optimatrix -O2 matrix2.c -lrt  -std=gnu99

optimatrixvec: matrix2.c
		gcc -o optimatrixvec -O2 -ftree-vectorize matrix2.c -lrt  -std=gnu99

optimatrix2 : matrix3.c
		gcc -o optimatrix2 -O2 matrix3.c -lrt  -std=gnu99

optimatrixvec2: matrix3.c
		gcc -o optimatrixvec2 -O2 -ftree-vectorize matrix3.c -lrt  -std=gnu99

matrixPar: matrixPar.c
		gcc -o matrixPar -O2 -ftree-vectorize matrixPar.c -lrt -fopenmp  -std=gnu99
clean:
		rm  matrix matrixvec optimatrix optimatrixvec optimatrix2 optimatrixvec2 matrixPar