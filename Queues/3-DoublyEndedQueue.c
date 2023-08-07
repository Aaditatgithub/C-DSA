#include<stdio.h>
#include<stdlib.h>

typedef struct queue{

    int size;
    int f;
    int r;
    int *arr;

}queue;

void enqueueF(queue *q,int data){

    if(q->f == 0)
        printf("NOT POSSIBLE");

    else{
        q->f--;
        q->arr[q->f] = data;
    }
}

void enqueueR(queue *q,int data){

    if(q->r == q->size - 1)
        printf("NOT POSSIBLE");
    
    else{

        q->r++;
        q->arr[q->r] = data;
    }
}

int dequeueF(queue *q){
    
    int a = -1;
    if(q->f == q->size-1){
        printf("NOT POSSIBLE");
    }
    else{

        if(q->f == -1)
            q->f = 0;
        int a = q->arr[q->f];
        q->f++;
    }
    return a;
}

int dequeueR(queue *q){

    int a = -1;
    if(q->r == -1)
        printf("NOT POSSIBLE");

    else{
        int a = q->arr[q->r];
        q->r--;
    }
    return a;
}

void display(queue *ptr){

    if(ptr->f == -1){
        for(int i = ptr->f+1; i<= ptr->r ; i++){
            printf("%d\t",ptr->arr[i]);
        }
    }

    else{
        for(int i = ptr->f; i<= ptr->r ; i++){
            printf("%d\t",ptr->arr[i]);
        }
    }
    printf("\n");
}

int main()
{
    queue *q = (queue*) malloc(sizeof(queue));
    q->size = 10;
    q->f = -1;
    q->r = -1;
    q->arr = (int*)malloc(q->size*sizeof(int));

    //Enqueue few elements
    enqueueR(q, 12);
    enqueueR(q, 43);
    enqueueR(q, 78);
    enqueueR(q, 45);
    enqueueR(q, 98);
    display(q);
    dequeueF(q);
    display(q);
}