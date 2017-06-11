#include <Timer.hpp>
#include <iostream>
#include <iomanip>
#include <string>
using LOFAR::NSTimer;
using std::cout;
using std::cerr;
using std::endl;
using std::fixed;
using std::string;
using std::setprecision;



__device__ double selectKth(double* arr,int * index, int k, int len, int startIndex) {
// double selectKth(double* arr, int k, int len) {
 
 int from = startIndex, to = (startIndex+len) - 1;
 
 // if from == to we reached the kth element
 while (from < to) {
  int r = from, w = to;
  double mid = arr[(r + w) / 2];
 
  // stop if the reader and writer meets
  while (r < w) {
 
   if (arr[r] >= mid) { // put the large values at the end
    double tmp = arr[w];
    int tempIndex=index[w];
    arr[w] = arr[r];
    index[w]=index[r];
    index[r]=tempIndex;
    arr[r] = tmp;
    w--;
   } else { // the value is smaller than the pivot, skip
    r++;
   }
  }
 
  // if we stepped up (r++) we need to step one down
  if (arr[r] > mid)
   r--;
 
  // the r pointer is on the end of the first k elements
  if ((k+startIndex) <= r) {
   to = r;
  } else {
   from = r + 1;
  }
 }
 
 return arr[k+startIndex];
}


//double* sort(double * array,int* indexArray, int size, int N ){
__device__ void sort(double * array,int* indexArray, int size, int N, int startIndex ){

 // double * dupplicate = malloc(sizeof(double)*size);
 //  for(int i=0;i<size;i++){
 //    dupplicate[i]=array[i];
 //  }
  //double *  unsorted = malloc(sizeof(double)*N);
  //int * unsoretedIndex =malloc(sizeof(int)*N);
  // double kth = selectKth(dupplicate,N-1,size);
  double kth = selectKth(array, indexArray, N-1, size, startIndex);
  //printf("Start Index: %d\t Kth Value: %f\n",startIndex,kth );
  
  //printf("\n");
  //printf("\n");
  //printf("Kth Element : %f\n",kth );
  int j=startIndex;
  int i=startIndex;
  for(i=startIndex; i<startIndex+size; i++){
    if(array[i]<kth){

      array[j] = array[i];
      indexArray[j] = indexArray[i];
      //unsoretedIndex[j]=indexArray[i];
      //printf("unsorted in loop : %f\n",unsorted[j] );
      j++;
    }
  }
  //printf("outside for J:%d\n",j);
  while(j<N){
     //printf("J: %d\n",j);
     array[j]=kth;
     //printf("Inside while: Unsorted is : %f\n",unsorted[j]);
     j++;
  }
  //return unsorted;

}

__global__ void distance(const int nodeNumber,const int * x, const int * y,double * distance, int * index) {
		//CODE MOTION

		unsigned int first = (blockIdx.x * blockDim.x) + threadIdx.x;
		unsigned int second = (blockIdx.y * blockDim.y) + threadIdx.y;
		if(first<nodeNumber && second<nodeNumber){
			int x1 = x[first];
			int y1 = y[first];
			double sq1 = (x1-x[second])*(x1-x[second]);
			double sq2 = (y1-y[second])*(y1-y[second]);
			distance[(first*nodeNumber)+second]=sq1 + sq2;
			index[(first*nodeNumber)+second]=second;
			//printf("Distance Calculated for i : %d\t%f\n", );
			//nodes[first].neighbourID[second]=second;
		}

	
}
__global__ void test2( int N, const int nodeNumber, double * distance, int * indexArray) {
		unsigned int first = blockIdx.x * blockDim.x + threadIdx.x;//* blockDim.y+ threadIdx.y * blockDim.x 
		//unsigned int second = (blockIdx.y * blockDim.y) + threadIdx.y;
		
		
		if(first<nodeNumber){
			//printf("FIRST: %d\n",first);
			sort(distance, indexArray, nodeNumber, N, (first*nodeNumber));
			//printf("Distance Calculated for i : %d\t%f\n", );
			//nodes[first].neighbourID[second]=second;
		}
}




// int main(int argc, char **argv)
// {
  
//   int index[10]={0,1,2,3,4,5,6,7,8,9};
//   double arr[10] ={0,3,10,9,7,5,1,6,2,0};
//   //printf("\n");

//   double* kth = sort(arr,index,10,5);
//   //printf("returned \n");
//   for(int i=0;i<5;i++){
//     //printf("Index: %d \t Value: %f\n",index[i],kth[i]);
//   }
//   //printf("\n");
  
//   return 0;
// }
void distanceMain(const int N,const int nodeNumber,const int * x, const int * y,double * distanceVar, int * index) {
	   //Memory Timer		    
	NSTimer memoryTimer("MemoryTimer", false, false);
		//Creating variables to be used by Kernel
	int  * d_x;
	int * d_y;
	int * d_index;
	double * d_distance;

	//unsigned char* d_out;
	//Allocating memory on Device
	cudaMalloc((void**) &d_x, (nodeNumber*sizeof(int)));
	cudaMalloc((void**) &d_y, (nodeNumber*sizeof(int)));
	cudaMalloc((void**) &d_distance, (nodeNumber*nodeNumber*sizeof(double)));
	cudaMalloc((void**) &d_index, (nodeNumber*nodeNumber*sizeof(int)));
	//cudaMalloc((void**) &d_out,width*height);
	memoryTimer.start();
	//Copying from Host to device 
	cudaMemcpy(d_x, x, (nodeNumber*sizeof(int)), cudaMemcpyHostToDevice);
	cudaMemcpy(d_y, y, (nodeNumber*sizeof(int)), cudaMemcpyHostToDevice);
	memoryTimer.stop();
	 //Number of blocks is (width/16)+1 and (height/16)+1. We add 1 to each in case the width or height is not perfectly divisible by 1. We cater for any extra 
	 // threads we get in the kernel
	dim3 gridSize((nodeNumber/16)+1,(nodeNumber/16)+1);
		//16x16 Threads per block (utalizing 256 threads per block)
	dim3 blockSize(16,16);
	//Kernel Timer
	NSTimer kernelTimer = NSTimer("darker", false, false);
	kernelTimer.start();
		// Starting Kernel
	distance<<< gridSize, blockSize >>>(nodeNumber,d_x,d_y,d_distance,d_index);
	cudaDeviceSynchronize();

	dim3 gridSize2((nodeNumber/256)+1,(nodeNumber/1)+1);
    dim3 blockSize2(1,1);
	test2<<<256, 256 >>>(N,nodeNumber,d_distance,d_index);
	cudaDeviceSynchronize();
	kernelTimer.stop();
			  
	memoryTimer.start();
	// Copying Resylts back from Device To Host
	cudaMemcpy(distanceVar, d_distance, (nodeNumber*nodeNumber*sizeof(double)), cudaMemcpyDeviceToHost);
	cudaMemcpy(index, d_index, (nodeNumber*nodeNumber*sizeof(int)), cudaMemcpyDeviceToHost);
	memoryTimer.stop();
	//Printing Time
	cout << "Kernel (s): \t"<<fixed <<setprecision(6)<< kernelTimer.getElapsed() << endl;
  	cout << "Memory (s): \t"<<fixed <<setprecision(6)<< memoryTimer.getElapsed() << endl;


}