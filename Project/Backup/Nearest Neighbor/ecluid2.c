#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>  
#include <stdlib.h>
#include <float.h>
#include "quickSelection.c"
#include "struct.h" 

//double distance [10000][10000] ;
int main(int argc, char **argv){
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
	
	struct Distance *nodeDistance = malloc(sizeof(struct Distance)*nodeNumber);
	// struct Nodes * outputNode=malloc(sizeof(struct Nodes)*nodeNumber);
	// struct Distance *outputNodeDistance = malloc(sizeof(struct Distance)*nodeNumber);

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

	struct timeval before;
	struct timeval after;
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
			
			// nodes[i].neighbourDistance= malloc(sizeof(double)*N);
			// nodes[i].neighbourID= malloc(sizeof(double)*N);
			// outputNode[i].neighbourDistance= malloc(sizeof(double)*N);
			// outputNode[i].neighbourID= malloc(sizeof(double)*N);
			

			nodeDistance[i].neighbourDistance= malloc(sizeof(double)*N);
			nodeDistance[i].neighbourID= malloc(sizeof(double)*N);
			// outputNodeDistance[i].neighbourDistance= malloc(sizeof(double)*N);
			// outputNodeDistance[i].neighbourID= malloc(sizeof(double)*N);
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
	
	gettimeofday(&before, NULL);

	#pragma omp parallel for private (first,second) shared(nodeDistance,nodes)
	for (first=0;first<nodeNumber;first++){
		//CODE MOTION
		int x = nodes[first].x;
		int y = nodes[first].y;
		double max=DBL_MAX;
		int maxIndex=0;
		int empty=0;
		double *n_distance = nodeDistance[first].neighbourDistance;
		int *id = nodeDistance[first].neighbourID;
		//printf("new element : %d\n", first );

		for(second=0;second<nodeNumber;second++){
			// ORIGINAL
			// double sq1 = (nodes[first].x-nodes[second].x)*(nodes[first].x-nodes[second].x);
			// double sq2 = (nodes[first].y-nodes[second].y)*(nodes[first].y-nodes[second].y);
			//CODE MOTION
			double x1= x-nodes[second].x;
			double y1 = y-nodes[second].y;
			//double x1= 0.0;
			//double y1 = 0.0;
			double sq1=x1*x1;
			double sq2 = y1*y1;
			double distance =sq1+sq2;
			//printf(" distance :%f,  empty : %d\n",distance, empty);
			if((distance<max) || (empty < N)){
				
				if(empty==N){
					//printf("%s:%d\n",__FUNCTION__,__LINE__ );
					n_distance[maxIndex]=distance;
					id[maxIndex] = second;

				}else{
					//printf("%s:%d\n",__FUNCTION__,__LINE__ );
					n_distance[empty]=distance;
					id[empty] = second;
				//	nodes[first].neighbourDistance[empty]=distance;
				//	nodes[first].neighbourID[empty] = second;
					empty++;
				}
				
				max = 0.00;

				for(int i=0;i<empty;i++){
					if (n_distance[i] > max) {
						//max = nodes[first].neighbourDistance[i];
						max = n_distance[i];
						maxIndex = i;
					}
				}

				//printf("maxIndex : %d and max element %f at line %d\n", maxIndex, max,  __LINE__);
			}
			// double sq1 = (x-nodes[second].x)*(x-nodes[second].x);
			// double sq2 = (y-nodes[second].y)*(y-nodes[second].y);
				
			// nodeDistance[first].neighbourDistance[second]=sq1 + sq2;
			// nodeDistance[first].neighbourID[second]=second;
			

			// distance[first][second]=sq1+sq2;
			//distance[first][second]=sq1 + sq2;
			// nodes[first].neighbourID[second]=second;
			// nodes[first].neighbourDistance[second]=sq1 + sq2;
		}

	}
	gettimeofday(&after, NULL);
	FILE *f = fopen("ec2.txt", "w");

	int x=0;
	int y=0;
	for (y=0;y<nodeNumber;y++){
		for (x=0;x<N;x++){
			fprintf(f,"Current Node : %d\t ID : %d\tDistance : %f\n",y,nodeDistance[y].neighbourID[x],nodeDistance[y].neighbourDistance[x]);
		}
	}
	fclose(f);


	double timeVal = (double)(after.tv_sec - before.tv_sec) +
	(double)(after.tv_usec - before.tv_usec) / 1e6;

	printf("%f", timeVal);
	
	return 0;


}
