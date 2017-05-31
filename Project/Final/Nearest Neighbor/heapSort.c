void swap(double *a,  double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}
 
 
int partition(double *A, int left, int right){
 
    double pivot = A[right];
    int i = left, x;
 
    for (x = left; x < right; x++){
        if (A[x] <= pivot){
            swap(&A[i], &A[x]);
            i++;
        }
    }
 
    swap(&A[i], &A[right]);
    return i;
}
 
 
double quickselect(double *A, int left, int right, int k){
 
    //p is position of pivot in the partitioned array
    int p = partition(A, left, right);
 
    //k equals pivot got lucky
    if (p == k-1){
        return A[p];
    }
    //k less than pivot
    else if (k - 1 < p){
        return quickselect(A, left, p - 1, k);
    }
    //k greater than pivot
    else{
        return quickselect(A, p + 1, right, k);
    }
}
 
double ksmallest(double *A, int n, int k){
 
    int left = 0; 
    int right = n - 1; 
 
    return quickselect(A, left, right, k);
}
 
double* call(double* array, int  N, int k)
{

    
    double *sortedArray = malloc(sizeof(double)*k);

    int index=0;
    sortedArray[0]=0;
    for(int i=1;i<=k;i++){
      sortedArray[i]=ksmallest(array, N, i);
    }
    //printf("\n");

    return sortedArray;
}
