#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node *next;
    struct node *prev;

}node;

node* insertatfirst(node *head, int data){

  node *x = (node*)malloc(sizeof(node));
  x->data = data;
  x->prev = NULL;
  x->next = head;
  head->prev = x;
  return x;

}

node* insertatindex(node *head, int index,int data){

  node *x = (node*)malloc(sizeof(node));
  x->data = data;

  node* ptr = head;
  for(int i = 0; i < index -1 ; i++){
    ptr = ptr->next;
  }

  x->next = ptr->next;
  x->prev = ptr;
  ptr->next = x;
  (ptr->next)->prev = x;
   
  return head;
}

node* insertatend(node *head, int data){

  node *x = (node*)malloc(sizeof(node));
  x->data = data;

  node* ptr = head;
  while(ptr->next != NULL){
    ptr = ptr->next;
  }

  x->next = ptr->next;
  x->prev = ptr;
  ptr->next = x;
   
  return head;
}

node* deletefirst(node *head){

  node* ptr = head;
  head = head->next;
  head->prev = NULL;
  free(ptr);
  return head;
}

node* deleteindex(node *head, int index){

  node *ptr= head;
  for (int i = 0; i < index ; i++)
  {
    ptr = ptr->next;
  }
  
  ptr->next->prev = ptr->prev;
  ptr->prev->next = ptr->next;
  free(ptr);
  return head;

} 

node* deletelast(node *head){

  node *ptr = head;

  while(ptr->next !=NULL){
    ptr = ptr->next;
  }
  
  ptr->prev->next = ptr->next;
  free(ptr);
  return head;
} 

node* deletevalue(node *head, int val){

  node* ptr = head;
  while(ptr->data != val && ptr!= NULL){
    ptr = ptr->next;
  }

  if(ptr == NULL){
    printf("Value not found:");
    return head;
  }

  else{
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    free(ptr);
    return head;
  }
}

void display(node* head){

  node* ptr = head;
  while(ptr != NULL){
    
      printf("%d->",ptr->data);
      ptr = ptr->next;
  }
  printf("NULL\n");
  return;
}


int main(){

  // Initialising a linked list

  node *head = (node*)malloc(sizeof(node));
  node *second = (node*)malloc(sizeof(node));
  node *third = (node*)malloc(sizeof(node));

  // initialising head
  head->data = 20;
  head->prev = NULL;  
  head->next = second;

    // initialising second node
  second->data = 9;
  second->prev = head;  
  second->next = third;
  
    // initialising third node
  third->data = 16;
  third->prev = second;  
  third->next = NULL;

  display(head);
  head = insertatfirst(head, 19);
  display(head);
  head = insertatindex(head, 2 , 34);
  head = insertatend(head, 34);
  head = deletefirst(head);
  head = deletelast(head);
  head = deleteindex(head, 2);
  display(head);

  
}