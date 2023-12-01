#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student {
    int roll_no;
    float cpi;
    char name[10];
}student;

void swap(student* a, student* b) {
    student temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(student* arr, int size, int curr) {
    
    while (2 * curr <= size) {

        int left_child = 2 * curr;
        int right_child = 2 * curr + 1;
        int max_child = left_child;

        if (right_child <= size && arr[right_child].roll_no > arr[left_child].roll_no)
            max_child = right_child;
        if (arr[max_child].roll_no < arr[curr].roll_no)
            return; 

        swap(&arr[curr], &arr[max_child]);
        curr = max_child;
    }
}

void remove(student* arr, int* size) {
    swap(&arr[1], &arr[*size]);
    (*size)--;
    heapify(arr, *size, 1);
}

void HeapSort(student* arr, int size) {
    for (int i = (size / 2); i > 0; i--) {
        heapify(arr, size, i);
    }
    while (size)
        remove(arr, &size);
}

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    student* arr = (student*)malloc(sizeof(student) * (n + 1));

    for (int i = 1; i <= n; i++) {
        printf("Enter roll number, name, cgpa of student %d: ", i);
        scanf("%d %s %f", &arr[i].roll_no, arr[i].name, &arr[i].cpi);
    }

    HeapSort(arr, n);

    for (int i = 1; i <= n; i++)
        printf("Rollno: %d, Name: %s, CGPA: %f\n", arr[i].roll_no, arr[i].name, arr[i].cpi);

    free(arr); // Don't forget to free the dynamically allocated memory.

    return 0;
}
