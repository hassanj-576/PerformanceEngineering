double selectKth(double* arr, int k, int len) {
 
 int from = 0, to = len - 1;
 
 // if from == to we reached the kth element
 while (from < to) {
  int r = from, w = to;
  double mid = arr[(r + w) / 2];
 
  // stop if the reader and writer meets
  while (r < w) {
 
   if (arr[r] >= mid) { // put the large values at the end
    double tmp = arr[w];
    arr[w] = arr[r];
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


double* sort(double * array,int* indexArray, int size, int N ){


 double * dupplicate = malloc(sizeof(double)*size);
  for(int i=0;i<size;i++){
    dupplicate[i]=array[i];
  }
  double *  unsorted = malloc(sizeof(double)*N);
  int * unsoretedIndex =malloc(sizeof(int)*N);
  double kth = selectKth(dupplicate,N-1,size);
 
  int j=0;
  int i=0;
  for(i=0;i<size;i++){
    if(array[i]<kth){
      unsorted[j]=array[i];
      unsoretedIndex[j]=indexArray[i];
      
      j++;
    }
  }
 
  while(j<N){
   
     array[j]=kth;
    
     j++;
  }
  return unsorted;

}
