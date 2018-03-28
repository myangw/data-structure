#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 128
#define MAX_ARGUMENT 2

//define circular queue struct
struct CQueue {
    int *array;
    int front;
    int rear;
    int size;
    int capacity;
};

//Function needed for the queue
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
    printf("%d\t%d\t%d\t%d\t%d\t", (*Q)->array[0],(*Q)->array[1],
(*Q)->array[2],(*Q)->array[3],(*Q)->array[4]);
    printf("f: %d, r: %d\n", (*Q)->array[(*Q)->front], (*Q)->array[(*Q)->rear]);
}

void Dequeue(struct CQueue **Q){
    if(IsEmpty(Q)){
        printf("ERROR: The queue is empty.\n");
    }else{
       (*Q)->size--;
       (*Q)->array[(*Q)->front] = 0;
       (*Q)->front = Succ((*Q)->front, Q);
       printf("Dequeued:\t");
       PrintAll(Q);
    }
}
void Enqueue(struct CQueue **Q, int new){
    if(IsFull(Q)){
        printf("ERROR:The queue is Full.\n");
    }else{
        if(IsEmpty(Q)){
            (*Q)->size++;
            (*Q)->array[(*Q)->rear] = new;   
        }else{
            (*Q)->size++;
            (*Q)->rear = Succ((*Q)->rear, Q);
            (*Q)->array[(*Q)->rear] = new;
        }
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
    (*Q)->front = 1;
    (*Q)->rear = 0;
}
//Structure and Function for user input and print
struct commandline_t{
    char buf[MAX_BUF];
    int arguments[MAX_ARGUMENT];
};
void ParseCommandLine(struct commandline_t *commandline, struct CQueue **Q){
    char command = commandline->buf[0];
    //int num = commandline->buf[2] - 48;
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
