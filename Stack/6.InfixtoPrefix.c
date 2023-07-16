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

void reverse(char *str){
    int i;
    int j;
    char temp;

    for(i = 0,j = strlen(str)-1; i < j; i++,j--){

        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char *infixtoprefix(char *infix){

    reverse(infix);

    stack *sp = (stack*)malloc(sizeof(stack));
	sp->size = 20;
	sp->top = -1;
	sp->arr = (char*)malloc(sp->size * sizeof(char));

	char *prefix = (char*)malloc((strlen(infix)+1) *sizeof(char));

	int i = 0; // track infix traversal
	int j = 0; // track prefix traversal

	for(i =0; infix[i]!=0 ; i++ ){

		if((infix[i] >='a' && infix[i] <='z') || (infix[i]>='A' && infix[i]<='Z') || (infix[i]>='0' && infix[i]<='9')){

			prefix[j] = infix[i];
			j++;
		}

		else if(infix[i] == ')'){
			push(sp,infix[i]);
		}

		else if(infix[i] == '(')
		{
			while(!isempty(sp) && stackTop(sp)!=')' ){
				prefix[j] = stackTop(sp);
				pop(sp);
				j++;
			}

			if(!isempty(sp)){
				pop(sp);
			}
		}

		else{
			while(!isempty(sp) && precedence(stackTop(sp)) >= precedence(infix[i])){
				prefix[j] = pop(sp);
				j++;
			}
			push(sp, infix[i]);

		}
	}
	

	while(!isempty(sp)){
		prefix[j] = pop(sp);
		j++;
	}

	prefix[j] = '\0';
    reverse(prefix);
	return prefix;
}

int main(){

	char infix[] = "(a-b/c)*(23/k-l)";

	printf("Prefix is %s", infixtoprefix(infix));

}