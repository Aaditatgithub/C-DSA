#include <stdio.h>
#include <stdlib.h>
 
typedef struct node{
    int data;
    struct node *next;
}node;

node *f = NULL;
node *r = NULL;

void enqueue(int data){

    node *ptr = (node*)malloc(sizeof(node));
    ptr->data = data;
    ptr->next = NULL;

    if(f = NULL){
        f = r = ptr;
        return;
    }
    else{
        r->next = ptr;
        r = ptr;
    }
    return;
}

void dequeue(){

    if(f == NULL){
        printf("QUeue is empty\n");
    }
    else if(f == r){
        node *ptr = f;
        f = r = NULL;
        free(ptr);
    }
    else{
        node *ptr = f;
        f = f->next;
        free(ptr);
    }
    return ;
}

void QueueTraversal(){
    node *ptr = f;
    while(ptr){
        printf(" %d ", ptr->data);
        ptr = ptr->next;
    }
    return;
}
 
int main()
{
    int n;
	int choice = 1;
	
	do{
		printf("What do you want to perform:\n 1. Enqueue\n 2. Dequeue\n 3. Print queue \n enter your choice: ");
		scanf("%d",&n);

		switch(n)
        {
			case 1: printf("ENter data to be enqueued");
					int data;
					scanf("%d",&data);
					enqueue(data);
					break;
			case 2: 
					dequeue();
					break;
		
			case 3: QueueTraversal();
					break;
		}
		printf("Do you want to continue?");
		scanf("%d", &choice);

	}while(choice);
	
}
