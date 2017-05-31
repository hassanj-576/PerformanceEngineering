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


void sobelOpt1(data_t *inData, data_t *outData, const int width, const int height) {

	for ( int y = 1; y < height-1; y++ ) {
		for ( int x = 1; x < width-1; x++ ) {
			int outterIndex=(y * width) + x;
			unsigned int filterItem = 0;
			float magX = 0.0f;
			float magY = 0.0f;

			magX= inData[(x-1+((y-1)*width))]*filterX[0]+inData[(x+((y-1)*width))]*filterX[1]+inData[(x+1+((y-1)*width))]*filterX[2]
			+inData[(x-1+((y)*width))]*filterX[3]+inData[(x+((y)*width))]*filterX[4]+inData[(x+1+((y)*width))]*filterX[5]
			+inData[(x-1+((y+1)*width))]*filterX[6]+inData[(x+((y+1)*width))]*filterX[7]+inData[(x+1+((y+1)*width))]*filterX[8];

			magY= inData[(x-1+((y-1)*width))]*filterY[0]+inData[(x+((y-1)*width))]*filterY[1]+inData[(x+1+((y-1)*width))]*filterY[2]
			+inData[(x-1+((y)*width))]*filterY[3]+inData[(x+((y)*width))]*filterY[4]+inData[(x+1+((y)*width))]*filterY[5]
			+inData[(x-1+((y+1)*width))]*filterY[6]+inData[(x+((y+1)*width))]*filterY[7]+inData[(x+1+((y+1)*width))]*filterY[8];

			outData[x+(y*width)]=sqrt((magX*magX)+(magY*magY));
		}
	}
	
}
void sobelOpt2(data_t *inData, data_t *outData, const int width, const int height) {

	for ( int y = 1; y < height-1; y++ ) {
		for ( int x = 1; x < width-1; x++ ) {
			int outterIndex=(y * width) + x;
			unsigned int filterItem = 0;
			float magX = 0.0f;
			float magY = 0.0f;

			float magX1= inData[(x-1+((y-1)*width))]*filterX[0]+inData[(x+((y-1)*width))]*filterX[1]+inData[(x+1+((y-1)*width))]*filterX[2];
			float magX2=inData[(x-1+((y)*width))]*filterX[3]+inData[(x+((y)*width))]*filterX[4]+inData[(x+1+((y)*width))]*filterX[5];
			float magX3=inData[(x-1+((y+1)*width))]*filterX[6]+inData[(x+((y+1)*width))]*filterX[7]+inData[(x+1+((y+1)*width))]*filterX[8];
			magX=magX1+magX2+magX3;

			float magY1= inData[(x-1+((y-1)*width))]*filterY[0]+inData[(x+((y-1)*width))]*filterY[1]+inData[(x+1+((y-1)*width))]*filterY[2];
			float magY2=inData[(x-1+((y)*width))]*filterY[3]+inData[(x+((y)*width))]*filterY[4]+inData[(x+1+((y)*width))]*filterY[5];
			float magY3=inData[(x-1+((y+1)*width))]*filterY[6]+inData[(x+((y+1)*width))]*filterY[7]+inData[(x+1+((y+1)*width))]*filterY[8];

			magY=magY1+magY2+magY3;
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
	sobelOpt2(inputData,outputData,width,height);


	gettimeofday(&after, NULL);
	//printf("Start offset: %d\n",STARTOFFSET);


	timeVal = (double)(after.tv_sec - before.tv_sec) +
	(double)(after.tv_usec - before.tv_usec) / 1e6;
	

	
	printf("Total run time : %f\n", timeVal);
	   
	
  	return 0;
 
}