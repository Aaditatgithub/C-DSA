#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    node* next;
}*pnode, node;

pnode createnode(int data){
    pnode n = (pnode)malloc(sizeof(node));
    n->data = data;
    n->next = NULL;
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
    return head;
}

typedef struct split{
    pnode list1;
    pnode list2;
}*splitlist,lists;

void frontbacklist(splitlist plists, pnode head){
    pnode temp = head;

    if(head == NULL || head->next == NULL){
        plists->list1 = head;
        plists->list2 = NULL;
        return;
    }

    pnode slow = head;
    pnode fast = head->next;

    while(fast){
        fast = fast->next;
        if(fast){
            fast = fast->next;
            slow = slow->next;
        }
    }

    plists->list1 = head;
    plists->list2 = slow->next;
    slow->next = NULL;          //separating lists
}

void printlist(pnode head){
    while(head){
        printf("%d -> ",head->data);
        head = head->next;
    }printf("NULL\n");
}

int main(){

    splitlist plists = (splitlist)malloc(sizeof(lists));
    plists->list1 = NULL;
    plists->list2 = NULL;

    pnode head = NULL;
    head = insert(head,2);
    //head = insert(head,3);
    //head = insert(head,5);
    //head = insert(head,7);
    //head = insert(head,11);

    printlist(head);
    frontbacklist(plists,head);
    printlist(plists->list1);
    printlist(plists->list2);
    

}