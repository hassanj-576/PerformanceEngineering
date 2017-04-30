#include <stdio.h>
#include <string.h>
#include <time.h>  
#include "struct.h" 
#include <math.h>


int main(int argc, char **argv)
{
	if (argc !=3) {
		printf("Please provide all arguments\n");
		return 1;
	}
	printf("Hello World :D\n");
	int nodeNumber = atoi(argv[1]);
	int inputFile = argv[2];
	struct Nodes * nodes = malloc(sizeof(struct Nodes)*nodeNumber);
	char *str;
	FILE *fp;
	char * line = malloc(sizeof(char)*1000);
	size_t len = 0;
	ssize_t read;
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
		}
		i++;
	}
	if(i<nodeNumber){
		printf("Error Number of points in file less then the number specified\n");
		return 1;
	}
	fclose(fp);
	for (int first=0;first<nodeNumber;first++){
		for(int second=0;second<nodeNumber;second++){
			double sq1 = pow((nodes[first].x-nodes[second].x),2);
			double sq2 = pow((nodes[first].y-nodes[second].y),2);
			nodes[first].neighbourDistance[second]=sqrt(sq1 + sq2);
			nodes[first].neighbourID[second]=second;
		}

	}
	double swap=0;
	int idswap=0;
	for (int currentNode=0;currentNode<nodeNumber;currentNode++){
		for (int c = 0 ; c < ( nodeNumber - 1 ); c++)
		{
			for (int d = 0 ; d < nodeNumber - c - 1; d++)
			{
				if (nodes[currentNode].neighbourDistance[d] > nodes[currentNode].neighbourDistance[d+1]) /* For decreasing order use < */
		 		 {
					swap = nodes[currentNode].neighbourDistance[d];
					nodes[currentNode].neighbourDistance[d]   = nodes[currentNode].neighbourDistance[d+1];
					nodes[currentNode].neighbourDistance[d+1] = swap;
					idswap = nodes[currentNode].neighbourID[d];
					nodes[currentNode].neighbourID[d]   = nodes[currentNode].neighbourID[d+1];
					nodes[currentNode].neighbourID[d+1] = idswap;
		  		}
			}
	 	 }
	}


			
			//printf("Current Node : 1\t Id: %f \t Distance : %f\n",nodes[1].neighbourID[0],nodes[1].neighbourDistance[0]);
	FILE *f = fopen("output.txt", "w");

	for (int y=0;y<nodeNumber;y++){
		for (int x=0;x<nodeNumber;x++){
			fprintf(f,"Current Node : %d\t Id: %d \t Distance : %f\n",y,nodes[y].neighbourID[x],nodes[y].neighbourDistance[x]);
		}
	}
	fclose(f);
	return 0;



}