#include<stdio.h>

void printArray(int* A, int n){

    for (int i = 0; i < n; i++)
    {
        printf("%d\t", A[i]);
    }
    
}

void insertionSort(int *a, int n){
    
    int key;
    int j;
    // Loop for passes
    for (int i = 1; i < n; i++)
    {
        key = a[i];
        j = i-1;
        while(j >=0 && key < a[j]){

            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

int main(){

    int A[] = {12, 54, 65, 7, 23, 9};
    int n = 6;
    
    insertionSort(A, n);
    printf("\nArray after Insertion Sorting : \n");
    printArray(A, n);
    return 0;
}
