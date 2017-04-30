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
        }
        i++;
    }
    printf("value of i: %d\n",i);
    if(i<nodeNumber){
    	printf("Error Number of points in file less then the number specified\n");
    	return 1;
    }

    for (int first=0;first<nodeNumber;first++){
    	for(int second=0;second<nodeNumber;second++){
    		double sq1 = pow((nodes[first].x-nodes[second].x),2);
    		double sq2 = pow((nodes[first].y-nodes[second].y),2);
    		nodes[first].neighbourDistance[second]=sqrt(sq1 + sq2);
    		printf("Distance Calculated: %f\n",nodes[first].neighbourDistance[second]);
    	}

    }



    printf("X value: %f\n",nodes[1].neighbourDistance[0]);
	return 0;



}