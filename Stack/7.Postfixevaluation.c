#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct stack{

    int size;
    int top;
    int *arr;

}stack;


int isEmpty(stack *ptr){
    if(ptr->top==-1)
        return 1;
    else
        return 0;
}


int isFull(stack *ptr){

     if(ptr->top==ptr->size-1)
        return 1;
    else
        return 0;
}


void push(stack *ptr, int value){

    if(ptr->top==ptr->size-1)
        printf("stack overflow");

    else{
        (ptr->top)++;
        ptr->arr[ptr->top]=value;        
    }
}


int pop(stack *ptr){
    if(ptr->top==-1){
        printf("stack underflow");
        return -1;
    }    
    else{
        int a = ptr->arr[ptr->top];
        (ptr->top)--;
        return a;  
    }
}


int peek(stack *ptr,int i){

    if( ptr->top-i+1 < 0){
        printf("not a valid position:");
        return -1;
    }
    else
        return ptr->arr[ptr->top -i + 1];
}

int stackTop(stack *s){
	return s->arr[s->top];
}



int postfixevaluation(char *s){

    stack *sp = (stack*)malloc(sizeof(stack));
	sp->size = 20;
	sp->top = -1;
	sp->arr = (int*)malloc(sp->size * sizeof(int));

    for(int i = 0; s[i]!='\0'; i++){

        if(s[i]>='0' && s[i]<='9'){
            push(sp, (int)(s[i] - '0'));
        }

        else{

            int op2 = pop(sp);
            int op1 = pop(sp);

            switch(s[i]){

                case '+' : push(sp, op1+op2);
                            break;
                case '-' : push(sp, op1-op2);
                            break;
                case '*' : push(sp, op1*op2);
                            break;
                case '/' : push(sp, op1/op2);
                            break;
                case '^' : push(sp,(int)pow(op1,op2));
                            break;
            }
        }
    }
    
    return stackTop(sp);
}

int main(){

    printf("%d",postfixevaluation("46+2/5*7+"));

}