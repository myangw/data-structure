#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INF 2147483647;

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

int IsFull(struct PQueue **Q){
    if((*Q)->size >= (*Q)->capacity){
        return 1;
    }else{
        return 0;
    }
}

int MinInThree(struct PQueue **Q, int parent){
    int min;
    if((*Q)->queue[parent * 2].d > (*Q)->queue[parent * 2 + 1].d){
        min = parent * 2;
    }else{
        min = parent * 2 + 1;
    }
    if((*Q)->queue[parent].d > (*Q)->queue[min].d){
        min = parent;
    }
    return min;
}

void Replace(struct Node *a, struct Node *b){
    struct Node tmp = *a;
    *a = *b;
    *b = tmp;
}

void HeapifyUpward(struct PQueue **Q, struct Node *node){
    int i;
    for(i = ((*Q)->size); (*Q)->queue[i/2].d > node->d && i > 0; i /= 2){
        (*Q)->queue[i].d = (*Q)->queue[i/2].d;
        (*Q)->queue[i].pred = (*Q)->queue[i/2].pred;
        (*Q)->queue[i].vertexNo = (*Q)->queue[i/2].vertexNo;
    }
    (*Q)->queue[i].d = node->d;
    (*Q)->queue[i].pred = (*Q)->queue[i].pred;
    (*Q)->queue[i].vertexNo = (*Q)->queue[i].vertexNo;
}

void HeapifyDownward(struct PQueue **Q){
    for(int i = 1; i < (*Q)->size; i *= 2){
        int minIdx = MinInThree(Q, i);
        if((*Q)->queue[i].d != (*Q)->queue[minIdx].d){
            Replace(&((*Q)->queue[i]), &((*Q)->queue[minIdx]));
        }else{
            return;
        }
    }
}

//void Insert(struct PQueue **Q, int value){
//    if(IsFull(Q)){
//        printf("Insert: The Priority Queue is Full.\n");
//        return;
//    }else{
//        ((*Q)->size)++;
//        HeapifyUpward(Q, value);
//    }
//}
//
struct Node PopMin(struct PQueue **Q){
    if((*Q)->size == 0){
        printf("Delete fail: Empty priority Queue.\n");
    }else{
        struct Node minNode = (*Q)->queue[0];
        (*Q)->queue[1].d = (*Q)->queue[(*Q)->size].d;
        (*Q)->queue[1].pred = (*Q)->queue[(*Q)->size].pred;
        (*Q)->queue[1].vertexNo = (*Q)->queue[(*Q)->size].vertexNo;
        (*Q)->size -= 1;
        HeapifyDownward(Q);
        return minNode;
    }
}

void InitializePQueue(struct PQueue **Q, int capacity){
    *Q = (struct PQueue *)malloc(sizeof(struct PQueue));
    (*Q)->queue = (struct Node *)malloc(sizeof(struct Node) * capacity);
    for(int i = 1;i < capacity + 1; i++){
        (*Q)->queue[i].d = INF;
        (*Q)->queue[i].pred = NULL;
        (*Q)->queue[i].vertexNo = i+1;
    }
    
    (*Q)->capacity = capacity + 1;
    (*Q)->size = 0;
}

void PrintPQueue(struct PQueue **Q){
    if((*Q)->size == 0){
        printf("Empty.\n");
    }else{
        for(int i = 1; i < (*Q)->size + 1; i++){
            printf("%d \t", (*Q)->queue[i].d);
        }
        printf("\n");
    }
}

int **CreateAdjMatrix(int size, char *edges){
    int **adjMatrix = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++){
        adjMatrix[i] = (int *)malloc(sizeof(int) * size);
    }
    int v1,v2,d;
    char *tokenPtr = strtok(edges, " ");
    while(tokenPtr != NULL){
        sscanf(tokenPtr, "%d%*c%d%*c%d", &v1,&v2,&d);
        adjMatrix[v1-1][v2-1] = d;
        tokenPtr = strtok(NULL, " ");
    }

    for(int i = 0; i < size; i++){
        for(int j=0;j<size;j++){
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    return adjMatrix;
}

void Relaxation(struct PQueue **Q, int **adjMatrix, int graphSize, int vertexNo){
    for(int i = 0;i < graphSize; i++){
        if(adjMatrix[vertexNo - 1][i] != 0){
            if((*Q)->queue[vertexNo - 1].d + adjMatrix[vertexNo - 1][i] < (*Q)->queue[i].d){
                (*Q)->queue[i].d = (*Q)->queue[vertexNo - 1].d + adjMatrix[vertexNo - 1][i];
                (*Q)->queue[i].pred = &((*Q)->queue[vertexNo - 1]);
                HeapifyUpward(Q, &((*Q)->queue[i]));
            }
        }
    }
}


void DisposeAdjMatrix(int **adjMatrix, int size){
    for(int i = 0; i < size; i++){
        free(adjMatrix[i]);
    }
    free(adjMatrix);
}

int main(int argc, const char *argv[]){
    if(argc == 2){
        FILE *fp = fopen(argv[1], "r");
        if(fp){
            char buf[128];
            int **adjMatrix;
            int graphSize;
            struct PQueue *PQ;
            int inputLine = 1;
            while(fgets(buf, sizeof(buf), fp)){
                if(inputLine == 1){
                    graphSize = buf[strlen(buf) - 2] - 48;
                    printf("%d : size \n", graphSize);
                    inputLine++;
                }else{
                    char *edges = buf;
                    adjMatrix = CreateAdjMatrix(graphSize, edges);
                    InitializePQueue(&PQ, graphSize);
                    int start, visiting, end;
                    int count;
                    char restart = 'Y';
                    struct Node *visited = (struct Node *)malloc(sizeof(struct Node) * graphSize);
                    while(restart == 'Y'){
                        printf("Start : ");
                        scanf("%d", &start);
                        printf("End : ");
                        scanf("%d", &end);
                        //finding each vertex's shortest path.
                        visiting = start;
                        PQ->queue[visiting-1].d = 0;
                        while(1){
                            HeapifyUpward(&PQ, &(PQ->queue[visiting-1]));
                            visited[count] = PopMin(&PQ);
                            visiting = visited[count].vertexNo;
                            Relaxation(&PQ, adjMatrix, graphSize, visiting);
                            if(visiting == end){
                                struct Node *nextNode = &(visited[count]);
                                while(nextNode->vertexNo != start){
                                    printf("%d ", visited[count].vertexNo);
                                    nextNode = visited[count].pred;
                                }
                                break;
                            }
                            count++;
                        }
                        printf("\n"); 
                        printf("restart? (Y/N) :");
                        scanf("%*c%c", &restart);
                        fflush(stdin);
                    }
                    PrintPQueue(&PQ);
                }
            }
            DisposeAdjMatrix(adjMatrix, graphSize);
        }
    }else{
        printf("Execute with an input file. \n");
    }
    return 0;
}
