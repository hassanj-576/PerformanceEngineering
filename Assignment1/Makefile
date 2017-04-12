all: matrix matrixvec optimatrix optimatrixvec optimatrix2 optimatrixvec2

matrix: matrix.c
		gcc -o matrix -O2 matrix.c -lrt

matrixvec: matrix.c
		gcc -o matrixvec -O2 -ftree-vectorize matrix.c -lrt

optimatrix : matrix2.c
		gcc -o optimatrix -O2 matrix2.c -lrt

optimatrixvec: matrix2.c
		gcc -o optimatrixvec -O2 -ftree-vectorize matrix2.c -lrt

optimatrix2 : matrix3.c
		gcc -o optimatrix2 -O2 matrix3.c -lrt

optimatrixvec2: matrix3.c
		gcc -o optimatrixvec2 -O2 -ftree-vectorize matrix3.c -lrt
