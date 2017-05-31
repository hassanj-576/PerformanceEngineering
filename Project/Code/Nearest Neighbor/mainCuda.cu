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

__global__ void distance(const int nodeNumber,const struct Nodes * inputData) {
		//CODE MOTION

		unsigned int first = (blockIdx.x * blockDim.x) + threadIdx.x;
		unsigned int second = (blockIdx.y * blockDim.y) + threadIdx.y;
		if(first<nodeNumber && second<nodeNumber){
			int x = nodes[first].x;
			int y = nodes[first].y;
			double sq1 = (x-nodes[second].x)*(x-nodes[second].x);
			double sq2 = (y-nodes[second].y)*(y-nodes[second].y);
			nodes[first].neighbourDistance[second]=sq1 + sq2;
			nodes[first].neighbourID[second]=second;
		}

	
}

void distanceMain(const int nodeNumber, const struct Nodes * inputNodes) {
	   //Memory Timer		    
	NSTimer memoryTimer("MemoryTimer", false, false);
		//Creating variables to be used by Kernel
	struct Nodes * d_in;
	//unsigned char* d_out;
	//Allocating memory on Device
	cudaMalloc((void**) &d_in, (nodeNumber*sizeof(struct Nodes)));
	//cudaMalloc((void**) &d_out,width*height);
	memoryTimer.start();
	//Copying from Host to device 
	cudaMemcpy(d_in, inputNodes, (nodeNumber*sizeof(struct Nodes)), cudaMemcpyHostToDevice);
	memoryTimer.stop();
	 //Number of blocks is (width/16)+1 and (height/16)+1. We add 1 to each in case the width or height is not perfectly divisible by 1. We cater for any extra 
	 // threads we get in the kernel
	dim3 gridSize((width/16)+1,(height/16)+1);
		//16x16 Threads per block (utalizing 256 threads per block)
	dim3 blockSize(16,16);
	//Kernel Timer
	NSTimer kernelTimer = NSTimer("darker", false, false);
	kernelTimer.start();
		// Starting Kernel
	greyScale<<< gridSize, blockSize >>>(width,height,d_in, d_out);
	cudaDeviceSynchronize();
	kernelTimer.stop();
			  
	memoryTimer.start();
	// Copying Resylts back from Device To Host
	cudaMemcpy(inputNodes, d_in, (nodeNumber*sizeof(struct Nodes)), cudaMemcpyDeviceToHost);
	memoryTimer.stop();
	//Printing Time
	cout << "Kernel (s): \t"<<fixed <<setprecision(6)<< kernelTimer.getElapsed() << endl;
  	cout << "Memory (s): \t"<<fixed <<setprecision(6)<< memoryTimer.getElapsed() << endl;


}