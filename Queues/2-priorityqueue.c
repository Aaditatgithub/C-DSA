#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    int priority;
    struct node* next;

}node;

node *f = NULL;
node *r = NULL;
int max_priority = __INT_MAX__;

void enqueue(int data, int prior){

    node *ptr = (node*)malloc(sizeof(node));
    ptr->data = data;
    ptr->next = NULL;
    ptr->priority = prior;

    if(ptr->priority < max_priority){
        max_priority = ptr->priority;
    }

    if(f == NULL){
        f = r = ptr;
    }
    else{
        r->next = ptr;
        r = ptr;  
    }
}

int dequeue(node *head){
    int a = 1;
    if(f == NULL){
        printf("Queue is empty\n");
        return a ;
    }

    node *ptr = head;
    node *ptr2 = head->next;

    if(head->priority == max_priority){
        head = head->next;
        a = ptr->data;
        free(ptr);  
        return a;
    }

    else{
        while(ptr2){
            if(ptr2->priority == max_priority){
                ptr->next = ptr2->next;
                a = ptr2->data;
                free(ptr2);
                return a;
            }
            ptr = ptr->next;
            ptr2 = ptr2->next;
        }

    }
}

void display(){
    node *ptr = f;
    while(ptr){
        printf("Data is : %d    Priority is : %d \n", ptr->data, ptr->priority);
        ptr = ptr->next;
    }

}

int main(){

    int n;
    int choice = 1;
    int data; 
    int prior = 1;

    do{
        printf("What do you want to do : \n 1. Enqueue\n 2. Dequeue\n 3. Print \n");
        scanf("%d",&n);
        switch(n){
            case 1 : printf("Enter the data and its priority : ");
                     scanf("%d %d", &data, &prior);
                     enqueue(data, prior);
                     break;

            case 2 : printf("The dequeued element is %d\n", dequeue(f));
                     break;

            case 3 : display();
                     break;
        }
        
        printf("Do you want to continue? ");
        scanf("%d",&choice);

    }while(choice);
}
