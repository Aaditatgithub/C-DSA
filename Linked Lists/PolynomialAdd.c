#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node,*pnode;

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

    node* temp = head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = createnode(data);
    return head;
}

void addition(pnode polyadd, pnode poly1, pnode poly2){
    
    if(polyadd == NULL){
        return ;
    }
    polyadd->data = poly1->data + poly2->data;
    pnode temp = polyadd;
    poly1 = poly1->next;
    poly2 = poly2->next;

    while(poly1 && poly2){
        temp->next = createnode(poly1->data + poly2->data);
        temp = temp->next;
        poly1 = poly1->next;
        poly2 = poly2->next;
    }
}

void printlist(pnode head){
    while(head){
        printf("%d->",head->data);
        head = head->next;
    }printf("NULL\n");
}

int main(){
    
    int degree;
    printf("Enter degree: ");
    scanf("%d",&degree);

    pnode poly1 = NULL;
    pnode poly2 = NULL;
    pnode poly3 = createnode(0);

    printf("Enter coefficients of polynomial 1: ");
    for(int i = 0; i <= degree; i++){
        int a;
        scanf("%d",&a);
        poly1 = insert(poly1,a);
    }
    printf("Polynomial 1 is: ");
    printlist(poly1);

    printf("Enter coefficients of polynomial 2: ");
    for(int i = 0; i <= degree; i++){
        int a;
        scanf("%d",&a);
        poly2 = insert(poly2,a);
    }
    printf("Polynomial 2 is: ");
    printlist(poly2);

    printf("Addition:\nPolynomial 3 is: ");
    addition(poly3, poly1, poly2);
    printlist(poly3);

}