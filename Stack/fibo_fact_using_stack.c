#include<stdio.h>
#include<stdlib.h>

typedef struct stack{
    int top = -1;
    int size;
    int *arr;
}*pstack,stack;

void factorial(int n){

    if(!n){ printf("\nfact of 0 is 1");
            return; }

    // stack init
    pstack s = (pstack)malloc(sizeof(stack));
    s->arr = (int*)malloc(sizeof(int)*n);
    s->top = -1;
    s->size = n;

    int result = 1;

    do{
        printf("%d ",n);
        s->arr[++s->top] = n;
    } while((n--) -1);    
    
    while(s->top > -1){
        result *= s->arr[s->top--];
    }
   
    printf("fact of %d is %d.",s->size,result);
}

void fibonacci(int n){
    
    pstack s = (pstack)malloc(sizeof(stack));
    s->arr = (int*)malloc(sizeof(int)*n);
    s->top = -1;
    s->size = n;
    
    int f0 = 0;
    int f1 = 1;

    for(int i = n; i >= 0; i--){
        s->arr[++s->top] = f0;

        int next = f0 + f1;
        f0 = f1;
        f1 = next;
    }

    printf("\n");
    while(s->top != -1){
        printf("%d ",s->arr[s->top--]);
    }

}

int main(){
    factorial(0);
    fibonacci(5);
}