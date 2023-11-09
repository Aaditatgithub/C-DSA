#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define V 5 // Number of vertices

int find(int parent[], int node) {
    while (parent[node] != node)
        node = parent[node];
    return node;
}

void unionSets(int parent[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    parent[rootX] = rootY;
}

void kruskalMST(int graph[V][V]) {
    int parent[V];
    int minEdgeCount = 0;

    // Initialize parent array
    for (int i = 0; i < V; i++)
        parent[i] = i;

    printf("Edges in the Minimum Spanning Tree:\n");

    while (minEdgeCount < V - 1) {
        int minWeight = INT_MAX;
        int u, v;

        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (graph[i][j] && graph[i][j] < minWeight) {
                    int rootU = find(parent, i);
                    int rootV = find(parent, j);
                    if (rootU != rootV) {
                        minWeight = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU != rootV) {
            unionSets(parent, u, v);
            printf("(%d, %d) Weight: %d\n", u, v, minWeight);
            minEdgeCount++;
        }
    }
}


int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 9},
        {6, 8, 0, 0, 0},
        {0, 5, 9, 0, 0}
    };

    kruskalMST(graph);
    return 0;
}
