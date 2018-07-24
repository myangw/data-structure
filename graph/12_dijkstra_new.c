#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct Node {
    int vertex_no;
    int pred; //previous node in the path
    int d; //distance
};

// priority Queue: min-heap ordering by distance
struct PQueue {
    int capacity;
    int size;
    struct Node *queue;
};

struct AdjMatrix {
    int num_vertex;
    int **matrix;
};

int MinInThree(struct PQueue *Q, int parent) {
    int min = parent;
    if (Q->queue[min].d > Q->queue[parent * 2].d) {
        min = parent * 2;
    }
    if (Q->queue[min].d > Q->queue[parent * 2 + 1].d) {
        min = parent * 2 + 1;
    }
    return min;
}

void Swap(struct Node *a, struct Node *b) {
    struct Node tmp = *a;
    *a = *b;
    *b = tmp;
}

void HeapifyUpward(struct PQueue *Q, int node_idx) {
    int parent = node_idx / 2;
    if (parent > 0 && Q->queue[parent].d > Q->queue[node_idx].d) {
        Swap(&(Q->queue[parent]), &(Q->queue[node_idx]));
        HeapifyUpward(Q, parent);
    }
}

void HeapifyDownward(struct PQueue *Q) {
    for (int parent = 1; (parent * 2 + 1) <= (Q->size); parent *= 2) {
        int minIdx = MinInThree(Q, parent);
        if (Q->queue[parent].d != Q->queue[minIdx].d) {
            Swap(&(Q->queue[parent]), &(Q->queue[minIdx]));
        } else {
            return;
        }
    }
}

struct Node PopMin(struct PQueue *Q) {
    if (Q->size == 0) {
        return Q->queue[0];
    } else {
        struct Node minNode = Q->queue[1];
        Swap(&(Q->queue[1]), &(Q->queue[Q->size]));
        Q->size -= 1;
        HeapifyDownward(Q);
        return minNode;
    }
}

struct PQueue *CreatePQ(struct AdjMatrix *adj_matrix) {
    struct PQueue *PQ = (struct PQueue *)malloc(sizeof(struct PQueue));
    PQ->capacity = adj_matrix->num_vertex;
    PQ->size = adj_matrix->num_vertex;
    PQ->queue = (struct Node *)malloc(sizeof(struct Node) * (PQ->capacity + 1));
    for (int i = 0; i <= PQ->capacity; i++) {
        PQ->queue[i].vertex_no = i;
        PQ->queue[i].pred = 0;
        PQ->queue[i].d = INT_MAX;
    }
    return PQ;
}

//create an array that its index indicates vertex_no.
struct Node *CreateIdxArray(struct PQueue *Q) {
    struct Node *idxArray = (struct Node *)malloc(sizeof(struct Node) * (Q->size + 1));
    for (int i = 1; i < (Q->size) + 1; i++) {
        idxArray[i] = Q->queue[i];
    }
    return idxArray;
}

