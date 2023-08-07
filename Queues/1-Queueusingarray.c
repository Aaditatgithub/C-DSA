#include<stdio.h>
#include<stdlib.h>

typedef struct queue{

    int size;
    int f;
    int r;
    int *arr;

}queue;

int isFull(queue *ptr){
    return (ptr->r == ptr->size - 1);
}

int isEmpty(queue *ptr){
    return (ptr->r == ptr->f);
}

void enqueue(queue *ptr, int data){
    if(isFull(ptr)){
        printf("Queue is full\n");
    }
    else{
        ptr->r++;
        ptr->arr[ptr->r] = data;
    }
}

int dequeue(queue *ptr, int data){
    int a = -1;
    if(isFull(ptr)){
        printf("Queue is Empty\n");
    }
    else{
        ptr->f++;
        a = ptr->arr[ptr->f];
    }
    return a;
}

void display(queue *ptr){

    for(int i = ptr->f + 1 ; i<= ptr->r ; i++){

        printf("%d\t",ptr->arr[i]);
    }
}


int main(){

    queue *q;
    q->size = 5;
    q->f = q->r = -1;
    q->arr = (int*)malloc(sizeof(int));


    enqueue(q,12);
    enqueue(q,4);
    enqueue(q,97);
    enqueue(q,9);
    enqueue(q,87);
    enqueue(q,12);
    display(q);

}