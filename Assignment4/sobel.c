#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define data_t	float 
// #define STARTOFFSET 2;
// #define ENDOFFSET 3;
const data_t filterX[] = {-1.0f, 0.0f, 1.0f, -2.0f, 0.0f, 2.0f, -1.0f, 0.0f, 1.0f};
const data_t filterY[] = {-1.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 1.0f};

void sobel1(data_t *inData, data_t *outData, const int width, const int height) {

	for ( int y = 1; y < height-1; y++ ) {
		for ( int x = 1; x < width-1; x++ ) {
			int outterIndex=(y * width) + x;
			unsigned int filterItem = 0;
			float magX = 0.0f;
			float magY = 0.0f;

			for ( int fy = 0; fy <  3; fy++ ) {
				int innerIndex=fy*width;
				for ( int fx = 0; fx <3; fx++ ) {
					int xInd = x+fx-1;
					int yInd = y+fy-1;
					int index= xInd+yInd*width;
					magX+= inData[index]*filterX[fx+(fy*3)];
					magY+= inData[index]*filterY[fx+(fy*3)];
				}
			}
			outData[x+(y*width)]=sqrt((magX*magX)+(magY*magY));
		}
	}
	
}
void sobel2(data_t *inData, data_t *outData, const int width, const int height) {

	for ( int y = 1; y < height-1; y++ ) {
		for ( int x = 1; x < width-1; x++ ) {
			int outterIndex=(y * width) + x;
			unsigned int filterItem = 0;
			float magX = 0.0f;
			float magY = 0.0f;

			for ( int fy = 0; fy <  3; fy++ ) {
				int yInd = y+fy-1;
				int innerIndex=yInd*width;
				int fy3=fy*3;
				for ( int fx = 0; fx <3; fx++ ) {
					int xInd = x+fx-1;
					int index= xInd+innerIndex;
					magX+= inData[index]*filterX[fx+(fy3)];
					magY+= inData[index]*filterY[fx+(fy3)];
				}
			}
			outData[x+(y*width)]=sqrt((magX*magX)+(magY*magY));
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
			outputData[i*height + j] = inputData[i*height + j];
		}
	}
	gettimeofday(&before, NULL);
	sobel2(inputData,outputData,width,height);


	gettimeofday(&after, NULL);
	//printf("Start offset: %d\n",STARTOFFSET);


	timeVal = (double)(after.tv_sec - before.tv_sec) +
	(double)(after.tv_usec - before.tv_usec) / 1e6;
	

	// for (i = 0; i < width; i++) {
	// 	for (j = 0; j < height; j++) {
	// 		printf("%f\t",outputData[i*height + j] );
	// 	}
	// 	printf("\n");
	// }
	printf("Total run time : %f\n", timeVal);
	   
	// generate data 
	// start timer 
	// call convolution 
	// end timer 
  	return 0;
 
}
