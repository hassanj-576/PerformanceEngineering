all: convo triangle sobel convoPar convoOpt triangleOpt sobelOpt

convo: convo.c
		gcc-7 -o convo -O3 convo.c  
convoOpt: convoOpt.c
		gcc-7 -o convoOpt -O3 convoOpt.c  
convoPar: convoPar.c
		gcc-7 -o convoPar -O3 convoPar.c -fopenmp  

triangle: triangle.c
		gcc-7 -o triangle -O3 triangle.c  -std=gnu99

triangleOpt: triangleOpt.c
		gcc-7 -o triangleOpt -O3 triangleOpt.c  -std=gnu99

sobel: sobel.c
		gcc-7 -o sobel -O3 sobel.c  -std=gnu99
sobelOpt: sobelOpt.c
		gcc-7 -o sobelOpt -O3 sobelOpt.c  -std=gnu99

clean:
		rm  convo triangle convoOpt convoPar triangleOpt sobelOpt sobel