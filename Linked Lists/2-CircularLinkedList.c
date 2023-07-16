#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    
    int data;
    struct node *next;
    
}node;

void traverse(node *head){

    node *x = head;
    do{

        printf("%d\t",x->data);
        x = x->next;

    }while(x != head);
}

//--------------------------------------------------INSERTION---------------------------------------------------------------

node * insertatfirst(node * head, int data){

    node *x = (node*)malloc(sizeof(node));
    node * ptr = head->next;

    while(ptr->next != head)
    {
        ptr = ptr->next; 
    }

    x->data = data;
    x->next = head;
    ptr->next = x;
    return x;
}

node *insertatend(node *head, int data){
    
    node *x = (node*)malloc(sizeof(node));
    node *ptr = head;
    do{
        ptr = ptr->next; 

    }while(ptr->next != head);

    x->next = head;
    x->data = data;
    ptr->next = x;
    return head;
}

node* insertatindex(node *head, int data, int index){

    node *x = (node*)malloc(sizeof(node));
    node *ptr = head;

    for(int i = 0; i<index -1;i++)
    {
        ptr = ptr->next; 
    }

    x->data = data;
    x->next = ptr->next;
    ptr->next = x;
    return head;
}
//--------------------------------------------DELETION-OF-NODE-------------------------------------------------------------------

node* deleteatfirst(node * head){

    node *x =  head;
    node *ptr = head;

    do{
        ptr = ptr->next; 

    }while(ptr->next != head);

    head = head->next;
    ptr->next = head;
    free(x);
    return head;
}

node* deleteatindex(node * head, int index){
 
    node *ptr1 = head;
    node *ptr2 = head->next;

    for(int i = 0; i< index -1; i++){
        ptr1= ptr1->next;
        ptr2= ptr2->next;
    }
    
    ptr1->next = ptr2->next;
    free(ptr2);
    return head;     
}

node* deletevalue(node * head, int value){

    node *ptr1 = head;
    node *ptr2 = head->next;

    for(int i = 0; ptr2->data != value; i++){

        ptr1= ptr1->next;
        ptr2= ptr2->next;
    }
    
    ptr1->next = ptr2->next;
    free(ptr2);
    return head; 
}

node* deleteatlast(node * head){

    node *ptr1 = head;
    node *ptr2 = head->next;

    for(int i = 0; ptr2->next != head; i++){
        ptr1= ptr1->next;
        ptr2= ptr2->next;
    }
    
    ptr1->next = ptr2->next;
    free(ptr2);
    return head;

}

//-----------------------------------------------------------------------------------------------------------------------

int main(){

    node *head;
    node *second;
    node *third;
    node *fourth;

    //Allocate memory for nodes in linked list in heap
    head = (node*) malloc(sizeof(node));
    second = (node*) malloc(sizeof(node));
    third = (node*) malloc(sizeof(node));
    fourth = (node*) malloc(sizeof(node));
    
    //link head and second node
    head->data = 7;
    head->next = second;

    //link second and third node
    second->data = 12;
    second->next = third;

    //link third and fourth node
    third->data = 53;
    third->next = fourth;
    
    //Terminate the linked list at fourth node
    fourth->data = 66;
    fourth->next = head;

    traverse(head);
    printf("\nchanging head\n");
    head =  insertatend(head, 93);
    traverse(head);
    head = deleteatfirst(head);
    printf("\ndeleting head\n");
    traverse(head);
    head = deletevalue(head,21);
    printf("\nLinked list is:\n");
    traverse(head);
}