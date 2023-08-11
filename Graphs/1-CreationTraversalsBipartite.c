#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Stack {
    int top;
    int size;
    int *array;
}stack;

int isEmpty(stack* s) {
    return s->top == -1;
}

void push(stack* s, int item) {
    if (s->top == s->size - 1) {
        printf("Stack overflow.\n");
        return;
    }
    s->array[++s->top] = item;
}

int pop(stack* s) {
    return s->array[s->top--];
}
typedef struct queue{
    int size,f,r;
    int *arr;
}queue;

int isFull(queue *ptr){
    return (ptr->r == ptr->size - 1);
}

int isEmpty(queue *ptr){
    return (ptr->r == ptr->f);
}

void enqueue(queue *ptr, int data){

    ptr->r++;
    ptr->arr[ptr->r] = data;
}

int dequeue(queue *ptr){
    int a;
    ptr->f++;
    a = ptr->arr[ptr->f];
    return a;
}

void clearVisited(int *visitedArr, int num_nodes){
    for(int i = 0; i<num_nodes; i++){
        visitedArr[i] = 0;
    }
}

// Functions for Matrix Graph -----------------------------------------------------------------------------------------------------
void BreadthFirstSearch_NonRecursive_ADJMAT(int **matrix, int* visited, queue* neighbours, int num_nodes, int vertex){

    printf("%d ",vertex);
    visited[vertex] = 1;
    enqueue(neighbours, vertex);

    while(!isEmpty(neighbours)){
        int node = dequeue(neighbours);
        for(int i = 0; i < num_nodes; i++){
            if(matrix[node][i] == 1 && visited[i] == 0){
                printf("%d ", i);
                visited[i] = 1;
                enqueue(neighbours,i);
            } 
        }
    }
}

void recursiveBFS(int **matrix, int* visited, queue* neighbours, int num_nodes) {
    if (isEmpty(neighbours))
        return;

    int node = dequeue(neighbours);
    printf("%d ", node);

    for (int i = 0; i < num_nodes; i++) {
        if (matrix[node][i] == 1 && visited[i] == 0) {
            visited[i] = 1;
            enqueue(neighbours, i);
        }
    }

    recursiveBFS(matrix, visited, neighbours, num_nodes);
}

void BreadthFirstSearch_Recursive_ADJMAT(int **matrix, int* visited, queue* neighbours, int num_nodes, int start_vertex) {
    visited[start_vertex] = 1;
    enqueue(neighbours, start_vertex);

    recursiveBFS(matrix, visited, neighbours, num_nodes);
}

void DepthFirstSearch_NonRecursive_ADJMAT(int **matrix, int* visited, int num_nodes, int start_vertex){
   
    stack *dfsStack = (stack*)malloc(sizeof(stack));
    dfsStack->size = num_nodes;
    dfsStack->top = -1;
    dfsStack->array = (int*)malloc(sizeof(int)*num_nodes);

    push(dfsStack, start_vertex);

    while (!isEmpty(dfsStack)) {
        int node = pop(dfsStack);
        if (visited[node])
            continue;

        printf("%d ", node);
        visited[node] = 1;

        for (int i = num_nodes - 1; i >= 0; i--) {
            if (matrix[node][i] == 1 && !visited[i]) {
                push(dfsStack, i);
            }
        }
    }
}

void DepthFirstSearch_Recursive_ADJMAT(int **matrix, int* visited, int num_nodes, int vertex){
    
    printf("%d ",vertex);
    visited[vertex] = 1;
    for (int j = 0; j < num_nodes; j++){
        if(matrix[vertex][j]==1 && !visited[j])
            DepthFirstSearch_Recursive_ADJMAT(matrix,visited,num_nodes,j);
    }   
}

