#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define data_t	float 
static int STARTOFFSET=2;
static int ENDOFFSET =3;
data_t filter5x5[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 2.0f, 3.0f, 2.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
data_t filter3x3[] = {-1.0f, 0.0f, 1.0f, -2.0f, 0.0f, 2.0f, -1.0f, 0.0f, 1.0f};

void convolution(data_t *inData, data_t *outData, const int width, const int height,data_t *filter) {

	for ( int y = 0; y < height; y++ ) {
	   for ( int x = 0; x < width; x++ ) {
	   		int outterIndex=(y * width) + x;
		   	unsigned int filterItem = 0;
		   	for ( int fy = y - STARTOFFSET; fy < y + ENDOFFSET; fy++ ) {
		   		int innerIndex=fy*width;
		   		for ( int fx = x - STARTOFFSET; fx < x + ENDOFFSET; fx++ ) {
			   		if ( ((fy < 0) || (fy >= height)) || ((fx < 0) || (fx >= width)) ) {
						filterItem++;
						//printf("Filter Item inside: %d\n",filterItem);
						continue;
					}
			   		//outData[(y * width) + x] += inData[(fy * width) + fx] * filter[filterItem];
			   		//outData[outterIndex] += inData[(fy * width) + fx] * filter[filterItem];
			   		//printf("Filter Item: %d\t Filter: %f\n",filterItem,filter[filterItem]);
			   		outData[outterIndex] += inData[(innerIndex) + fx] * filter[filterItem];
			   		filterItem++;
	   			}
			}
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
	if (argc != 4) {
		printf("Please enter the width and height of the image and Kernel type (3 or 5)\n");
		return 0;
	}
	width = strtol(argv[1], 0, 10);
	height = strtol(argv[2], 0, 10);
	kernel=strtol(argv[3], 0, 10);

	data_t *inputData,*outputData,*filter ; 
	if(kernel==3){
		printf("inside kernel\n");
		filter=(data_t *)malloc(9*sizeof(data_t));
		filter=filter3x3;
		
    	STARTOFFSET=2;
    	
    	ENDOFFSET=1;
		printf("Start offset: %d\n",STARTOFFSET);

	}
	else if(kernel==5){
		filter=(data_t *)malloc(25*sizeof(data_t));
		filter=filter5x5;


	}else{
		printf("Wrong Value for kernel, exiting\n");
		return -1;
	}
	inputData = (data_t *)malloc(width*height*sizeof(data_t));
	outputData = (data_t *)malloc(width*height*sizeof(data_t));

	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			inputData[i*height + j] = rand()%255;
			outputData[i*height + j] = 0;
		}
	}
	gettimeofday(&before, NULL);
	convolution(inputData,outputData,width,height,filter);


	gettimeofday(&after, NULL);
	printf("Start offset: %d\n",STARTOFFSET);


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
