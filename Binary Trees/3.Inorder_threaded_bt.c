#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data, lbit, rbit;
    struct node* left, * right;
}node;

node* insertnode(node* root, int data) {
    node* curr = root;
    node* parent = NULL;

    while (curr != NULL) {
        if ((curr->data) == data) {
            printf("key already exists...\n");
            return root;
        }
        parent = curr;
        if (data < curr->data) {
            if (curr->lbit == 0)
                curr = curr->left;
            else
                break;
        }
        else {
            if (curr->rbit == 0)
                curr = curr->right;
            else
                break;
        }
    }

    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->lbit = 1;
    newnode->rbit = 1;

    if (parent == NULL) {
        root = newnode;
        newnode->left = NULL;
        newnode->right = NULL;
    }

    else if (data < (parent->data)) {
        newnode->left = parent->left;
        newnode->right = parent;
        parent->lbit = 0;
        parent->left = newnode;
    }
    else {
        newnode->left = parent;
        newnode->right = parent->right;
        parent->rbit = 0;
        parent->right = newnode;
    }
    return root;
}

node* inordersucc(node* current) {
    if (current->rbit == 1)
        return current->right;
    else {
        current = current->right;
        while (current->lbit == 0)
            current = current->left;
        return current;
    }
}

void inorder(node* root) {
    node* current = root;
    while (current->left)
        current = current->left;
    while (current) {
        printf("%d ", current->data);
        current = inordersucc(current);
    }
}

void preorder(node* root) {
    while (root) {
        printf("%d ", root->data);
        if (root->lbit == 0) {
            root = root->left;
        }
        else if (root->rbit == 0) {
            root = root->right;
        }
        else {
            while (root->rbit == 1 && root) {
                root = inordersucc(root);
            }
            if (root) {
                root = root->right;
            }
        }
    }
}

//stick to this only, no matter what you think
void postorder(node* root){
    if(root){
        if(root->lbit == 0)
            postorder(root->left);
        if(root->rbit == 0)

            postorder(root->right);
        printf("%d ",root->data);
    }
}

int main() {
    node* root = NULL;
    int count = 6;
    root = insertnode(root, 10);
    root = insertnode(root, 6);
    root = insertnode(root, 9);
    root = insertnode(root, 12);
    root = insertnode(root, 11);
    root = insertnode(root, 13);
    inorder(root);
    printf("\n");
    //preorder(root);
    printf("\n");
    postorder(root);
}
