#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
    int size, f, r;
    int *arr;
} queue;

int isFull(queue *ptr) {
    return (ptr->r == ptr->size - 1);
}

int isEmpty(queue *ptr) {
    return (ptr->r == ptr->f);
}

void enqueue(queue *ptr, int data) {
    ptr->r++;
    ptr->arr[ptr->r] = data;
}

int dequeue(queue *ptr) {
    int a = ptr->arr[ptr->f];
    ptr->f++;
    return a;
}

struct Node {
    int vertex;
    struct Node *next;
};

struct Graph {
    int numVertices;
    struct Node **adjLists;
};

struct Node *createNode(int v) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int V) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = V;

    graph->adjLists = (struct Node **)malloc(V * sizeof(struct Node *));

    for (int i = 0; i < V; ++i) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest) {
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph *graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node *temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Non-Recursive BFS Traversal
void nonRecursiveBFS(struct Graph *graph, int startVertex) {
    bool visited[graph->numVertices];
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = false;
    }

    queue q;
    q.size = graph->numVertices;
    q.f = -1;
    q.r = -1;
    q.arr = (int *)malloc(q.size * sizeof(int));

    visited[startVertex] = true;
    enqueue(&q, startVertex);

    printf("Non-Recursive BFS Traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        struct Node *temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(&q, adjVertex);
            }
            temp = temp->next;
        }
    }

    printf("\n");
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    struct Graph *graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter edges (format: source destination):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("\nGraph created:\n");
    printGraph(graph);

    int startVertex;
    printf("Enter the starting vertex for BFS traversal: ");
    scanf("%d", &startVertex);

    nonRecursiveBFS(graph, startVertex);

    return 0;
}
