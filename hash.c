#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ListNode
{
    int element;
    struct ListNode *next;
};
struct Hashtable
{
    int tableSize;
    struct ListNode **theLists;
};

void CreateHashtable(struct Hashtable **H, int size){
    (*H)->theLists = (struct ListNode **)(malloc(sizeof(struct ListNode *)*size));
    (*H)->tableSize = size;
    for(int i=0;i<size;i++){
        (*H)->theLists[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
        ((*H)->theLists[i])->next = NULL;
    }
}

int Hash(int key, int tablesize){
    double A = 0.30000;
    return (int)(floor(tablesize * ((key*A) - floor(key*A))));
}

struct ListNode *Find(struct Hashtable **H, int value){
    struct ListNode *position = NULL;
    struct ListNode *list = NULL;

    list = (*H)->theLists[Hash(value, (*H)->tableSize)];
    position = list->next;
    while(position != NULL && position->element != value){
        position = position->next;
    }

    return position;
}

void Insert(struct Hashtable **H, int value){
    struct ListNode *pos = NULL;
    struct ListNode *newCell = NULL;
    struct ListNode *list = NULL;
    int hashed = 0;

    pos = Find(H, value);
    if(pos == NULL){
        newCell = (struct ListNode *)(malloc(sizeof(struct ListNode)));
        hashed = Hash(value, (*H)->tableSize);
        list = (*H)->theLists[hashed];
        newCell->next = list->next;
        newCell->element = value;
        list->next = newCell;
    }
    printf("inserted : %d in node%d", value, hashed);
}
void Delete(struct Hashtable *H, int value){

}

//값이 NULL 이면 NULL 로 출력해주는 구문 필요
void Print(struct Hashtable *H){
    struct ListNode *pos;

}
int main(int argc, const char *argv[])
{
    struct Hashtable *Htable;
    CreateHashtable(&Htable, 8);
    Insert(&Htable, 3);
    Insert(&Htable, 5);
    Insert(&Htable, 8);
    return 0;
}
