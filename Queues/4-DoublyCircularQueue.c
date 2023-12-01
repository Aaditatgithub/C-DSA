#include<stdio.h>
#include<stdlib.h>

typedef struct dqueue{
    int size;
    int f, r;
    int *arr;
}*pdqueue,dqueue;

void insert_rare(pdqueue q, int data){
    if((q->r + 1)% q->size == q->f){
        printf("Queue is full...\n");
        return;
    }
    else{
        if(q->f == -1 && q->r == -1)
            q->f = q->r = 0;
        else
            q->r = (q->r + 1) % q->size;
    }
    q->arr[q->r] = data;
}

void insert_front(pdqueue q, int data){
    if((q->r + 1)% q->size == q->f){
        printf("Queue is full...\n");
        return;
    }
    else{
        if(q->f == -1 && q->r == -1)
            q->f = q->r = 0;
        else
            q->f = (q->f - 1) % q->size;
    }
    q->arr[q->f] = data;
}

void delete_rare(pdqueue q){
    if(q->r == -1 && q->f == -1){
        printf("Queue is empty\n");
        return;
    }
    else{
        if(q->r == 0 && q->f == 0){
            q->r = -1;
            q->f = -1;
        }
        else{
            q->r = (q->r - 1)%q->size;
        }
    }
}

void delete_front(pdqueue q){
    if(q->r == -1 && q->f == -1){
        printf("Queue is empty\n");
        return;
    }
    else{
        if(q->r == 0 && q->f == 0){
            q->r = -1;
            q->f = -1;
        }
        else{
            q->f = (q->f + 1)%q->size;
        }
    }
}

void display(pdqueue q){

    for(int i = q->f; i != q->r; i = (i + 1)%q->size){
        printf("%d ",q->arr[i]);
    }   printf("%d ",q->arr[q->r]);
    printf("\n");
}

int main(){

    // init queue
    pdqueue q = (pdqueue)malloc(sizeof(dqueue));
    q->size = 5;
    q->arr = (int*)malloc(sizeof(int)*q->size);
    q->f = -1;
    q->r = -1;

    insert_rare(q,12);
    insert_rare(q,54);
    insert_rare(q,76);
    insert_rare(q,15);
    insert_rare(q,98);
    display(q);
    delete_rare(q);
    delete_rare(q);
    delete_rare(q);
    display(q);
    insert_front(q,98);
    display(q);
    delete_front(q);
    display(q);

}
