#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
}node,*pnode;

pnode createnode(int data){
    pnode n = (pnode)malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

pnode insert(pnode head, int data){
    if(head == NULL){
        return createnode(data); 
    }

    pnode temp = head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = createnode(data);
    temp->next->prev = temp;
    return head;
}

pnode mergesortedlist(pnode list1, pnode list2){
    
    pnode mergedlist = NULL;
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    while(list1 != NULL && list2 != NULL){
        if(list1->data < list2->data){
            mergedlist = insert(mergedlist,list1->data);
            list1 = list1->next;
        }
        else{
            mergedlist = insert(mergedlist, list2->data);
            list2 = list2->next;
        }
    }

    while(list1){
        mergedlist = insert(mergedlist, list1->data);
        list1 = list1->next;
    }
    while(list2){
        mergedlist = insert(mergedlist, list2->data);
        list2 = list2->next;
    }
    return mergedlist;
}

void printlist(node* head){
    while(head){
        printf("%d->",head->data);
        head = head->next;
    }printf("NULL\n");
}

int main(){

    pnode head1 = NULL;
    pnode head2 = NULL;
    pnode sorted = NULL;

    //head1 = insert(head1,2);
    //head1 = insert(head1,7);
    //head1 = insert(head1,11);
    
    head2 = insert(head2,3);
    //head2 = insert(head2,6);
    //head2 = insert(head2,9); 
    
    printlist(head1);
    printlist(head2);
    sorted = mergesortedlist(head1, head2);
    printlist(sorted);
    
}