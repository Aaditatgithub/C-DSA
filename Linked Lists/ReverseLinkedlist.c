#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

node* createnode(int data){
    node* n = (node*)malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    return n;
}
    
node* insert(node* head, int data){
    if(!head){
        return createnode(data);
    }
    node* temp = head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = createnode(data);
    return head;
}

node* reverse(node* head){
    if(!head){
        printf("\nLinked list is empty\n");
        return head;
    } 
    node* prev = NULL;
    node* curr = head;
    node* next = head->next;

    while(next){
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;
    return curr;
}

void printlist(node* head){
    while(head){
        printf("%d->",head->data);
        head = head->next;
    }printf("NULL\n");
}

int main(){
    node* head = NULL;
    head = insert(head,2);
    head = insert(head,3);
    head = insert(head,5);
    // head = insert(head,7);
    // head = insert(head,11);
    printlist(head);
    head = reverse(head);
    printlist(head);
}