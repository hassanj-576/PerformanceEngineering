__global__ void histogram1DCuda(const int width, const int height, const unsigned char * inputImage, unsigned int * histogram){

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
}