#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct Node {
    int vertexNo;
    struct Node *pred; //previous node in the path
    int d; //distance
};

// priority Queue: min-heap ordering by distance
struct PQueue {
    int capacity;
    int size;
    struct Node *queue;
};

struct AdjMatrix {
    int numVertex;
    int **matrix;
};

int MinInThree(struct PQueue *Q, int parent){
    int min;
    if(Q->queue[parent * 2].d > Q->queue[parent * 2 + 1].d){
        min = parent * 2;
    }else{
        min = parent * 2 + 1;
    }
    if(Q->queue[parent].d > Q->queue[min].d){
        min = parent;
    }
    return min;
}

void Swap(struct Node *a, struct Node *b){
    struct Node tmp = *a;
    *a = *b;
    *b = tmp;
}

void HeapifyUpward(struct PQueue *Q, int nodeIdx){
    int parent = nodeIdx / 2;
    if(parent > 0 && Q->queue[parent].d > Q->queue[nodeIdx].d){
        //Swap 이런식으로 해도 되는건가? 
        Swap(&(Q->queue[parent]), &(Q->queue[nodeIdx]));
        HeapifyUpward(Q, parent);
    }
}

void HeapifyDownward(struct PQueue *Q){
    for(int parent = 1; parent <= (Q->size) / 2; parent *= 2){
        int minIdx = MinInThree(Q, parent);
        if(Q->queue[parent].d != Q->queue[minIdx].d){
            Swap(&(Q->queue[parent]), &(Q->queue[minIdx]));
        }else{
            return;
        }
    }
}

struct Node PopMin(struct PQueue *Q){
    if(Q->size == 0){
        printf("Delete fail: Empty priority Queue.\n");
    }else{
        struct Node minNode = Q->queue[1];
        Q->queue[1].d = Q->queue[Q->size].d;
        Q->queue[1].pred = Q->queue[Q->size].pred;
        Q->queue[1].vertexNo = Q->queue[Q->size].vertexNo;
        Q->size -= 1;
        HeapifyDownward(Q);
        return minNode;
    }
}

struct PQueue *CreatePQ(struct AdjMatrix *adjMatrix) {
    struct PQueue *PQ = (struct PQueue *)malloc(sizeof(struct PQueue));
    PQ->capacity = adjMatrix->numVertex;
    PQ->size = adjMatrix->numVertex;
    PQ->queue = (struct Node *)malloc(sizeof(struct Node) * PQ->capacity + 1);
    for(int i = 1; i <= PQ->capacity; i++) {
        PQ->queue[i].d = INT_MAX;
        PQ->queue[i].pred = NULL;
        PQ->queue[i].vertexNo = i;
    }
    return PQ;
}

void PrintPQueue(struct PQueue *Q){
    if(Q->size == 0){
        printf("Empty.\n");
    }else{
        for(int i = 1; i < Q->size + 1; i++){
            printf("%d  ", Q->queue[i].d);
        }
    }
}

int GetNumInputUnit(char *buf, int len)
{
    int size = 0;
    for (int i = 0; i < len; i++) {
        if (buf[i] == '\n' || buf[i] == '\0') {
            size += 1;
            break;
        }
        if (buf[i] == ' ') {
            size += 1;
        }
    }
    return size;
}

void InitializeMatrix(struct AdjMatrix *adjMatrix, FILE *fp) {
    int start, end, distance;
    while (!feof(fp)) {
        fscanf(fp, "%d%*c%d%*c%d ", &start, &end, &distance);
        adjMatrix->matrix[start][end] = distance;
    }
}

struct AdjMatrix *CreateAdjMatrix(FILE *fp) {
    char buf[128];
    fgets(buf, sizeof(buf), fp);
    struct AdjMatrix *adjMatrix = (struct AdjMatrix *)malloc(sizeof(struct AdjMatrix));
    adjMatrix->numVertex = GetNumInputUnit(buf, sizeof(buf));
    adjMatrix->matrix = (int **)malloc(sizeof(int *) * adjMatrix->numVertex + 1);
    for (int i = 0; i < adjMatrix->numVertex + 1; i++) {
        adjMatrix->matrix[i] = (int *)malloc(sizeof(int) * adjMatrix->numVertex + 1);
    }
    return adjMatrix;
}

void PrintMatrix(int **matrix) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void Relax(struct PQueue *Q, struct AdjMatrix *adjMatrix, int visitingVertex){
    for(int i = 1;i < adjMatrix->numVertex + 1; i++){
        if(adjMatrix->matrix[visitingVertex][i] != 0){
            if(Q->queue[visitingVertex].d + adjMatrix->matrix[visitingVertex][i] < Q->queue[i].d){
                Q->queue[i].d = Q->queue[visitingVertex].d + adjMatrix->matrix[visitingVertex][i];
                Q->queue[i].pred = &(Q->queue[visitingVertex]);
                HeapifyUpward(Q, i);
                printf("\nafter relaxation: ");
                PrintPQueue(Q);
            }
        }
    }
}

void PrintShortestPath(int start, int end, struct Node *popped){
    struct Node *nextNode;
    int count = 0;
    int pathVertexes[7] = {0, };
    while(1){
        if(popped->pred){
            if(popped->vertexNo == start)
                break;
            pathVertexes[count] = popped->vertexNo;
            nextNode = popped->pred;
        }else{
            printf("Nowhere to go end:%d\n", end);
            return;
        }
        count++;
    }
    for(int i = count; i <= 0; i--){
        printf("%d ", pathVertexes[i]);
    }
}
 
void RunDijkstra(struct AdjMatrix *adjMatrix, struct PQueue *Q, int start, int end){
    int count = 1;
    int visiting = start;
    Q->queue[visiting].d = 0;
    while(1){
        HeapifyUpward(Q, visiting);
        struct Node popped = PopMin(Q);
        visiting = popped.vertexNo;
        Relax(Q, adjMatrix, visiting);
        
        if(count > adjMatrix->numVertex - 1){
            PrintShortestPath(start, end, &popped);
            break;
        }
        count++;
    }
}
void DisposeAdjMatrix(struct AdjMatrix *adjMatrix){
    for(int i = 0; i < adjMatrix->numVertex + 1; i++){
        free(adjMatrix->matrix[i]);
    }
    free(adjMatrix->matrix);
    free(adjMatrix);
}

void DisposePQueue(struct PQueue *PQ){
    free(PQ->queue);
    free(PQ);
}

int main(int argc, const char *argv[]) {
    if(argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if(fp == NULL) {
            printf("Execute with an input file. \n");
            return 0;
        }

        struct AdjMatrix *adjMatrix = CreateAdjMatrix(fp);
        InitializeMatrix(adjMatrix, fp);
        struct PQueue *PQ = NULL;
        
        int start = 0;
        int end = 0;
        char restart = 'Y';
        while(restart == 'Y'){
            printf("Start : ");
            scanf("%d", &start);
            printf("End : ");
            scanf("%d", &end);
            
            PQ = CreatePQ(adjMatrix);
            RunDijkstra(adjMatrix, PQ, start, end);
            DisposeAdjMatrix(adjMatrix);
            //DisposePQueue(PQ);
            
            printf("\nrestart? (Y/N) :");
            scanf("%*c%c", &restart);
        }   
    }
}

