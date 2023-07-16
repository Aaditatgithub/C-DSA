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

void peek(stack *q, int i){

    if(q->top-i+1 < 0)
        printf("\ninvalid position");

    else{
        printf("\nThe value at %d pos is %d", i, q->arr[q->top - i + 1]);
    }
    return;
}

int size(stack *q){
    return q->top+1;
}

int main()
{   
    int n;   
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
    
    printf("%d",pop(sp));
    printf("\nsize of stack is : %d",size(sp));

    peek(sp,3);

}