void printBipartiteSets_ADJMAT(int* colors, int numVertices) {
    printf("Vertices in Set 1: ");
    for (int i = 0; i < numVertices; ++i) {
        if (colors[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Vertices in Set 2: ");
    for (int i = 0; i < numVertices; ++i) {
        if (colors[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int isBipartite_ADJMAT(int** graph, int numVertices, int startVertex) {
    int* colors = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; ++i) {
        colors[i] = -1; // -1 indicates uncolored
    }

    colors[startVertex] = 0;

    int queue[numVertices];
    int front = 0, rear = -1;

    queue[++rear] = startVertex;

    while (front <= rear) {
        int vertex = queue[front++];

        for (int adjVertex = 0; adjVertex < numVertices; ++adjVertex) {
            if (graph[vertex][adjVertex] && colors[adjVertex] == -1) {
                colors[adjVertex] = 1 - colors[vertex];
                queue[++rear] = adjVertex;
            } else if (graph[vertex][adjVertex] && colors[adjVertex] == colors[vertex]) {
                free(colors);
                printf("The vertices cannot be divided into two sets, since"
                    " vertices %d and %d have same color, while being adjacent.",vertex,adjVertex);
                return 0; // Not bipartite
            }
        }
    }
    printf("The graph can be divided into the following sets:\n");
    printBipartiteSets_ADJMAT(colors, numVertices);

    free(colors);
    return 1; // Bipartite
}

//Functions for Adjacency List ------------------------------------------------------------------------------------
struct Node {
    int vertex;
    struct Node* next;
};

typedef struct Graph {
    int numVertices;
    struct Node** adjLists;
}Graph;

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = V;

    graph->adjLists = (struct Node**)malloc(V * sizeof(struct Node*));

    for (int i = 0; i < V; ++i) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void nonRecursive_BFS_ADJLIST(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    struct Node* queue = createNode(startVertex);
    visited[startVertex] = 1;

    while (queue) {
        int vertex = queue->vertex;
        printf("%d ", vertex);
        
        struct Node* temp = graph->adjLists[vertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                struct Node* newQueueNode = createNode(adjVertex);

                // Enqueue the new node at the end of the queue
                struct Node* queueTemp = queue;
                while (queueTemp->next) {
                    queueTemp = queueTemp->next;
                }
                queueTemp->next = newQueueNode;
            }
            temp = temp->next;
        }

        // Dequeue the processed node
        struct Node* tempQueue = queue;
        queue = queue->next;
        free(tempQueue);
    }
    free(visited);
}


void recursiveBFS_adjlist(struct Graph* graph, int* queue, int* visited, int queueStart, int queueEnd) {
    if (queueStart > queueEnd) {
        return;
    }

    int vertex = queue[queueStart];
    queueStart++;
    printf("%d ", vertex);

    visited[vertex] = 1;

    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            queueEnd++;
            queue[queueEnd] = adjVertex;
            visited[adjVertex] = 1;
        }
        temp = temp->next;
    }

    recursiveBFS_adjlist(graph, queue, visited, queueStart, queueEnd);
}

void recursive_BFS_ADJLIST(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    queue[0] = startVertex;

    printf("Recursive BFS Traversal starting from vertex %d: ", startVertex);
    recursiveBFS_adjlist(graph, queue, visited, 0, 0);

    free(queue);
    free(visited);
}

void NonRecursive_DFS_ADJLIST(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    // Create a stack for DFS traversal
    int stack[graph->numVertices];
    int top = -1;

    stack[++top] = startVertex;

    while (top >= 0) {
        int vertex = stack[top--];

        if (!visited[vertex]) {
            printf("%d ", vertex);
            visited[vertex] = 1;

            struct Node* temp = graph->adjLists[vertex];
            while (temp) {
                if (!visited[temp->vertex]) {
                    stack[++top] = temp->vertex;
                }
                temp = temp->next;
            }
        }
    }

    free(visited);
}

void DFSRecursive_adjlist(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFSRecursive_adjlist(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void Recursive_DFS_ADJLIST(struct Graph* graph, int startVertex) {
    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSRecursive_adjlist(graph, startVertex, visited);

    free(visited);
}


int edgeExists(struct Graph* graph, int src, int dest) {
    struct Node* temp = graph->adjLists[src];
    while (temp) {
        if (temp->vertex == dest) {
            return 1; // Edge already exists
        }
        temp = temp->next;
    }
    return 0; // Edge doesn't exist
}

void AddEdge(struct Graph *graph, int num_vertices){

    printf("Enter edge (source destination): ");
    int src, dest;
    scanf("%d %d", &src, &dest);

    if (src >= 0 && src < num_vertices && dest >= 0 && dest < num_vertices) {
        if (!edgeExists(graph, src, dest)) { // Add this check
            addEdge(graph, src, dest);
            printf("Edge added between %d and %d.\n", src, dest);
        } else {
            printf("Edge already exists between %d and %d.\n", src, dest); // Error message for duplicate edge
        }
    } 
    else {
        printf("Invalid vertex index.\n");
    }  
}

void printBipartiteSets(struct Graph* graph, int* colors) {
    printf("Vertices in Set 1: ");
    for (int i = 0; i < graph->numVertices; ++i) {
        if (colors[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Vertices in Set 2: ");
    for (int i = 0; i < graph->numVertices; ++i) {
        if (colors[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int isBipartite(struct Graph* graph, int startVertex) {
    
    int* colors = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        colors[i] = -1; // -1 indicates uncolored
    }

    colors[startVertex] = 0;

    struct Node* queue = createNode(startVertex);

    while (queue) {
        int vertex = queue->vertex;
        queue = queue->next;

        struct Node* temp = graph->adjLists[vertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (colors[adjVertex] == -1) {
                colors[adjVertex] = 1 - colors[vertex];
                struct Node* newQueueNode = createNode(adjVertex);
                newQueueNode->next = queue;
                queue = newQueueNode;
            } else if (colors[adjVertex] == colors[vertex]) {
                free(colors);
                printf("The colors of %d and %d are same even though they are adjacent\n",vertex, adjVertex);
                printf("Thus, by color coding we can say that the graph cannot be divided into 2 sets of vertices"
                       " such that set of vertices belonging to a set, remain disconnected\n"
                        );
                return 0; // Not bipartite
            }
            temp = temp->next;
        }
    }

    printf("The graph can be divided into the following sets:\n");
    printBipartiteSets(graph, colors);

    free(colors);
    return 1; // Bipartite
}

int main(){

    int choice;
    int num_vertices;
    int mat_input;
    int vertex;
    int edges_connected;
    printf("Wanna create a Graph by: \n1. Adjacency Matrix(enter 1) \n2. Adjacency List(enter 2) \n");
    scanf("%d", &choice);
    
    do{
        while(choice != 1 && choice != 2){
            printf("Invalid option:\n");
            printf("Wanna create a Graph by: \n1. Adjacency Matrix(enter 1) \n2. Adjacency List(enter 2) \n");
            scanf("%d", &choice);
        }

        switch(choice){
            case 1:{
                printf("How many vertices do you want in your Graph\n");
                scanf("%d", &num_vertices);

                //array to determine which nodes have been visited
                int *visited = (int*)calloc(num_vertices, sizeof(int));

                //queue to keep track of adjacent nodes to a node in graph
                queue *neighbours = (queue*)malloc(sizeof(queue));
                neighbours->size = num_vertices;
                neighbours->f = neighbours->r = -1;
                neighbours->arr = (int*)malloc(sizeof(int)*num_vertices);

                //Dynamic allocation of 2d Matrix
                int** Matrix = (int**)malloc(num_vertices * sizeof(int*));
                for (int i = 0; i < num_vertices; ++i) {
                    Matrix[i] = (int*)calloc(num_vertices,sizeof(int));
                }

                printf("Enter the Adjacency Matrix for the Graph:\n");
                //Initializing matrix
                for(int i = 0; i<num_vertices; i++){
                    for(int j = 0; j<num_vertices; j++){ 
                        scanf("%d",&mat_input);
                        Matrix[i][j] = mat_input;
                    }
                }
                do{
                    printf("\nEnter the operation you want to perform:\n"
                            "0. Exit \n1. BFS without Recursion\n2. BFS with Recursion"
                            "\n3. DFS without Recursion \n4. DFS with Recursion\n"
                            "5. Check if bipartite \nEnter a choice:");
                    scanf("%d",&choice);
                    
                    switch(choice){
                        case 0:
                            printf("Exiting...");
                            break;
                        case 1:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ",num_vertices-1);
                            scanf("%d",&vertex);
                            BreadthFirstSearch_NonRecursive_ADJMAT(Matrix,visited,neighbours,num_vertices,vertex);
                            clearVisited(visited,num_vertices);
                            neighbours->f = neighbours->r = -1;
                            break;
                        case 2:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ",num_vertices-1);
                            scanf("%d",&vertex);
                            BreadthFirstSearch_Recursive_ADJMAT(Matrix,visited,neighbours, num_vertices,vertex);
                            clearVisited(visited,num_vertices);
                            neighbours->f = neighbours->r = -1;
                            break;
                        case 3:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ",num_vertices-1);
                            scanf("%d",&vertex);
                            DepthFirstSearch_NonRecursive_ADJMAT(Matrix, visited, num_vertices, vertex);
                            clearVisited(visited,num_vertices);
                            break;
                        case 4: 
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices-1);
                            scanf("%d",&vertex);
                            DepthFirstSearch_Recursive_ADJMAT(Matrix,visited,num_vertices,vertex);
                            clearVisited(visited,num_vertices);
                            break;
                        case 5:
                            if (isBipartite_ADJMAT(Matrix, num_vertices, 0)) 
                                printf("The graph is bipartite.\n");
                            else 
                                printf("The graph is not bipartite.\n");
                            break;
                    }

                }while(choice);

                free(neighbours);
                free(Matrix);
                free(visited);
            }
            break;
            case 2:{
            
                printf("Enter the number of vertices: ");
                scanf("%d", &num_vertices);
                struct Graph* graph = createGraph(num_vertices);

                while(1){

                    printf("\nMenu:\n");
                    printf("0. Exit\n");
                    printf("1. Add an edge\n");
                    printf("2. Print the graph\n");
                    printf("3. Non-Recursive BFS Traversal\n");
                    printf("4. Recursive BFS Traversal\n");
                    printf("5. Non-Recursive DFS Traversal\n");
                    printf("6. Recursive DFS Traversal\n");
                    printf("7. Check if Bipartite\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 0:
                            printf("Exiting program.\n");
                        case 1:      
                            AddEdge(graph,num_vertices);
                            break;
                        case 2:
                            printf("\nGraph:\n");
                            printGraph(graph);
                            break;
                        case 3:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices-1);
                            scanf("%d",&vertex);
                            nonRecursive_BFS_ADJLIST(graph, vertex);
                            break;
                        case 4:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices-1);
                            scanf("%d",&vertex);
                            recursive_BFS_ADJLIST(graph, vertex);
                            break;
                        case 5:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices-1);
                            scanf("%d",&vertex);
                            NonRecursive_DFS_ADJLIST(graph, vertex);
                            break;
                        case 6:
                            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices-1);
                            scanf("%d",&vertex);
                            Recursive_DFS_ADJLIST(graph,vertex);
                            break;
                        case 7:
                            if (isBipartite(graph, 0)) 
                                printf("The graph is bipartite.\n");
                            else 
                                printf("The graph is not bipartite.\n");
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }
                }
            }   
        }
        printf("Do you want to create a graph?\n"
               "Enter 1 To continue:\n"
               "Enter 0 To Confirm your Exit:\n"
            );
        scanf("%d",&choice);

    }while(choice);
    
    return 0;
}       