#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 128
#define MAX_ARGUMENT 2

struct CQueue {
    int *array;
    int front;
    int rear;
    int size;
    int capacity;
};

struct commandline_t{
    char buf[MAX_BUF];
    int arguments[MAX_ARGUMENT];
};

void CreateCircularQ(struct CQueue **Q, int max){
    *Q = (struct CQueue *)malloc(sizeof(struct CQueue));
    (*Q)->capacity = max;
    (*Q)->array = (int *)malloc(sizeof(int));
    (*Q)->front = 0;
    (*Q)->rear = 0;
    (*Q)->size = 0;
} 
int IsEmpty(struct CQueue **Q){
    if((*Q)->size == 0){
        return 1;
    }else{
        return 0;
    }
}
int IsFull(struct CQueue **Q){
    if((*Q)->size == (*Q)->capacity){
        return 1;
    }else{
        return 0;
    }
}
int Succ(int value, struct CQueue **Q){
    if(++value == (*Q)->capacity)
        value = 0;
    return value;
}
void PrintAll(struct CQueue **Q){
    int front = (*Q)->front;
    int rear = (*Q)->rear;
    if(front < rear){
        for(int i=front;i<rear;i++){
            printf("%d\t", (*Q)->array[i]);
        }
    }else if(front > rear || IsFull(Q)){
        for(int i=front;i<(*Q)->capacity;i++){
            printf("%d\t", (*Q)->array[i]);
        }
        for(int i=0;i<rear;i++){
            printf("%d\t", (*Q)->array[i]);
        }
    }
    printf("f: %d, r: %d\n", front, rear);
}

void Dequeue(struct CQueue **Q){
    if(IsEmpty(Q)){
       printf("ERROR: The queue is empty.\n");
    }else{
       (*Q)->size--;
       (*Q)->front = Succ(((*Q)->front)++, Q);
       printf("Dequeued:\t");
       PrintAll(Q);
    }
}
void Enqueue(struct CQueue **Q, int new){
    if(IsFull(Q)){
        printf("ERROR:The queue is Full.\n");
    }else{
        (*Q)->size++;
        (*Q)->array[(*Q)->rear] = new;
        (*Q)->rear = Succ(((*Q)->rear)++, Q);
    }
    printf("Enqueued:\t");
    PrintAll(Q);
}
void PrintFront(struct CQueue **Q){
    printf("Front: %d\n", (*Q)->array[(*Q)->front]);
}

void PrintRear(struct CQueue **Q){
    printf("Rear: %d\n", (*Q)->array[(*Q)->rear]);
}
void DeleteQueue(struct CQueue **Q){
    free((*Q)->array);
    free(*Q);
}

void MakeEmpty(struct CQueue **Q){
    (*Q)->size = 0;
    (*Q)->front = 0;
    (*Q)->rear = 0;
}

void ParseCommandLine(struct commandline_t *commandline, struct CQueue **Q){
    char command = commandline->buf[0];
    int num;
    switch(command){
        case 'e': 
            sscanf(commandline->buf, "%*c %d", &num);
            Enqueue(Q, num); 
            break;
        case 'd': Dequeue(Q); break;
        case 'f': PrintFront(Q); break;
        case 'r': PrintRear(Q); break;
        case 'n': 
            sscanf(commandline->buf, "%*c %d", &num);
            CreateCircularQ(Q, num); 
            break;
    }
}

int main(int argc, const char *argv[])
{
    if(argc ==2){
        FILE *fp = fopen(argv[1], "r");
        if (fp) {
            struct commandline_t commandline;
            while(fgets(commandline.buf, sizeof(commandline.buf),fp)){
                struct CQueue *queue;
                ParseCommandLine(&commandline, &queue);
            }
        }else{
            printf("file open error \n");
        }
    }else{
        printf("input text file plz\n");
    } 

    return 0;
}
