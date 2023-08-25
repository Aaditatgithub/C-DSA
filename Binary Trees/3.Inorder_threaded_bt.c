#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {

    int data;
    struct node* left, * right;
    bool lbit;
    bool rbit;

} node;

node* insert(node* root, int key) {

    node* current = root;
    node* parent = NULL;
    while (current != NULL) {
        if (key == (current->data)) {
            printf("Duplicate value !\n");
            return root;
        }
        parent = current;
        if (key < current->data) {
            if (current->lbit == false)
                current = current->left;
            else
                break;
        }
        else {
            if (current->rbit == false)
                current = current->right;
            else
                break;
        }
    }

    node* temp = (node*)malloc(sizeof(node));
    temp->data = key;
    temp->lbit = true;
    temp->rbit = true;

    if (parent == NULL) {
        root = temp;
        temp->left = NULL;
        temp->right = NULL;
    }
    else if (key < (parent->data)) {
        temp->left = parent->left;
        temp->right = parent;
        parent->lbit = false;
        parent->left = temp;
    }
    else {
        temp->left = parent;
        temp->right = parent->right;
        parent->rbit = false;
        parent->right = temp;
    }
    return root;
}

node* inSucc(node* current) {
    if (current->rbit == true)
        return current->right;

    current = current->right;
    while (current->lbit == false)
        current = current->left;

    return current;
}

// For returning inorder successor using rbit 
 node* inorderSuccessor(node* current)
{
    // If rbit is set, we can quickly find
    if (current->rbit == true)
        return current->right;

    // Or return the leftmost child of right subtree
    current = current->right;
    while (current->lbit == false)
        current = current->left;
    return current;
}

// Print the threaded tree
void inorder(node* root)
{
    if (root == NULL)
        printf("Tree is empty");
    // Taking leftmost node
    node* current = root;
    while (current->lbit == false)
        current = current->left;

    while (current != NULL) {
        printf("%d ", current->data);
        current = inorderSuccessor(current);
    }
}

node* inPred( node* current) {

    if (current->lbit == true)
        return current->left;

    current = current->left;
    while (current->rbit == false)
        current = current->right;
    return current;

}

// Here 'parent ' is a pointer referring to the parent node 
// and 'current' is a pointer to the current node.
node* case1(node* root,  node* parent,  node* current)
{
    // If root node has to be deleted
    if (parent == NULL)
        root = NULL;

    // If the node to be deleted is left child of its parent
    else if (current == parent->left) {
        parent->lbit = true;
        parent->left = current->left;
    }

    // If the node to be deleted is the right child of its parent
    else {
        parent->rbit = true;
        parent->right = current->right;
    }

    // Now memory is freed and new root is returned
    free(current);
    return root;
}

// Here 'parent ' is a pointer referring to the parent node 
// and 'current' is a pointer to the current node.
 node* case2( node* root,  node* parent,  node* current)
{
     node* child;
    // First initialize whether the child node to be deleted has left child.
    if (current->lbit == false)
        child = current->left;

    // or a right child
    else
        child = current->right;

    // If root node has to be deleted
    if (parent == NULL)
        root = child;

    // If the node to be deleted is left child of its parent
    else if (current == parent->left)
        parent->left = child;

    // If the node to be deleted is right child of its parent
    else
        parent->right = child;

    // Find successor and predecessor
    node* s = inSucc(current);
    node* p = inPred(current);

    // If current node has left subtree
    if (current->lbit == false)
        p->right = s;

    // If current node has right subtree.
    else {
        if (current->rbit == false)
            s->left = p;
    }

    // Now memory is freed and new root is returned
    free(current);
    return root;
}

// Here 'parent' is a pointer referring to the parent node 
// and 'current' is a pointer to the current node
node* case3( node* root,  node* parent,  node* current) {
    
    // Find the inorder successor 
    node* parsucc = current;
    node* succ = current->right;

    // Find the leftmost child 
    while (succ->lbit == false) {
        parsucc = succ;
        succ = succ->left;
    }
    current->data = succ->data;
    if (succ->lbit == true && succ->rbit == true)
        root = case1(root, parsucc, succ);
    else
        root = case2(root, parsucc, succ);

    return root;
}

// For deleting the value from threaded BST with the given root 
// and returning a new root of BST

node* dThreadedBST(node* root, int value) {

    node *parent = NULL, *current = root;

    // Set true if value is found
    int found = 0;

    // Searching value in BST 
    while (current != NULL) {
        if (value == current->data) {
            found = 1;
            break;
        }
        parent = current;
        if (value < current->data) {
            if (current->lbit == false)
                current = current->left;
            else
                break;
        }
        else {
            if (current->rbit == false)
                current = current->right;
            else
                break;
        }
    }

    if (found == 0)
        printf("The value not present in tree\n");
    else if (current->lbit == false && current->rbit == false)
        root = case3(root, parent, current);
    else if (current->lbit == false)
        root = case2(root, parent, current);
    else if (current->rbit == false)
        root = case2(root, parent, current);
    else
        root = case1(root, parent, current);

    return root;
}

int main() {

    node* root = NULL;
    int choice, data;

    do {

        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Delete\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the data : ");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf("%d", &data);
            root = dThreadedBST(root, data);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please choose again.\n");
        
        }

    } while (choice != 4);

    return 0;
}
