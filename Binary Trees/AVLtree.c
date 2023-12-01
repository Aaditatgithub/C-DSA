#include<stdio.h>
#include<stdlib.h>

// Most operations of binary tree are of order O(h) [h->height]
// Inefficient trees can have n height, thus time complexity would increase (skewed tree)
// Thus, usage of balanced trees guarantees us an upper bound of O(logn) for all ops.
// Height difference bw left and right subtrees for every node is max 1
// Balanced Factor = |Hr - Hl| <= 1

// LL insertion -> Right rotate once
// RR insertion -> Left Rotate once
// LR insertion -> rotate left , rotate right   -> child of first imbalanced node , 
// RL insertion -> rotate right , rotate left

typedef struct node{
    int data;
    int height;
    struct node* left,*right;
}*pnode, node;

int getmax(int a, int b){
    return ((a > b) ? a : b);
}

int getheight(pnode n){
    return (n ? n->height : 0);
}
int getbalancefactor(pnode root){
    return ((root != NULL) ? (getheight(root->left) - getheight(root->right)) : 0); 
}

pnode createnode(int data){
    pnode n = (pnode)malloc(sizeof(node));
    n->data = data;
    n->height = 0;
    n->left = n->right = NULL;
    return n;
}

pnode leftrotate(pnode x){
    pnode y = x->right;
    pnode T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = 1 + getmax(getheight(x->left), getheight(x->right));
    y->height = 1 + getmax(getheight(y->left), getheight(y->right));

    return y;
}

pnode rightrotate(pnode y){
    pnode x = y->left;
    pnode T2 = x->right;

    y->left = T2;
    x->right = y;

    x->height = 1 + getmax(getheight(x->left), getheight(x->right));
    y->height = 1 + getmax(getheight(y->left), getheight(y->right));

    return x;
}

pnode insert(pnode root, int key){
    if(!root)
        return createnode(key);
    
    if(key < root->data)
        root->left = insert(root->left,key);
    else if(key > root->data)
        root->right = insert(root->right,key);
    
    root->height = 1 + getmax(getheight(root->left), getheight(root->right));
    int bf = getbalancefactor(root);

    //LL
    if(bf > 1 && root->left->data > key){
        return rightrotate(root);
    }
    //RR
    if(bf < -1 && root->right->data < key){
        return leftrotate(root);
    }
    //RL
    if(bf < -1 && root->right->data > key){
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }
    //LR
    if(bf > 1 && root->left->data < key){
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }

    return root;
}

void inorder(pnode root){
    pnode curr = root;
    pnode stack[10];
    int top = -1;

    while(curr || top >= 0){
        while(curr){
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%d ",curr->data);
        curr = curr->right;
    }
}

int main(){

    pnode root = createnode(12);
    root = insert(root,23);
    root = insert(root,16);
    root = insert(root,76);
    root = insert(root,9);
    root = insert(root,13);
    inorder(root);

}
