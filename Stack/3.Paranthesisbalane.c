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

int paranthesismatch(char *exp)
{
    stack *sp = (stack*)malloc(sizeof(stack));
    sp->size = 20;
    sp->top = -1;
    sp->arr = (int*)malloc(sizeof(int) * (sp->size));

    for(int i = 0; exp[i] ; i++ ){
        
        if(exp[i] == '(')
            push(sp,'(');

        else if(exp[i] == ')'){
            if(isEmpty(sp))
                return 0;
            pop(sp);
        }
    }
    return(isEmpty(sp));       
}

int main(){

    char exp[] = "(23-12)";

    if(paranthesismatch(exp))
        printf("Parantheis matches");
    
    else
        printf("paranthesis doesnt match");
    
    return 0;
}