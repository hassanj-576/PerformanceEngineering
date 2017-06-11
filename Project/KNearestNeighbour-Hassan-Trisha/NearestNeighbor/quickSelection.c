double selectKth(double* arr,int * index, int k, int len) {
// double selectKth(double* arr, int k, int len) {
 
 int from = 0, to = len - 1;
 
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
  if (k <= r) {
   to = r;
  } else {
   from = r + 1;
  }
 }
 
 return arr[k];
}


//double* sort(double * array,int* indexArray, int size, int N ){
void sort(double * array,int* indexArray, int size, int N ){

 // double * dupplicate = malloc(sizeof(double)*size);
 //  for(int i=0;i<size;i++){
 //    dupplicate[i]=array[i];
 //  }
  //double *  unsorted = malloc(sizeof(double)*N);
  //int * unsoretedIndex =malloc(sizeof(int)*N);
  // double kth = selectKth(dupplicate,N-1,size);
  double kth = selectKth(array,indexArray,N-1,size);
  
  //printf("\n");
  //printf("\n");
  //printf("Kth Element : %f\n",kth );
  int j=0;
  int i=0;
  for(i=0;i<size;i++){
    if(array[i]<kth){
      array[j]=array[i];
      indexArray[j]=indexArray[i];
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