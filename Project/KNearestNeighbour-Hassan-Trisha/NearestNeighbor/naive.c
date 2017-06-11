#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>  
#include "struct2.h" 
#include <math.h>
#include <time.h>
#include "quickSelection.c"
#include "omp.h"


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
	struct Nodes * nodes = malloc(sizeof(struct Nodes)*nodeNumber);
	//struct Nodes * outputNode=malloc(sizeof(struct Nodes)*nodeNumber);
	char *str;
	FILE *fp;
	char * line = malloc(sizeof(char)*1000);
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
			nodes[i].x=atoi(digit);
			digit=strtok(NULL," ");
			nodes[i].y=atoi(digit);
			digit=strtok(NULL," ");
			nodes[i].neighbourDistance= malloc(sizeof(double)*nodeNumber);
			nodes[i].neighbourID= malloc(sizeof(double)*nodeNumber);
			//outputNode[i].neighbourDistance= malloc(sizeof(double)*N);
			//outputNode[i].neighbourID= malloc(sizeof(double)*N);
		}
		i++;
	}
	free(line);
	if(i<nodeNumber){
		printf("Error Number of points in file less then the number specified\n");
		return 1;
	}
	fclose(fp);
	//clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	//#pragma omp parallel for
	int first=0;
	int second=0;
	struct timeval ecStart,ecEnd, sortStart,sortEnd;


	struct timeval before;
	struct timeval after;
	gettimeofday(&before, NULL);
	
	
	for (first=0;first<nodeNumber;first++){
		int x = nodes[first].x;
		int y = nodes[first].y;
		for(second=0;second<nodeNumber;second++){
			double sq1 = (x-nodes[second].x)*(x-nodes[second].x);
			double sq2 = (y-nodes[second].y)*(y-nodes[second].y);
			nodes[first].neighbourDistance[second]=sq1 + sq2;
			nodes[first].neighbourID[second]=second;
		}

	}
	
	
	double swap=0;
	int idswap=0;
	int currentNode=0;
	int c=0;
	int d=0;
	for (currentNode=0;currentNode<nodeNumber;currentNode++){
		for (c = 0 ; c < ( nodeNumber - 1 ); c++)
		{
			for (d = 0 ; d < nodeNumber - c - 1; d++)
			{
				if (nodes[currentNode].neighbourDistance[d] > nodes[currentNode].neighbourDistance[d+1]) /* For decreasing order use < */
		 		 {
					//swapping distance
					swap = nodes[currentNode].neighbourDistance[d];
					nodes[currentNode].neighbourDistance[d]   = nodes[currentNode].neighbourDistance[d+1];
					nodes[currentNode].neighbourDistance[d+1] = swap;
					
					//swapping id
					idswap = nodes[currentNode].neighbourID[d];
					nodes[currentNode].neighbourID[d]   = nodes[currentNode].neighbourID[d+1];
					nodes[currentNode].neighbourID[d+1] = idswap;
		  		}
			}
	 	 }
	}
	gettimeofday(&after, NULL);

	FILE *f = fopen("naive.txt", "w");

	int x=0;
	int y=0;
	for (y=0;y<nodeNumber;y++){
		for (x=0;x<N;x++){
			fprintf(f,"Current Node : %d\t ID : %d\tDistance : %f\n",y,nodes[y].neighbourID[x],nodes[y].neighbourDistance[x]);
		}
	}

	fclose(f);
	for(int i=0;i<nodeNumber;i++){
		free(nodes[i].neighbourDistance);
		free(nodes[i].neighbourID);
	}
	free (nodes);
	
	double timeVal = (double)(after.tv_sec - before.tv_sec) +
	(double)(after.tv_usec - before.tv_usec) / 1e6;


	printf("%f", timeVal);
	return 0;



}