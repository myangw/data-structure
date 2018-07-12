#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double A;

struct ListNode
{
    int element;
    struct ListNode *next;
};

struct Hashtable
{
    int tableSize;
    struct ListNode **linkedLists;
};

void CreateHashtable(struct Hashtable **H, int size){
    (*H)->linkedLists = (struct ListNode **)(malloc(sizeof(struct ListNode *) * size));
    (*H)->tableSize = size;
    for(int i = 0;i < size;i++){
        (*H)->linkedLists[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
        ((*H)->linkedLists[i])->next = NULL;
    }
}

int Hash(int key, int tablesize){
    return (int)(floor(tablesize * ((key * A) - floor(key * A))));
}

struct ListNode *Find(struct Hashtable **H, int value){
    struct ListNode *position = NULL;
    struct ListNode *list = NULL;

    int hashed = Hash(value, (*H)->tableSize);
    list = (*H)->linkedLists[hashed];
    position = list->next;
    while(position != NULL && position->element != value){
        position = position->next;
    }

    return position;
}

void Insert(struct Hashtable **H, int value){
    struct ListNode *newCell = NULL;
    struct ListNode *list = NULL;
    int hashed = 0;

    if(Find(H, value) == NULL){
        newCell = (struct ListNode *)(malloc(sizeof(struct ListNode)));
        newCell->element = value;
        hashed = Hash(value, (*H)->tableSize);
        list = (*H)->linkedLists[hashed];
        newCell->next = list->next;
        list->next = newCell;
        printf("inserted : %d in node%d\n", value, hashed);
    }
}

void Delete(struct Hashtable **H, int value){
    struct ListNode *del;
    struct ListNode *pos;

    int hashed = Hash(value, (*H)->tableSize);
    del = Find(H, value);
    if(del != NULL){
        pos = (*H)->linkedLists[hashed];
        while(pos->next != del){
            pos = pos->next;
        }
        pos->next = del->next;
        free(del);
        printf("deleted: %d in node %d\n", value, hashed);
    }
}

void Print(struct Hashtable **H){
    struct ListNode *pos;
    struct ListNode *list;

    for(int i = 0;i < (*H)->tableSize;i++){
        list = (*H)->linkedLists[i];
        pos = list->next;
        printf("[%d]", i);
        if(pos == NULL){
            printf("null\n");
        }else{
            printf("%d  ", pos->element);
            while(pos->next != NULL){
                pos = pos->next;
                printf("%d  ", pos->element);
            }
            printf("\n");
        }
    }
}

void FreeAll(struct Hashtable **H){
    struct ListNode *pos;
    for(int i = 0;i < (*H)->tableSize;i++){
        free((*H)->linkedLists[i]);
    }
    free((*H)->linkedLists);
    free(*H);
}

void ParseToFunction(char *buf, struct Hashtable **H){
    char command = buf[0];
    int value = 0;
    switch(command){
        case 'i':
            sscanf(buf, "%*c %d", &value);
            Insert(H, value);
            break;
        case 'f':
            sscanf(buf, "%*c %d", &value);
            struct ListNode *found;
            found= Find(H, value);
            if(found != NULL){
                printf("found %d \n", found->element);
            }else{
                printf("NULL.\n");
            }
            break;
        case 'p':
            Print(H);
            break;
        case 'd':
            sscanf(buf, "%*c %d", &value);
            Delete(H, value);
            break;
        case 'q':
            FreeAll(H);
            break;
    }
}
int main(int argc, const char *argv[])
{
    if(argc == 2){
        FILE *fp = fopen(argv[1], "r");
        if(fp){
            char buf[8];
            int count = 0;
            struct Hashtable *Htable = (struct Hashtable *)(malloc(sizeof(struct Hashtable)));
            while(fgets(buf, sizeof(buf), fp)){
                if(count == 0){
                    int tableSize = buf[0] - 48;
                    CreateHashtable(&Htable, tableSize);
                    count++;
                }else if(count == 1){
                    sscanf(buf, "%lf", &A);
                    printf("A: %lf\n", A);
                    count++;
                }else{
                    ParseToFunction(buf, &Htable);
                }
            }
            
        }else{
            printf("file open error\n");
        }
    }else{
        printf("Run with input txt file.");
    }
   
    return 0;
}
