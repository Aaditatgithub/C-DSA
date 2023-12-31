#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int data, weight;
    struct node* next;
}node;

node** createlist(int vertices) {
    node** newlist = (node**)malloc(sizeof(node*) * vertices);
    for (int i = 0; i < vertices; i++) {
        newlist[i] = NULL; // Initialize each list element to NULL
    }
    return newlist;
}

node* createnode(int vertex, int weight) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = vertex;
    newnode->weight = weight;
    newnode->next = NULL;
    return newnode;
}

void addedge(node** list, int src, int dest, int weight) {
    node* temp = list[src];
    if (temp == NULL) {
        list[src] = createnode(dest, weight);
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createnode(dest, weight);
    }

    temp = list[dest];
    if (temp == NULL) {
        list[dest] = createnode(src, weight);
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createnode(src, weight);
    }
}

void printgraph(node** list, int vertices) {
    for (int i = 0; i < vertices; i++) {
        node* temp = list[i];
        printf("Vertices of %d vertex: ", i);
        while (temp) {
            printf("(%d,%d)->", temp->data, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void BFS(node** list, int src, int vertices){
    int* visited = (int*)malloc(sizeof(int)*vertices);
    for(int i = 0; i < vertices;i++){
        visited[i] = 0;
    }

    int queue[10];
    int f = -1;
    int r = -1;
    queue[++r] = src;
    printf("%d ",src);
    visited[src] = 1;

    while(f != r){
        node* temp = list[++f];
        while(temp){
            if(visited[temp->data] != 1){
                printf("%d ", temp->data);
                visited[temp->data] = 1;
                queue[++r] = temp->data;
            }
            temp = temp->next;
        }
    }    
}

void DFS(node** list, int src, int vertices){
    int *visited = (int*)calloc(vertices, sizeof(int));
    int stack[20];
    int top = -1;

    stack[++top] = src;
    while(top >= 0){
        int vert = stack[top--];
        if(!visited[vert]){
            printf("%d ",vert);
            visited[vert] = 1;

            node* temp = list[vert];
            while(temp){
                if(!visited[temp->data])
                    stack[++top] = temp->data;
                temp = temp->next;
            }
        }
    }
}
 
void Prims(node** list, int vertices){
    int* key = (int*)malloc(sizeof(key)*vertices);
    int* mst = (int*)calloc(vertices,sizeof(key));
    int* parent = (int*)malloc(sizeof(key)*vertices);

    //init
    for(int i = 0; i < vertices; i++){
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;

    //starting the algo
    for(int count = 1; count < vertices - 1; count++){
        int mini = INT_MAX;
        int u;         // nearest node

        //checking nearest node
        for(int i = 0; i < vertices; i++){
            if(!mst[i] && key[i] < mini){
                u = i;
                mini = key[i];
            }
        } 
        
        // nearest node added to mst
        mst[u] = 1;

        //checking adjacent nodes
        node* temp = list[u];
        while(temp){
            if(!mst[temp->data] && (temp->weight) < key[temp->data]){
               parent[temp->data] = u;
               key[temp->data] = temp->weight;
            }
            temp = temp->next;
        }
    }
    printf(" - Edges - Weight -\n");
    for(int i = 0; i < vertices; i++){
        printf("%d - %d , %d\n", parent[i], i, key[i]);
    }
}

int findparent(int* parent, int node){
    while(parent[node] != node){
        node = parent[node];
    }
    return node;
}

void unionsets(int *parent, int node1, int node2){
    int root_node1 = findparent(parent,node1);
    int root_node2 = findparent(parent,node2);
    parent[root_node1] = root_node2;
}

void kruskal(node** list, int vertices){
    int* parent = (int*)malloc(sizeof(int));
    int edges = 0;

    // init parent
    for (int i = 0; i < vertices; i++){
        parent[i] = i;
    }

    while(edges < vertices - 1){
        int minedge = INT_MAX;
        int u, v;               // nodes of min edge

        // find parents for the pair, if not equal assign
        for(int i = 0; i < vertices- 1; i++){
            node* temp = list[i];
            while(temp){
                if(temp->weight < minedge){
                    int rootU = findparent(parent, i);
                    int rootV = findparent(parent, temp->data);
                    if(rootU != rootV){
                        minedge = temp->weight;
                        u = i;
                        v = temp->data;
                    }           
                }
                temp = temp->next;
            }
        }

        int rootU = findparent(parent, u);
        int rootV = findparent(parent, v);
        
        // not equal parents, add to tree
        if(rootU != rootV){
            unionsets(parent, u, v);
            printf("%d - %d, %d\n",u,v,minedge);
            edges++;
        }
    }
}

void dijkstras(node** list, int src ,int vertices){
    int *dist = (int*)malloc(sizeof(int)*vertices);
    int *sptset = (int*)calloc(vertices, sizeof(int));

    for(int i = 0; i < vertices; i++){
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    //starting algo
    for(int count = 1; count < vertices -1; count++){
        int u;
        int min = INT_MAX;

        // finding nearest node
        for(int i = 0; i < vertices; i++){
            if(!sptset[i] && dist[i] < min){
                min = dist[i];
                u = i;
            }
        }
        // including it in shortest path traversal
        sptset[u] = 1;

        // updating distances of nearest nodes
        node* temp = list[u];
        while(temp){
            if(!sptset[temp->data] && temp->weight + dist[u] < dist[temp->data]){
                dist[temp->data] = dist[u] + temp->weight;
            }
            temp = temp->next;
        }
    }    

    printf("\nnode -- dist\n");
    for(int i = 0; i < vertices; i ++){
        printf("%d -- %d\n",i,dist[i]);
    }
}

int main() {
    int vertices = 5;
    int edges = 6;
    node** list = createlist(vertices);
    char c;

    for (int i = 0; i < edges; i++) {
        int src, dest, w;
       // while ((c = getchar()) != '\n'); // Clear input buffer
        printf("Enter src dest weight: ");
        scanf("%d%d%d", &src, &dest, &w);
        addedge(list, src, dest, w);
    }

    printgraph(list, vertices);
    printf("BFS :: ");
    BFS(list,1,vertices);
    printf("\nDFS :: ");
    DFS(list,0,vertices);
    Prims(list,5);
    dijkstras(list,0,vertices);
    kruskal(list,vertices);
    return 0;
}
