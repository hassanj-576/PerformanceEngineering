all: convo triangle sobel convoPar convoOpt triangleOpt sobelOpt

convo: convo.c
		gcc -o convo -O3 convo.c  -std=gnu99
convoOpt: convoOpt.c
		gcc -o convoOpt -O3 convoOpt.c  -std=gnu99
convoPar: convoPar.c
		gcc -o convoPar -O3 convoPar.c -fopenmp  -std=gnu99

triangle: triangle.c
		gcc -o triangle -O3 triangle.c  -std=gnu99

triangleOpt: triangleOpt.c
		gcc -o triangleOpt -O3 triangleOpt.c  -std=gnu99

sobel: sobel.c
		gcc -o sobel -O3 sobel.c  -std=gnu99
sobelOpt: sobelOpt.c
		gcc -o sobelOpt -O3 sobelOpt.c  -std=gnu99

clean:
		rm  convo triangle convoOpt convoPar triangleOpt sobelOpt sobel