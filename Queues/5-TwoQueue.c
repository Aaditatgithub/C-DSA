#include<stdio.h>
#include<stdlib.h>

typedef struct twoqueue{
    int f1,r1;
    int f2,r2;
    int *arr;
    int size;
}*ptwoqueue,twoqueue;


void insertQ1(ptwoqueue q, int data){
    if((q->r1 + 1) == (q->r2 - 1)){
        printf("Queue is full..\n");
    }
    else{
        q->arr[++q->r1] = data;
    }
}

void insertQ2(ptwoqueue q, int data){
    if((q->r1 + 1) == (q->r2 - 1)){
        printf("Queue is full..\n");
    }
    else{
        q->arr[--q->r2] = data;
    }
}

void displayQ1(ptwoqueue q){
    for(int i = q->f1 + 1; i <= q->r1; i++){
        printf("%d ",q->arr[i]);
    }printf("\n");
}

void displayQ2(ptwoqueue q){
    for(int i = q->f2 - 1; i >= q->r2; i--){
        printf("%d ",q->arr[i]);
    }printf("\n");
}

void displaymemory(ptwoqueue q){
    for(int i = 0;i < q->size; i++){
        printf("%d ",q->arr[i]);
    }printf("\n");
}

int main(){

    ptwoqueue queue = (ptwoqueue)malloc(sizeof(twoqueue));
    queue->size = 10;
    queue->f1 = queue->r1 = -1;
    queue->f2 = queue->r2 = queue->size;
    queue->arr = (int*)malloc(sizeof(int)*queue->size);

    insertQ1(queue,10);
    insertQ1(queue,50);
    insertQ1(queue,70);
    insertQ2(queue,76);
    insertQ2(queue,98);
    insertQ2(queue,34);
    displayQ1(queue);
    displayQ2(queue);
}