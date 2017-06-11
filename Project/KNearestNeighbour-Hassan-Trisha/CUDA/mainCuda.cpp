#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>  
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "struct2.h" 

#include "omp.h"

extern void distanceMain(const int N,const int nodeNumber,const int * x, const int * y,double * distanceVar, int * index) ;
   

int main(int argc, char **argv)
{
	 //struct timespec start, end;
	if (argc !=4) {
		printf("Please provide all arguments\n");
		return 1;
	}
	//printf("Hello World :D\n");
	int nodeNumber = atoi(argv[1]);
	char* inputFile = argv[2];
	int N = atoi(argv[3]);
	// struct Nodes * nodes = malloc(sizeof(struct Nodes)*nodeNumber);
	// struct Nodes * outputNode=malloc(sizeof(struct Nodes)*nodeNumber);

	int * x = (int*)malloc(sizeof(int)*nodeNumber);
	int * y = (int*)malloc(sizeof(int)*nodeNumber);
	double * distance = (double*)malloc(sizeof(double)*nodeNumber*nodeNumber);
	int * index =(int*)malloc(sizeof(int)*nodeNumber*nodeNumber);

	char *str;
	FILE *fp;
	char * line = (char*)malloc(sizeof(char)*1000);
	size_t len = 0;
	size_t read;
	int i=0;
	int j=0;

	fp = fopen(argv[2], "r");
	if (fp == NULL){
		printf("Error Opening file\n");
		return 1;
	}
	char * digit;
	while ((read = getline(&line, &len, fp)) != -1) {
		if(i>=nodeNumber){
			printf("Error, more points in file than number specified\n");
			return 1;
		}
		digit= strtok(line," ");
		while(digit!=NULL){
			x[i]=atoi(digit);
			digit=strtok(NULL," ");
			y[i]=atoi(digit);
			digit=strtok(NULL," ");
		}
		i++;
	}
	if(i<nodeNumber){
		printf("Error Number of points in file less then the number specified\n");
		return 1;
	}
	fclose(fp);
	//clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	//#pragma omp parallel for
	int first=0;
	int second=0;
	struct timeval before;
	struct timeval after;
	gettimeofday(&before, NULL);
	



	distanceMain( N,nodeNumber,x,y,distance,index);


	// for(int i=0;i<nodeNumber*nodeNumber;i++){
	// 	printf("Index: %d\t Neighbor Index: %d\tDistance: %f\n",i/nodeNumber,index[i],distance[i] );
	// }


	// int currentNode=0;
	// #pragma omp parallel for private (currentNode)
	// for(currentNode=0;currentNode<(nodeNumber);currentNode++){
	// 	outputNode[currentNode].neighbourDistance=sort(nodes[currentNode].neighbourDistance,nodes[currentNode].neighbourID,nodeNumber,N);
	// }
	gettimeofday(&after, NULL);
	double timeVal = (double)(after.tv_sec - before.tv_sec) +
	(double)(after.tv_usec - before.tv_usec) / 1e6;
	// // double swap=0;
	// // int idswap=0;
	// // int currentNode=0;
	// // int c=0;
	// // int d=0;
	// // for (currentNode=0;currentNode<nodeNumber;currentNode++){
	// // 	for (c = 0 ; c < ( nodeNumber - 1 ); c++)
	// // 	{
	// // 		for (d = 0 ; d < nodeNumber - c - 1; d++)
	// // 		{
	// // 			if (nodes[currentNode].neighbourDistance[d] > nodes[currentNode].neighbourDistance[d+1]) /* For decreasing order use < */
	// // 	 		 {
	// // 				//swapping distance
	// // 				swap = nodes[currentNode].neighbourDistance[d];
	// // 				nodes[currentNode].neighbourDistance[d]   = nodes[currentNode].neighbourDistance[d+1];
	// // 				nodes[currentNode].neighbourDistance[d+1] = swap;
					
	// // 				//swapping id
	// // 				idswap = nodes[currentNode].neighbourID[d];
	// // 				nodes[currentNode].neighbourID[d]   = nodes[currentNode].neighbourID[d+1];
	// // 				nodes[currentNode].neighbourID[d+1] = idswap;
	// // 	  		}
	// // 		}
	// //  	 }
	// // }
	// //clock_gettime(CLOCK_MONOTONIC_RAW, &end);
 	// float delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
  //   printf("%f\n",delta_us); 

			
			// printf("Current Node : 1\t Id: %f \t Distance : %f\n",nodes[1].neighbourID[0],nodes[1].neighbourDistance[0]);

	// //FILE *f = fopen("output.txt", "w");
	// FILE *f = fopen("output5.txt", "w");

	// int x=0;
	// int y=0;
	// for (y=0;y<nodeNumber;y++){
	// 	for (x=0;x<N;x++){
	// 		fprintf(f,"Current Node : %d\t ID : %d\tDistance : %f\n",y,nodes[y].neighbourID[x],outputNode[y].neighbourDistance[x]);
	// 	}
	// }

	// // int x=0;
	// // int y=0;
	// // for (y=0;y<nodeNumber;y++){
	// // 	for (x=0;x<N;x++){
	// // 		fprintf(f,"Current Node : %d\t ID: %d\tDistance : %f\n",y,nodes[y].neighbourID[x],nodes[y].neighbourDistance[x]);
	// // 	}
	// // }
	// fclose(f);
	printf("Total run time : %f\n", timeVal);
	return 0;



}