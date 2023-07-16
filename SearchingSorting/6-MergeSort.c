#include <stdio.h>

void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void merge(int *a, int mid, int low, int high){

    int i = low;
    int j = mid+1;  
    int k = low;
    int b[100];

    while(i <= mid && j<=high){
        
        if(a[i]<a[j]){
            b[k] = a[i];
            i++; k++;
        }
        else{
            b[k] = a[j];
            k++; j++;
        }
    }

    while(i<=mid){
        b[k] = a[i];
        i++; k ++;
    }

    while(j<=high){
        b[k] = a[j];
        j++; k ++;
    }

    for(int i = 0; i<= high; i++){
        a[i] = b[i];
    }
}

void mergesort(int *a, int low, int high){
    
    int mid = (low+high)/2;
    if(low < high){
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        merge(a, mid, low, high);
    }
    
}

int main()
{
    // int A[] = {9, 14, 4, 8, 7, 5, 6};
    int A[] = {9, 1, 4, 14, 4, 15, 6, 67, 8097};
    int n = 9;
    printArray(A, n);
    mergesort(A, 0, 8);
    printArray(A, n);
    return 0;
}
