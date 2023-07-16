#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int size;
    int top;
    char *arr;

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

int match(char a, char b){

    if(a == '(' && b == ')')
        return 1;
    if(a == '[' && b == ']')
        return 1;
    if(a == '{' && b == '}')
        return 1;
}

int parenthesismatch(char *exp){

    stack *sp = (stack*)malloc(sizeof(stack));
    sp->size = 20;
    sp->top = -1;
    sp->arr = (char*)malloc(sizeof(char) * (sp->size));

    char popped_char;

    for(int i = 0; exp[i] ; i++ ){
        
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[' )
            push(sp,exp[i]);

        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']'){
            if(isEmpty(sp))
                return 0;

            popped_char = pop(sp);
            if(!match(popped_char, exp[i]))
                return 0;
        }
    }

    return(isEmpty(sp));  
}

int main(){

    char * exp = "[4-6]((8){(9-8))";
    
    if(parenthesismatch(exp)){
        printf("The parenthesis is balanced");
    }
    else{
        printf("The parenthesis is not balanced");
    }
    return 0;


}