int GetNumInputUnit(char *buf, int len) {
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

void InitializeMatrix(struct AdjMatrix *adj_matrix, FILE *fp) {
    int start, end, distance;
    while (!feof(fp)) {
        fscanf(fp, "%d%*c%d%*c%d ", &start, &end, &distance);
        adj_matrix->matrix[start][end] = distance;
    }
}

struct AdjMatrix *CreateAdjMatrix(FILE *fp) {
    char buf[128];
    fgets(buf, sizeof(buf), fp);
    struct AdjMatrix *adj_matrix = (struct AdjMatrix *)malloc(sizeof(struct AdjMatrix));
    adj_matrix->num_vertex = GetNumInputUnit(buf, sizeof(buf));
    adj_matrix->matrix = (int **)malloc(sizeof(int *) * (adj_matrix->num_vertex + 1));
    
    for (int i = 0; i < adj_matrix->num_vertex + 1; i++) {
        adj_matrix->matrix[i] = (int *)malloc(sizeof(int) * (adj_matrix->num_vertex + 1));
    }
    return adj_matrix;
}

int FindQueueIdx(struct PQueue *Q, int vertex_no) {
    for (int i = 1; i < Q->size + 1; i++) {
        if (Q->queue[i].vertex_no == vertex_no)
            return i;
    }
}

void Relax (struct PQueue *Q, 
            struct AdjMatrix *adj_matrix, 
            struct Node *idxArray, 
            int visiting_vertex) {
    for (int i = 1; i < adj_matrix->num_vertex + 1; i++) {
        if (adj_matrix->matrix[visiting_vertex][i] != 0) {
            if (idxArray[visiting_vertex].d + adj_matrix->matrix[visiting_vertex][i] < idxArray[i].d) {
                int idx = FindQueueIdx(Q, i);
                idxArray[i].d = idxArray[visiting_vertex].d + adj_matrix->matrix[visiting_vertex][i];
                Q->queue[idx].d = idxArray[visiting_vertex].d + adj_matrix->matrix[visiting_vertex][i];
                idxArray[i].pred = idxArray[visiting_vertex].vertex_no;
                Q->queue[idx].pred = idxArray[visiting_vertex].vertex_no;
                HeapifyUpward(Q, idx);
            }
        }
    }
}

void PrintShortestPath(int start, struct PQueue *Q, struct Node *idxArray, struct Node end_node){
    struct Node nextNode = end_node;
    int count = 0;
    int path_vertexes[7] = {0, };
    while (1) {
        if (nextNode.pred != 0 || nextNode.vertex_no == start) {
            path_vertexes[count] = nextNode.vertex_no;
            if (nextNode.vertex_no == start)
                break;
            nextNode = idxArray[nextNode.pred];
            count++;
        } else {
            printf("Nowhere to go.\n");
            return;
        }
    }
    for (int i = count; i >= 0; i--) {
        printf("%d ", path_vertexes[i]);
    }
}
 
void RunDijkstra(struct AdjMatrix *adj_matrix, 
                 struct PQueue *Q, 
                 struct Node *idxArray, 
                 int start, 
                 int end) {
    int count = 1;
    struct Node end_node = Q->queue[0];
    int visiting = start;
    Q->queue[visiting].d = 0;
    idxArray[visiting].d = 0;
    Swap(&(Q->queue[visiting]), &(Q->queue[1]));
    
    while (1) {
        visiting = Q->queue[1].vertex_no;
        Relax(Q, adj_matrix, idxArray, visiting);
        struct Node popped = PopMin(Q);
        if (popped.vertex_no == end)
            end_node = popped;
        if (Q->size == 0)
            break;
        count++;
    }
    PrintShortestPath(start, Q, idxArray, end_node);
}

void DisposeAdjMatrix(struct AdjMatrix *adj_matrix) {
    for (int i = 0; i < adj_matrix->num_vertex + 1; i++) {
        free(adj_matrix->matrix[i]);
    }
    free(adj_matrix->matrix);
    free(adj_matrix);
}

void DisposePQueue(struct PQueue *PQ) {
    free(PQ->queue);
    free(PQ);
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("Execute with an input file. \n");
            return 0;
        }
        struct AdjMatrix *adj_matrix = CreateAdjMatrix(fp);
        InitializeMatrix(adj_matrix, fp);
        struct PQueue *PQ = NULL;
        struct Node *idxArray = NULL;
        int start = 0;
        int end = 0;
        char restart = 'Y';
        while (restart == 'Y') {
            printf("Start : ");
            scanf("%d", &start);
            printf("End : ");
            scanf("%d", &end);
            PQ = CreatePQ(adj_matrix);
            idxArray = CreateIdxArray(PQ);

            RunDijkstra(adj_matrix, PQ, idxArray, start, end);   
            printf("\nrestart? (Y/N) :");
            scanf("%*c%c", &restart);
        }
        DisposeAdjMatrix(adj_matrix);
        DisposePQueue(PQ);
    }
}
