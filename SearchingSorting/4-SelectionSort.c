#include<stdio.h>

void printArray(int* A, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void selectionsort(int *a, int n){

    int temp;
    for(int i = 0; i < n-1; i++){

        int min = a[i];
        int indexofmin = i;
        int swap = 0;

        for(int j = i+1; j < n; j++)
        {
            if(a[indexofmin] > a[j]){
                indexofmin = j;
                swap = 1;
            }
        }
        if(swap){
            temp = a[indexofmin];
            a[indexofmin] = a[i];
            a[i] = temp; 
        }
        
    }
}

int main(){
    
    int a[] = {12,12,43,123,1,4,6,8};
    int n = 8;

    printArray(a,n);
    selectionsort(a,n);
    printArray(a,n);

}