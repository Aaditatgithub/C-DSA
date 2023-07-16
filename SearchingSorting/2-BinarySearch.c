#include<stdio.h>

int binarysearchwithRecursion(int arr[], int low, int high, int element){

    int mid = (low + high)/2;

    if (element == arr[mid]) {
        return mid;
    }
    else if (element < arr[mid]) {
        return binarysearch(arr, low, mid - 1, element);
    }
    else {
        return binarysearch(arr, mid + 1, high, element);
    }
    return -1;

}


int binarySearch(int arr[], int size, int element){
   
   int low = 0;
   int high = size -1;

   while(low<=high){

        int mid = (low+high)/2;
        if(arr[mid] == element)
            return mid;
        
        if(arr[mid] < element)
            low = mid+1;
        else    
            high = mid-1;
   }
   return -1;
    
}



int main(){

    int arr[] = {1,3,5,56,64,73,123,225,444};
    int size = sizeof(arr)/sizeof(int);
    int element = 444;
    int searchIndex = binarysearch(arr, 0, size-1, element);
    printf("The element %d was found at index %d \n", element, searchIndex);
    return 0;
}
