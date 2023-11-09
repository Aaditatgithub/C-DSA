#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct AdjMatrix{
	int vertices, edges;
	int **matrix;
}Matrix;

Matrix* createMatrix(int v, int e){
	Matrix* temp = (Matrix*)malloc(sizeof(Matrix));
	temp->vertices = v;
	temp->edges = e;
	temp->matrix = (int**)malloc(sizeof(int*)*v);
	for(int i = 0; i < v; i++){
		temp->matrix[i] = (int*)calloc(v,sizeof(int));
	}
	return temp;
}

void initMatrix(Matrix* matrix, int src, int dest, int weight){
	if(src < matrix->vertices && src >= 0 && dest < matrix->vertices && dest >= 0){
		matrix->matrix[src][dest] = weight;
		matrix->matrix[dest][src] = weight;
	}
	else{
		printf("Enter valid edge");
	}
}

int minDistance(int dist[], bool sptSet[],int vertices) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }  
    return min_index;
}

void printSolution(int dist[], int vertices) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

void dijkstra(Matrix* matrix, int src) {
    int *dist = (int*)malloc(sizeof(int)*matrix->vertices);
    bool *sptSet = (bool*)malloc(sizeof(bool)*matrix->vertices);

    for(int i = 0 ; i < matrix->vertices; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for(int i = 0; i < matrix->vertices - 1; i++){
        // nearest node
        int u = minDistance(dist,sptSet,matrix->vertices);

        //marked in mst
        sptSet[u] = true;

        for(int v = 0; v < matrix->vertices; v++){
            if(!sptSet[v] && matrix->matrix[u][v] && (dist[u] + matrix->matrix[u][v] < dist[v])){
                dist[v] = dist[u] + matrix->matrix[u][v];
            }
        }
    }
    printSolution(dist,matrix->vertices);
}

int main() {
    
    int vertex, edges, weight;
	int src, dest;
	printf("Enter the number of vertices, edges in graph\n");
	scanf("%d %d",&vertex,&edges);

	Matrix* matrix = createMatrix(vertex, edges);
    char c;
	for(int i = 0; i < edges; i++){
       // while((c = getchar()) != 10); 
		printf("Enter the source destination weight: ");
		scanf("%d %d %d",&src, &dest, &weight);
		initMatrix(matrix, src, dest, weight);
	}

    dijkstra(matrix, 4);
    
    return 0;
}
