#include <stdio.h>
#include <stdlib.h>

typedef struct node{

	int data;
	struct node *next;

}node;

node *top = NULL;

void push(int data){

	node* x = (node*)malloc(sizeof(node));
	x->data = data;
	x->next = top;
	top = x;
}

int pop()
{
	int a = -1;
	if(top == NULL){
		printf("Stack is empty\n");
		return a;
	}
	else{
		node* ptr = top;
		a = top->data;
		top = top->next;
		free(ptr);
		return a;
	}
}

void printstack(){
	node* ptr = top;
	while(ptr){
		printf("%d ",ptr->data);
		ptr = ptr->next;
	}
	printf("\n");
}

void peek(){

	printf("Data at top is : %d\n", top->data);
}

int main()
{
	int n;
	int choice = 1;
	int pos;
	

	do{
		printf("What do you want to perform:\n 1. Push Into Stack\n 2. Pop from stack\n 3. Print \n 4. Peek\n enter your choice: ");
		scanf("%d",&n);
		switch(n){
			case 1: printf("ENter data to be pushed");
					int data;
					scanf("%d",&data);
					push(data);
					break;
			case 2: 
					printf("The popped data is : %d \n", pop());
					break;
		
			case 3: printstack();
					break;

			case 4: peek();
					break;
					

		}

		printf("Do you want to continue?");
		scanf("%d",&choice);

	}while(choice);
	
}