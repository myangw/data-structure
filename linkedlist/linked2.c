#include <stdio.h>
#include <stdlib.h>

//Define structure
struct NODE { 
    int element;
    struct NODE *next;
};

//Create a node
struct NODE *CreateNode(int element){
    struct NODE *pos = malloc(sizeof(struct NODE));
    pos->element = element;
    pos->next = NULL;

    return pos; 
}

//Make all elements in the list empty 
struct NODE *MakeEmpty(struct NODE *list)
{
    struct NODE *pos = list->next;
    while(pos->next == NULL){
        pos->element = 0;
        pos = pos->next;
    }
}

int IsEmpty(struct NODE *list){
   return list->next == NULL;
}

int IsLast(struct NODE *pos){
    return pos->next == NULL;
}

//Find the element in the list
struct NODE *Find(int element, struct NODE *list){
    struct NODE *pos = list;
    
    while(pos != NULL){
        if(element == pos->element){
            break;
        }
        pos = pos->next;
    }    
    return pos;
}

//Insert
void Insert(int element, struct NODE *list, char prev){
    int prevNode;
    element -=48;
    if(prev == '-'){
        prevNode = -1;
    }else{
        prevNode = prev - 48;
    }
    struct NODE *pos = Find(prevNode, list);
    if(pos == NULL){
        printf("Insertion(%d) failed: element %d is not in the list\n",element,prevNode);
    }else{
    struct NODE *new = CreateNode(element);
    new->next = pos->next;
    pos->next = new;
    }   
}

//Delete
void Delete(int element, struct NODE *list) {
    element -=48;
    struct NODE *del = Find(element, list);
    if(del == NULL){
        printf("Deletion failed: element %d is not in the list\n", element);
    }else{
        struct NODE *pos = list;
        while(pos->next != del){
            pos = pos->next;
        }
        pos->next = del->next;
        free(del);
    }   
}

//Find the previous node
void FindPrevious(int element, struct NODE *list){
    element -=48;
    struct NODE *next = Find(element, list);
    if(next != NULL){
        struct NODE *pos = list;
        while(pos->next != next){
            pos = pos->next;
        }
        int prevNode = pos->element;
        if(prevNode!=-1){
            printf("Key of previous node of %d is %d\n",element,prevNode);
        }else{
            printf("Key of previous node of %d is header.\n",element);
        }
    }else{
        printf("Could not find %d in the list\n",element);
    }   
}

//Show the entire list
void PrintAll(struct NODE *list){
    struct NODE *pos = list;
    pos = pos->next;
    while(pos != NULL){
        printf("key: %d \t",pos->element);
        pos = pos->next;
    }
    printf("\n");
}

//Free memory
void FreeAll(struct NODE *list){
    struct NODE *pos = list;
    struct NODE *freeNode;
    while(pos != NULL){
        freeNode = pos;
        pos = pos->next;
        free(freeNode);
    }
}
void ReadFile(FILE* ifs, struct NODE *list)
{
   char str_read[8];
   char func;
   if(ifs == NULL){
        fprintf(stderr,"cannot open the file\n");
        exit(EXIT_FAILURE);
   }
        while(!feof(ifs)){
            fgets(str_read, 8, ifs);
            func = str_read[0];
            switch(func){
                case 'i': Insert(str_read[2],list,str_read[4]); break;
                case 'd': Delete(str_read[2],list); break;
                case 'f': FindPrevious(str_read[2],list); break;
                case 'p': PrintAll(list); break;
            }
        }
        fclose(ifs);

}
int main(int argc, const char *argv[])
{
    //Create a list.
    struct NODE *list;
    list = CreateNode(-1);

    //Read input from txt file.
    FILE* ifs;
    ifs = fopen(argv[1], "rt");
    if(argc ==2){
        ReadFile(ifs, list);       
    }else{
        printf("wrong execution: put an argument file");
    }
    FreeAll(list);
    return 0;
}
