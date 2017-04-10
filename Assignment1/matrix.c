#include<stdio.h>
#include<string.h>
#include<time.h>   

int main(int argc, char **argv)
{
	if (argc !=7) {
		//throw error

	}
    struct timespec start, end;
    
	int N1= atoi(argv[2]);
	int M1 =atoi(argv[3]);
	int N2= atoi(argv[5]);
	int M2= atoi(argv[6]);
	int * matrix = malloc(sizeof(int)*N1*M1);
	int * matrix2 = malloc(sizeof(int)*N2*M2);
	if(M1!=N2){
		printf("Dimensions do not match, Exiting Gracefully like we should, aewsome programmers\n");
		return -1;
	}
	char *str;
	FILE *fp, *output;
    char * line = malloc(sizeof(char)*1000);
    size_t len = 0;
    ssize_t read;
    int i=0;
    int j=0;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        printf("Error\n");
    char * digit;
    while ((read = getline(&line, &len, fp)) != -1) {
        digit= strtok(line," ");
        while(digit!=NULL){
        	matrix[i*M1+j]=atoi(digit);
        	j++;
        	digit=strtok(NULL," ");
        }
        j=0;
        i++;
    
    }

    fclose(fp);

    i=0;
    j=0;

    fp = fopen(argv[4], "r");
    if (fp == NULL)
        printf("Error\n");
    while ((read = getline(&line, &len, fp)) != -1) {
        digit= strtok(line," ");
        while(digit!=NULL){
        	matrix2[i*M2+j]=atoi(digit);
        	j++;
        	digit=strtok(NULL," ");
        }
        i++;
        j=0;
    }
    fclose(fp);
    if (line)
        free(line);
    FILE *f = fopen("output.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* print some text */
	
   clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int * ans= malloc(sizeof(int)*N1*M2);
    for(i=0;i<N1;i++){
    	for (j=0;j<M2;j++){
    		ans[i*M2+j]=0;
    		for(int k=0;k<M1;k++){
    			ans[i*M2+j]+=matrix[i*M1+k]*matrix2[k*M2+j];

    		}
    		
    		fprintf(f,"%d\t",ans[i*M2+j]);
    	}
    	fprintf(f,"\n");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    fclose(f);
    float delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("%f",delta_us);  

	return 0;
}