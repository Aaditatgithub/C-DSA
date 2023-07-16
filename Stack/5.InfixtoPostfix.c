#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{

    int size;
    int top;
    char *arr;

}stack;

int isfull(stack *s){
    if(s->top == s->size-1)
        return 1;
    else   
        return 0;
}

int isempty(stack *s)
{
    if(s->top == -1)
        return 1;
    else    
        return 0;
}

void push(stack *s , char data){

    if(isfull(s)){
        printf("Stack overflow");
    }
    else
    {
        s->top++;
        s->arr[s->top] = data;
    }
}

char pop(stack *s){

//O(1) : time compx
    if(isempty(s)){
        printf("Stack underflow");
        return -1;
    }

    int data = s->arr[s->top];
    s->top--;
    return data;
}

char stackTop(stack *s){
	return s->arr[s->top];
}

int precedence(char ch){

	if(ch == '^')
		return 3;
	else if(ch == '*' || ch == '/')
		return 2;
	else if(ch == '+' || ch == '-')
		return 1;
	else 
		return -1;
}


char *infixtopostfix(char *infix){

	stack *sp = (stack*)malloc(sizeof(stack));
	sp->size = 20;
	sp->top = -1;
	sp->arr = (char*)malloc(sp->size * sizeof(char));

	char *postfix = (char*)malloc((strlen(infix)+1) *sizeof(char));

	int i = 0; // track infix traversal
	int j = 0; // track postfix traversal

	for(i =0; infix[i]!=0 ; i++ ){

		if((infix[i] >='a' && infix[i] <='z') || (infix[i]>='A' && infix[i]<='Z') || (infix[i]>='0' && infix[i]<='9')){
			postfix[j] = infix[i];
			j++;
		}

		else if(infix[i] == '(')
			push(sp, infix[i]);
		
		else if(infix[i] == ')'){

			while(!isempty(sp) && stackTop(sp)!='('){
				postfix[j] = pop(sp);;
				j++;
			}
			if(!isempty(sp))
				pop(sp);
		}

		else{

			if(!isempty(sp) && precedence(stackTop(sp)) >= precedence(infix[i])){
				postfix[j] = pop(sp);
				j++;
			}
			push(sp, infix[i]);
		}
		
	}
	if(!isempty(sp)){
			postfix[j] = pop(sp);
			j++;
		}
	postfix[j] = '\0';
	return postfix;
}

int main(){

	char *infix = "(a^b/c)*(23/k-l)";
	printf("Postfix is %s", infixtopostfix(infix));

}
