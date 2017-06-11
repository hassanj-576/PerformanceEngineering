all: naive selectionAlgo2  selectionAlgo customAlgo customAlgo2
selectionAlgo2: selectionAlgo2.c
	gcc -o selectionAlgo2 -O2 -ftree-vectorize selectionAlgo2.c -lrt -std=c99 -fopenmp
naive: naive.c
	gcc -o naive -O2 -ftree-vectorize naive.c -lrt -std=c99 -fopenmp
selectionAlgo: selectionAlgo.c
	gcc -o selectionAlgo -O2 -ftree-vectorize selectionAlgo.c -lrt -std=c99 -fopenmp

customAlgo: customAlgo.c
	gcc -o customAlgo -O2 -ftree-vectorize customAlgo.c -lrt -std=c99 -fopenmp
customAlgo2: customAlgo2.c
	gcc -o customAlgo2 -O2 -ftree-vectorize customAlgo2.c -lrt -std=c99 -fopenmp
clean:
		rm  naive selectionAlgo2  selectionAlgo customAlgo customAlgo2
