#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    
    int data;
    struct node *left, *right;

} node;

node* insert(node *root, int data) {
    if (root == NULL){

        node *x = (node*) malloc (sizeof(node));
        x->data = data;
        x->left = x->right = NULL;
        root = x;
        return root;
    }

    else if (root->data >= data) {
            root->left = insert(root->left, data);
    }

    else{
            root->right = insert(root->right, data);
    }   
}

// Preorder with recursion
void preOrder(node *root) {
    if (root != NULL) {

        printf("%d - ", root->data);
        preOrder(root->left);
        preOrder(root->right);

    } 
}

// Preorder without recursion
void preOrderRecfree(node* root){

    if(root == NULL){
        return;
    }

    node *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {

        node* current = stack[top--];
        printf("%d ", current->data);

        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
}

void InOrder(node *root) {
    if (root != NULL) {

        InOrder(root->left);
        printf("%d - ", root->data);
        InOrder(root->right);
    
    } 
}

void PostOrder(node *root) {
    if (root != NULL) {

        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d - ", root->data);

    } 
}

void search(node *root, int data) {
    if(root == NULL){
        printf("Not found\n");
    }
    if (root->data == data){
        printf("Found\n");
    }
    else if (root->data >= data) {
        search(root->left, data);
    }
    else{
        search(root->right, data);
    }
      
}
node* findmax(node* root){
    while(root->right){
        root = root->right;
    }
    return root;
}

node *delete(node *root, int key){

    if(root == NULL){
        printf("Invalid key");
    }
    else if(root->data > key){
        root->left = delete(root->left, key);
    }
    else if(root->data > key){
        root->right = delete(root->right, key);
    }
    else{
        node* temp;
        if(root->right && root->left){
            temp = findmax(root->left);
            root->data = temp->data;
            root->left = delete(root->left,temp->data);
        }
        else{
            temp = root;
            if(root->left)
                root = root->left;
            if(root->right)
                root = root->right;
            free(temp);
        }
    }
    return root;
}


int main() {

    node *root = NULL;
    int n;
    int choice = 1;
    int data;
    int val = 0;

    do {

        printf("What do you want to do:\n 1. Insert\n 2. Preorder\n 3. Inorder\n 4. Postorder\n 5. Search\n 6.Delete \n");
        scanf("%d", &n);

        switch(n) {
            case 1:
                fflush(stdin);
                printf("Enter the data: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                preOrder(root);
                break;
            case 3:
                InOrder(root);
                break;
            case 4:
                PostOrder(root);
                break;
            case 5:
                fflush(stdin);
                printf("Enter the data to be searched ");
                scanf("%d", &val);
                search(root, val);
                break;
            case 6:
                printf("Enter the data to be deleted ");
                scanf("%d", &val);
                root = delete(root, val);
                break;

        }   
        printf("Do you want to continue? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);

    } while(choice);

    return 0;
}
