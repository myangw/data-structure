#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Graph{
    int **adj_matrix;
    int *indegree;
    int size;
};

struct Queue{
    int *array;
    int front;
    int rear;
    int size;
    int capacity;
};

struct Graph *CreateGraph(char *vertices, char *edges){
    int size = vertices[strlen(vertices) - 2] - 48;
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

    graph->adj_matrix = (int **)malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++){
        graph->adj_matrix[i] = (int *)malloc(sizeof(int) * size);
    }
    
    graph->indegree = (int *)malloc(sizeof(int) * size);
    graph->size = size;
    // input vertices를 adjacent matrix로 나타내기.  
    int v1,v2;
    char *ptr = strtok(edges, " ");
    while(ptr != NULL){
        v1 = ptr[0] - 48;
        v2 = ptr[2] - 48;
        graph->adj_matrix[v1-1][v2-1] = 1;
        ptr = strtok(NULL, " ");
    }
    //indegree 계산하여 array에 넣기
    int indegree = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            indegree += graph->adj_matrix[j][i];
        }
        graph->indegree[i] = indegree;
        indegree = 0;
    }
    return graph;
}

void CreateQueue(struct Queue **Q, int vertexNum){
    *Q = (struct Queue *)malloc(sizeof(struct Queue));
    (*Q)->array = (int *)malloc(sizeof(int) * vertexNum);
    (*Q)->front = 0; 
    (*Q)->rear = 0;
    (*Q)->size = 0;
    (*Q)->capacity = vertexNum;
}

int IsEmpty(struct Queue **Q){
    if((*Q)->size == 0){
        return 1;
    }else{
        return 0;
    }
}
int IsFull(struct Queue **Q){
    if((*Q)->size == (*Q)->capacity){
        return 1;
    }else{
        return 0;
    }
}

int Succ(int value, struct Queue **Q){
    if(++value == (*Q)->capacity)
        value = 0;
    return value;
}

int Dequeue(struct Queue **Q){
    int value = 0;
    if(!IsEmpty(Q)){
       (*Q)->size--;
       value = (*Q)->array[(*Q)->front];
       (*Q)->front = Succ(((*Q)->front)++, Q);
    }
    return value;
}

void Enqueue(struct Queue **Q, int new){
    if(!IsFull(Q)){
        (*Q)->size++;
        (*Q)->array[(*Q)->rear] = new;
        (*Q)->rear = Succ(((*Q)->rear)++, Q);
    }
}

void TopSort(struct Queue **queue, struct Graph **graph){
    int count = 0;
    int *result;
    result = (int *)malloc(sizeof(int) * (*graph)->size);
    for(int i = 0; i < (*graph)->size; i++){
        if((*graph)->indegree[i] == 0)
            Enqueue(queue, i+1);
    }
    while(!IsEmpty(queue)){
        int vertex = Dequeue(queue);
        result[count] = vertex;
        count++;
        for(int i = 0; i < (*graph)->size; i++){
            if((*graph)->adj_matrix[vertex-1][i] == 1){
                (*graph)->adj_matrix[vertex-1][i] = 0;
                (*graph)->indegree[i] -= 1;
                if((*graph)->indegree[i] == 0)
                    Enqueue(queue, i+1);
            }
        }
    }   
    for(int i = 0; i < (*graph)->size; i++){
        printf("%d  ",result[i]);
    }
    printf("\n");
}

void DisposeQueue(struct Queue **Q){
    free((*Q)->array);
    free(*Q);
}

void DisposeGraph(struct Graph **G){
    for(int i = 0; i < (*G)->size; i++){
        free((*G)->adj_matrix[i]);
    }
    free((*G)->indegree);
    free(*G);
}

int main(int argc, const char *argv[]){
    if(argc == 2){
        FILE *fp = fopen(argv[1], "r");
        if(fp){
            char buf[128];
            char *ptr;
            char vertices[128];
            struct Graph *graph;
            struct Queue *queue;
            int inputLine = 1;
            while(fgets(buf,sizeof(buf),fp)){
                if(inputLine == 1){
                    strcpy(vertices,buf);
                    inputLine++;
                }else{
                    char *edges = buf; 
                    graph = CreateGraph(vertices, edges);
                    CreateQueue(&queue, graph->size);
                    TopSort(&queue, &graph); 
                }
            }
            DisposeQueue(&queue);
            DisposeGraph(&graph);
        }else{
            printf("File open error! \n");
        }
    }else{
        printf("Execute with an input file!\n");
    } 
    return 0;
}
