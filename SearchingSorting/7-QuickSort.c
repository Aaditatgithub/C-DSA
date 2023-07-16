#include <stdio.h>

void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int partition(int *a, int low, int high){

int pivot = a[low];
int i = low+1;
int j = high;
int temp;

do{

    while(a[i] <= pivot){
        i++;
    }
    while(a[j] > pivot){
        j--;
    }   
    if(i<j){
        //swap a[i] and a[j]
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

}while(i<j);

// swap a[j] and a[low]

temp = a[low];
a[low] = a[j];
a[j] = temp;
return j;
}

void quicksort(int *a, int low, int high){

    int partitionindex;
    if(low<high){

        partitionindex = partition(a, low, high);
        quicksort(a,low, partitionindex-1);
        quicksort(a,partitionindex+1,high);
    }
}

int main()
{
   
    int A[] = {12, 4, 1, 845, 7, 5, 6};
    
    int n = 7;
    printArray(A, n);
    quicksort(A, 0, n - 1);
    printArray(A, n);
    return 0;
}