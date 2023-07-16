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
  x->prev = head->prev;
  x->next = head;
  head->prev->next = x;
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

  do{
        ptr = ptr->next;
    }while(ptr->next != head);

  x->next = ptr->next;
  x->prev = ptr;
  ptr->next = x;
  ptr->next->prev = x; 
  return head;
}

node* deletefirst(node *head){

  node* ptr = head;
  head->prev->next = head->next;
  head->next->prev = head->prev;
  head = head->next;
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

    do{
        ptr = ptr->next;

    }while(ptr->next != head);
  
  ptr->prev->next = ptr->next;
  ptr->next->prev = ptr->prev;
  free(ptr);
  return head;
} 

node* deletevalue(node *head, int val){

  node* ptr = head;

  if(ptr->data = val){
    deletefirst(head);
    return head;
  }

  do{
        ptr = ptr->next;
    }while(ptr != head  && ptr->data != val);

  if(ptr == head){
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

    do{
        printf("%d->",ptr->data);
        ptr = ptr->next;
    }while(ptr->next != head);
  
  printf("%d",ptr->data);
  printf("\n");
  return;
}


int main(){

  // Initialising a linked list
  node *head = (node*)malloc(sizeof(node));
  node *second = (node*)malloc(sizeof(node));
  node *third = (node*)malloc(sizeof(node));

  // initialising head
  head->data = 20;
  head->prev = third;  
  head->next = second;

    // initialising second node
  second->data = 9;
  second->prev = head;  
  second->next = third;
  
    // initialising third node
  third->data = 16;
  third->prev = second;  
  third->next = head;

  display(head);
  head = insertatfirst(head, 19);
  display(head);
  head = insertatindex(head, 2 , 34);
  display(head);

  
}