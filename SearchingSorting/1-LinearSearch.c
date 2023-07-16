#include<stdio.h>

int linearsearch(int *a, int element, int index){

    for(int index = 0; index < 10 ; index++){
        if(a[index] == element)
            return index;
    }       
    return -1;
}

int main(){

    int arr[10];
    for(int i = 0; i < 10 ; i++){
        scanf("%d",&arr[i]);
    }
    printf("The index of element in array is: %d", linearsearch(arr,34,0));
    
}