#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define data_t	float 
// #define STARTOFFSET 2;
// #define ENDOFFSET 3;
const data_t filter[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 2.0f, 3.0f, 2.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

void trangleSmoot(data_t *inData, data_t *outData, const int width, const int height) {

	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			int outterIndex=(y * width) + x;
			unsigned int filterItem = 0;
			float filterSum = 0.0f;
			float smoothPix = 0.0f;

			for ( int fy = y - 2; fy < y + 3; fy++ ) {
				int innerIndex=fy*width;
				for ( int fx = x - 2; fx < x + 3; fx++ ) {
					if ( ((fy < 0) || (fy >= height)) || ((fx < 0) || (fx >= width)) ) {
						filterItem++;
						continue;
					}

					smoothPix += inData[(innerIndex) + fx] * filter[filterItem];
					filterSum += filter[filterItem];
					filterItem++;
				}
			}

			smoothPix /= filterSum;
			outData[(outterIndex) + x] = (smoothPix);
		}
	}
	
}
int main(int argc, char **argv){
	int width, height,kernel;
 	struct timeval before;
	struct timeval after;
	double timeVal;
	int num_threads;
	int i, j;
	int start, end = 0;
	if (argc != 3) {
		printf("Please enter the width and height of the image and Kernel type (3 or 5)\n");
		return 0;
	}
	width = strtol(argv[1], 0, 10);
	height = strtol(argv[2], 0, 10);
	data_t *inputData,*outputData,*filter ; 
	
	inputData = (data_t *)malloc(width*height*sizeof(data_t));
	outputData = (data_t *)malloc(width*height*sizeof(data_t));

	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			inputData[i*height + j] = rand()%255;
			outputData[i*height + j] = 0;
		}
	}
	gettimeofday(&before, NULL);
	trangleSmoot(inputData,outputData,width,height);


	gettimeofday(&after, NULL);
	//printf("Start offset: %d\n",STARTOFFSET);


	timeVal = (double)(after.tv_sec - before.tv_sec) +
	(double)(after.tv_usec - before.tv_usec) / 1e6;
	

	// for (i = 0; i < width; i++) {
	// 	for (j = 0; j < height; j++) {
	// 		//printf("%f\t",outputData[i*height + j] );
	// 	}
	// 	//printf("\n");
	// }
	printf("Total run time : %f\n", timeVal);
	   
	// generate data 
	// start timer 
	// call convolution 
	// end timer 
  	return 0;
 
}
