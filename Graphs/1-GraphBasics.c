#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//Generic stack and queue functions required for operations

typedef struct Stack {
    int top;
    int size;
    int* array;
}stack;

int isEmpty_stack(stack* s) {
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

typedef struct queue {
    int size, f, r;
    int* arr;
}queue;

int isFull(queue* ptr) {
    return (ptr->r == ptr->size - 1);
}

int isEmpty(queue* ptr) {
    if (ptr->f == ptr->r)
        return 1;
    return 0;
}

void enqueue(queue* ptr, int data) {
    ptr->r++;
    ptr->arr[ptr->r] = data;
}

int dequeue(queue* ptr) {
    int a;
    ptr->f++;
    a = ptr->arr[ptr->f];
    return a;
}

void clearVisited(int* visited, int size) {
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    return;
}

//Functions for Adjacency Matrix

void AddEdge_Matrix(int** matrix, int num_vertices, int src, int dest) {
    if (src >= 0 && src < num_vertices && dest >= 0 && dest < num_vertices) {
        matrix[src][dest] = 1;
        matrix[dest][src] = 1;
        return;
    }
    else {
        return;
    }
}

void DFS_Mat_recursive(int** matrix, int* visited, int num_nodes, int vertex) {

    printf("%d ", vertex);
    visited[vertex] = 1;
    for (int j = 0; j < num_nodes; j++) {
        if (matrix[vertex][j] == 1 && !visited[j])
            DFS_Mat_recursive(matrix, visited, num_nodes, j);
    }
}

void DepthFirstSearch_NonRecursive_ADJMAT(int** matrix, int* visited, int num_nodes, int start_vertex) {

    stack* dfsStack = (stack*)malloc(sizeof(stack));
    dfsStack->size = num_nodes;
    dfsStack->top = -1;
    dfsStack->array = (int*)malloc(sizeof(int) * num_nodes);

    push(dfsStack, start_vertex);

    while (!isEmpty_stack(dfsStack)) {
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

void BreadthFirstSearch_NonRecursive_ADJMAT(int** matrix, int* visited, queue* neighbours, int num_nodes, int vertex) {

    printf("%d ", vertex);
    visited[vertex] = 1;
    enqueue(neighbours, vertex);

    while (!isEmpty(neighbours)) {
        int node = dequeue(neighbours);
        for (int i = 0; i < num_nodes; i++) {
            if (matrix[node][i] == 1 && visited[i] == 0) {
                printf("%d ", i);
                visited[i] = 1;
                enqueue(neighbours, i);
            }
        }
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
    int queue[10];
    int front = 0, rear = -1;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int vertex = queue[front++];

        for (int adjVertex = 0; adjVertex < numVertices; ++adjVertex) {
            if (graph[vertex][adjVertex] && colors[adjVertex] == -1) {
                colors[adjVertex] = 1 - colors[vertex];
                queue[++rear] = adjVertex;
            }
            else if (graph[vertex][adjVertex] && colors[adjVertex] == colors[vertex]) {
                free(colors);
                printf("The vertices cannot be divided into two sets,\nsince"
                    " vertices %d and %d have same color, while being adjacent."
                    , vertex, adjVertex);
                return 0; // Not bipartite
            }
        }
    }
    printf("The graph can be divided into the following sets:\n");
    printBipartiteSets_ADJMAT(colors, numVertices);

    free(colors);
    return 1; // Bipartite
}

void PrintMatrix(int** matrix, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            printf("%d ", matrix[i][j]);
        }printf("\n");
    }
}

//Functions for Adjacency List

typedef struct node {
    int vertex;
    struct node* next;
}node;

typedef struct graph {
    int numVertices;
    node** AdjList;
}graph;

node* createNode(int key) {
    node* x = (node*)malloc(sizeof(node));
    x->next = NULL;
    x->vertex = key;
    return x;
}

void addEdge(graph* graph, int src, int dest) {
    node* newNode = createNode(dest);
    newNode->next = graph->AdjList[src];
    graph->AdjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->AdjList[dest];
    graph->AdjList[dest] = newNode;
}

int edgeExists(graph* graph, int src, int dest) {
    node* temp = graph->AdjList[src];
    while (temp) {
        if (temp->vertex == dest) {
            return 1; // Edge already exists
        }
        temp = temp->next;
    }
    return 0; // Edge doesn't exist 
}

void AddEdge_AdjList(graph* graph, int num_vertices, int src, int dest, int* p) {

    if (src >= 0 && src < num_vertices && dest >= 0 && dest < num_vertices) {
        if (!edgeExists(graph, src, dest)) { // Add this check
            addEdge(graph, src, dest);
            printf("Edge added between %d and %d.\n", src, dest);
        }
        else {
            (*p)--;
            printf("Edge already exists between %d and %d.\n", src, dest); // Error message for duplicate edge
        }
    }
    else {
        (*p)--;
        printf("Invalid vertex index.\n");
    }
}

graph* createGraph(int vertices) {
    graph* G = (graph*)malloc(sizeof(graph));
    G->numVertices = vertices;
    G->AdjList = (node**)malloc(sizeof(node));

    for (int i = 0; i < vertices; i++) {
        G->AdjList[i] = NULL;
    }
    return G;
}

void DFSRecursive_adjlist(graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    node* temp = graph->AdjList[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFSRecursive_adjlist(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void Recursive_DFS_ADJLIST(graph* graph, int startVertex, int* visited) {

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSRecursive_adjlist(graph, startVertex, visited);
}

void NonRecursive_DFS_ADJLIST(graph* graph, int startVertex, int* visited) {

    // Create a stack for DFS traversal
    int stack[20];
    int top = -1;

    stack[++top] = startVertex;

    while (top >= 0) {
        int vertex = stack[top--];


        if (!visited[vertex]) {
            printf("%d ", vertex);
            visited[vertex] = 1;


            node* temp = graph->AdjList[vertex];
            while (temp) {
                if (!visited[temp->vertex]) {
                    stack[++top] = temp->vertex;
                }
                temp = temp->next;
            }
        }
    }
}

void nonRecursive_BFS_ADJLIST(graph* graph, int startVertex, int* visited) {

    node* queue = createNode(startVertex);
    visited[startVertex] = 1;


    while (queue) {
        int vertex = queue->vertex;
        printf("%d ", vertex);

        node* temp = graph->AdjList[vertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                node* newQueueNode = createNode(adjVertex);


                // Enqueue the new node at the end of the queue
                node* queueTemp = queue;
                while (queueTemp->next) {
                    queueTemp = queueTemp->next;
                }
                queueTemp->next = newQueueNode;
            }
            temp = temp->next;
        }


        // Dequeue the processed node
        node* tempQueue = queue;
        queue = queue->next;
        free(tempQueue);
    }
}

void printBipartiteSets(graph* graph, int* colors) {
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

int isBipartite(graph* graph, int startVertex) {

    int* colors = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        colors[i] = -1; // -1 indicates uncolored
    }

    colors[startVertex] = 0;
    node* queue = createNode(startVertex);

    while (queue) {
        int vertex = queue->vertex;
        queue = queue->next;

        node* temp = graph->AdjList[vertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (colors[adjVertex] == -1) {
                colors[adjVertex] = 1 - colors[vertex];
                node* newQueueNode = createNode(adjVertex);
                newQueueNode->next = queue;
                queue = newQueueNode;
            }
            else if (colors[adjVertex] == colors[vertex]) {
                free(colors);
                printf("The colors of %d and %d are same even though they are adjacent\n", vertex, adjVertex);
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

void printAdjacencyList(graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        node* temp = graph->AdjList[i];
        printf("Adjacency list of vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}


int main() {

    int choice = 1;
    int num_vertices;
    int num_edges;
    int vertex;
    int src, dest;


    printf("Creating a Graph\n");
    printf("Enter the number of vertices in the graph : ");
    scanf("%d", &num_vertices);
    printf("Enter the number of edges in the graph : ");
    scanf("%d", &num_edges);

    //Matrix created for Adjacency Matrix
    int** Matrix = (int**)malloc(sizeof(int*) * num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        Matrix[i] = (int*)calloc(num_vertices, sizeof(int));
    }

    //Graph for Adjacency List
    graph* G = createGraph(num_vertices);

    printf("Memory has been alloted...\n");
    int i;
    //Adding edges for Graph
    for (i = 0; i < num_edges; i++) {
        printf("Enter edge %d (source-destination) : ", i);
        fflush(stdin);
        scanf("%d", &src);
        scanf("%d", &dest);
        AddEdge_AdjList(G, num_vertices, src, dest, &i);
        AddEdge_Matrix(Matrix, num_vertices, src, dest);
    }
    printf("Graph has been created...\n");

    //Array for operations
    int* visited = (int*)calloc(num_vertices, sizeof(int));
    //queue for BFS
    queue* neighbours = (queue*)malloc(sizeof(queue));
    neighbours->size = num_vertices;
    neighbours->arr = (int*)malloc(sizeof(int) * num_vertices);
    neighbours->f = neighbours->r = -1;

    do {
        printf("\n---Menu---\n"
            "1. DFS using adjacency list with recursion\n"
            "2. DFS using adjacency list without recursion\n"
            "3. DFS using adjacency matrix with recursion\n"
            "4. DFS using adjacency matrix without recursion\n"
            "5. BFS using adjacency list without recursion\n"
            "6. BFS using adjacency matrix without recursion\n"
            "7. If the input graph is bipartite for Adjacency Matrix\n"
            "8. If the input graph is bipartite for Adjacency List\n"
            "9. Print Matrix\n"
            "10.Print Adjacency List\n"
        );
        printf("Enter the operation : ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices - 1);
            scanf("%d", &vertex);
            Recursive_DFS_ADJLIST(G, vertex, visited);
            clearVisited(visited, num_vertices);
            break;
        case 2:
            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices - 1);
            scanf("%d", &vertex);
            NonRecursive_DFS_ADJLIST(G, vertex, visited);
            clearVisited(visited, num_vertices);
            break;
        case 3:
            printf("Enter the vertex to start traversal from :");
            scanf("%d", &vertex);
            DFS_Mat_recursive(Matrix, visited, num_vertices, vertex);
            clearVisited(visited, num_vertices);
            break;
        case 4:
            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices - 1);
            scanf("%d", &vertex);
            DepthFirstSearch_NonRecursive_ADJMAT(Matrix, visited, num_vertices, vertex);
            clearVisited(visited, num_vertices);
            break;
        case 5:
            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices - 1);
            scanf("%d", &vertex);
            nonRecursive_BFS_ADJLIST(G, vertex, visited);
            clearVisited(visited, num_vertices);
            break;
        case 6:
            printf("Enter the vertex you want to start the traversal with (0 - %d): ", num_vertices - 1);
            scanf("%d", &vertex);
            BreadthFirstSearch_NonRecursive_ADJMAT(Matrix, visited, neighbours, num_vertices, vertex);
            clearVisited(visited, num_vertices);
            neighbours->f = -1; neighbours->r = -1;
            break;
        case 7:
            if (isBipartite_ADJMAT(Matrix, num_vertices, 0))
                printf("\nThe graph is bipartite.\n");
            else
                printf("\nThe graph is not bipartite.\n");
            break;
        case 8:
            if (isBipartite(G, 0))
                printf("\nThe graph is bipartite.\n");
            else
                printf("\nThe graph is not bipartite.\n");
            break;
        case 9:
            PrintMatrix(Matrix, num_vertices);
            break;
        case 10:
            printAdjacencyList(G);
            break;
        }
        printf("\nWanna continue?\n"
            "1. YES\n"
            "0. NO\n"
        );
        scanf("%d", &choice);

    } while (choice != 0);
    
    printf("\nExiting...");
    free(neighbours);
    free(visited);
    return 0;
}