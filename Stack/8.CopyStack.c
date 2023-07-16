#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int size;
    int top;
    int *arr;

}stack;

int isFull(stack *q){
    return (q->top == q->size-1);
}

int isEmpty(stack *q){
    return (q->top == -1);
}

void push(stack *q, int value){
    if(isFull(q))
        printf("stack overflow");
    
    else{
        q->top++;
        q->arr[q->top] = value;
    }
}

int pop(stack *q){

    int a = -1;
    if(isEmpty(q))
        printf("stack underflow");
    
    else{
        a = q->arr[q->top];
        q->top--;
    }

    return a;
}

int peek(stack *q, int i){

    if(q->top-i+1 < 0)
        return -1;
    return q->arr[q->top - i + 1];
    
}

int stacktop(stack *q){
    return q->arr[q->top];
}

void copy(stack *o, stack *c){
    if(isEmpty(o))
        return;
    int current = stacktop(o);
    pop(o);
    copy(o,c);
    push(c,stacktop(o));
}


int main(){

    stack *sp = (stack *)malloc(sizeof(stack));
    sp->size=5;
    sp->top=-1;  
    sp->arr=(int*) malloc(sp->size * 4);
    printf("stack has been created successfully\n");

    push(sp,12);
    push(sp,23);
    push(sp,65);
    push(sp,43);
    push(sp,1);
    printf("stack has been created successfully\n");
  

    for (int i = 0; i <= sp2->top; i++)
    {
        printf("%d\t",sp2->arr[i]);
    }



}