#include <stdio.h>

// Function to identify the swapped pair and their positions
void identifySwappedPair(int arr[], int n) {
    int first, middle, last;

    // Find the first element that is greater than its next element
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            first = i;
            break;
        }
    }

    // Find the last element that is greater than its next element
    for (int i = n - 1; i > 0; i--) {
        if (arr[i] < arr[i - 1]) {
            last = i;
            break;
        }
    }

    // Swap the elements to restore the sorted order temporarily
    int temp = arr[first];
    arr[first] = arr[last];
    arr[last] = temp;

    // Check if the array is now sorted
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            middle = i;
            break;
        }
    }

    // Swap the elements back to their original positions
    temp = arr[first];
    arr[first] = arr[last];
    arr[last] = temp;

    printf("Swapped elements: %d and %d\n", arr[first], arr[last]);
    printf("Positions: %d and %d\n", first + 1, last + 1);
}

// Main function for testing
int main() {
    int arr[] = {1, 5, 3, 4, 2, 6}; // Example array with two elements swapped
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    identifySwappedPair(arr, n);

    return 0;
}
