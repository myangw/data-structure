#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 128
#define MAX_ARGUMENT 2
//Binary max heap 구현: Complete, Partially Ordered.

//heap 구조 정의
struct HeapStruct{
    int capacity;
    int size;
    int *array;
};
//input commandline받는 구조체 
struct commandline_t
{
    char buf[MAX_BUF];
    int arguments[MAX_ARGUMENT];
};

/////insert, delete할 때 필요한 함수
int IsFull(struct HeapStruct **H){
    if((*H)->size >= (*H)->capacity){
        return 1;
    }else{
        return 0;
    }
}
///부모노드와 두개의 자식노드 비교해서 가장큰거 반환
int MaxAmongThree(struct HeapStruct **H, int parent){
    int max;
    if((*H)->array[parent*2] > (*H)->array[parent*2+1]){
        max = parent*2;
    } else{
        max = parent*2+1;
    }
    if((*H)->array[parent] > (*H)->array[max]){
        max = parent;
    } 
    return max; 
}
void Replace(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


//Insertion
void Insert(struct HeapStruct **H, int value){
    int i;
    if(IsFull(H)){
        printf("Insert: The Heap is full!\n");
        return;
    }else{
        ((*H)->size)++;
        //if the child is bigger, switch it with its parent
        for(i=((*H)->size); (*H)->array[i/2] < value && i>0; i/=2){
            (*H)->array[i] = (*H)->array[i/2];
        }
        (*H)->array[i] = value;
    } 
}
//Deletion
void DeleteMax(struct HeapStruct **H){
    if((*H)->size == 0){
        printf("Delete: The MaxHeap is empty!\n");
    }else{
        (*H)->array[1] = (*H)->array[(*H)->size];
        (*H)->size -= 1;
        for(int i=1;i<(*H)->size;i*=2){
            int maxIndex = MaxAmongThree(H, i);
            if((*H)->array[i] != (*H)->array[maxIndex]){
                Replace(&((*H)->array[i]), &((*H)->array[maxIndex]));      
            }else{
                return;
            }
         }    
    }
}

//CreateAHeap:heap구조생성,초기값insert까지
void CreateHeap(struct HeapStruct **H, int heapsize){
    *H = (struct HeapStruct *)malloc(sizeof(struct HeapStruct));
    (*H)->capacity = heapsize; 
    (*H)->array = (int *)malloc(sizeof(int) * heapsize);
    (*H)->size = 0;
    (*H)->array[0] = 9999999;
}
void PrintHeap(struct HeapStruct **H){
    if((*H)->size == 0){
        printf("Print: The MaxHeap is empty!\n");
    } else {
        for(int i=1;i<(*H)->size+1;i++){
            printf("%d \t", (*H)->array[i]);
        }
        printf("\n");
    }
}
//commandline-> function으로
void ParseCommandline(struct commandline_t *commandline, struct HeapStruct **maxHeap){
    char command = commandline->buf[0];
    int num;
    switch(command){
        case 'n':
            sscanf(commandline->buf, "%*c %d", &num);
            CreateHeap(maxHeap, num);
            break;
        case 'i':
            sscanf(commandline->buf, "%*c %d", &num);
            Insert(maxHeap, num); break;
        case 'd':
            DeleteMax(maxHeap); break;
        case 'p': 
            PrintHeap(maxHeap); break;
    }
}
int main(int argc, const char *argv[])
{
    if(argc == 2){
        FILE *fp = fopen(argv[1], "r");
        if(fp) {
           struct commandline_t commandline;
           while(fgets(commandline.buf, sizeof(commandline.buf),fp)){
                struct HeapStruct *maxHeap;
                ParseCommandline(&commandline, &maxHeap);
           }
        } else {
            printf("file open error \n");
        }
    } else {
        printf("Cannot find the input file...\n");
    }
    return 0;
}
