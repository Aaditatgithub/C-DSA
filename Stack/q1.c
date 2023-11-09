// A person is living in house having 5 rooms.
// These rooms are adjacent to each other.
// There is a treasure which is electronically locked and to
// unlock it we need a code. In last room there is a box in which
// some decimal number is written. We need to convert that number
// into binary to open treasure which is kept in room no.1 .
// We need to move from room no.1 to 2 to 3 and so on and 
// follow the reverse way to come back i.e. from 5 to 4 to 3 etc.
// Apply suitable logic to implement this scenario by using stacks.

#include <stdio.h>
#include <stdlib.h>

#define MAX_ROOMS 5

typedef struct stack{
    int top;
    int arr[MAX_ROOMS];
}*pstack;

void push(pstack stack, int bin){
    if(stack->top == MAX_ROOMS - 1){
        printf("Cannot open treasure...stack overflow...less number of rooms\n");
        exit(EXIT_FAILURE);
    }
    stack->arr[++stack->top] = bin;
}

void openTreasure(int decimal){

    pstack stack;
    stack->top = -1;

    while(decimal > 0){
        push(stack, decimal%2);
        decimal /= 2;
    }

    printf("Treasure opened...\n");
    while(stack->top != -1){
        printf("%d",stack->arr[stack->top--]);
    }
}

int main(){
    int decimal = 9;
    openTreasure(decimal);
}