all: convo tranigle sobel convoPar

convo: convo.c
		gcc-7 -o convo -O3 convo.c  
convoPar: convoPar.c
		gcc-7 -o convoPar -O3 convoPar.c -fopenmp  

tranigle: tranigle.c
		gcc -o tranigle -O3 tranigle.c  -std=gnu99
sobel: sobel.c
		gcc -o sobel -O3 sobel.c  -std=gnu99

clean:
		rm  convo tranigle