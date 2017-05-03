#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 1000

int histo[256];
int *image;

void compute_histo_thread (int length, int width)
{

  int i, j, index = 0;
  #pragma omp parallel for shared (histo) private (i,j)
  for (i = 0; i < width; i++) {
    for (j = 0; j < length; j++) {
      index = image[i*(length) + j];
      /* START CRITICAL REGION */
      #pragma omp critical 
      {
        histo[index] += 1;
      }
      /* END CRITICAL REGION */
    }
  }
}


int main(int argc, char **argv)
{

  int width, length;
  struct timeval before;
  struct timeval after;
  double time;
  int num_threads;
  int i, j;
  int start, end = 0;

  if (argc != 3) {
    printf("Please enter the width and length of the image and number of threads spawned\n");
    return 0;
  }

  width = strtol(argv[1], 0, 10);
  length = strtol(argv[2], 0, 10);

  

  image = (int *)malloc(width*length*sizeof(int));

  for (i = 0; i < width; i++) {
    for (j = 0; j < length; j++) {
      image[i*length + j] = rand()%255;
    }
  }

  for (i=0;i<256;i++)
    histo[i]=0;

  gettimeofday(&before, NULL);
  compute_histo_thread(length,width);

  
  gettimeofday(&after, NULL);

  time = (double)(after.tv_sec - before.tv_sec) +
        (double)(after.tv_usec - before.tv_usec) / 1e6;

  printf("Total run time : %f\n", time);

 for (i=0;i<256;i++){
  printf("Value of Index %d : %d\n",i,histo[i] );
 }

  return 0;

}
