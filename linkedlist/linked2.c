#include <stdio.h>
#include <stdlib.h>

struct NODE{ 
    int element;
    struct NODE *next;
};

struct NODE *CreateNode(int element){
    struct NODE *pos = malloc(sizeof(struct NODE));
    pos->element = element;
    pos->next = NULL;

    return pos; 
}

struct NODE *MakeEmpty(struct NODE *list){
    struct NODE *pos = list->next;
    struct NODE *tmp;
    while(pos->next == NULL){
        tmp = pos;
        pos = pos->next;
        free(tmp);
    }
}

int IsEmpty(struct NODE *list){
   return list->next == NULL;
}

int IsLast(struct NODE *pos){
    return pos->next == NULL;
}

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

void Insert(int element, struct NODE *list, int prev){
    struct NODE *pos = Find(prev, list);
    if(pos == NULL){
        printf("Insertion(%d) failed: element %d is not in the list\n",element,prev);
    }else{
        struct NODE *new = CreateNode(element);
        new->next = pos->next;
        pos->next = new;
    }   
}

void Delete(int element, struct NODE *list){
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

void FindPrevious(int element, struct NODE *list){
    struct NODE *pos = list;
    struct NODE *prev;
    while(pos->element != element && pos->next != NULL){
        prev = pos;
        pos = pos->next;
    }
    if(pos->element == element){
        int prevElement = prev->element;
        if(prevElement != -1){
            printf("Key of previous node of %d is %d.\n",pos->element,prevElement);
        }else{
            printf("Key of previous node of %d is header.\n",element);
        }
    }else{
        printf("Could not find %d in the list.\n",element);
    }
}

void PrintAll(struct NODE *list){
    struct NODE *pos = list->next;
    while(pos != NULL){
        printf("key: %d \t",pos->element);
        pos = pos->next;
    }
    printf("\n");
}

void FreeAll(struct NODE *list){
    struct NODE *pos = list;
    struct NODE *freeNode;
    while(pos != NULL){
        freeNode = pos;
        pos = pos->next;
        free(freeNode);
    }
}
void ReadFile(FILE* ifs, struct NODE *list){
   char str_read[8];
   char func;
   if(ifs == NULL){
        fprintf(stderr,"cannot open the file\n");
        exit(EXIT_FAILURE);
   }
   while(!feof(ifs)){
        fgets(str_read, 8, ifs);
        func = str_read[0];
        int element;
        int prev;
        switch(func){
            case 'i': 
                sscanf(str_read, "%*c %d %d", &element, &prev);
                Insert(element,list,prev); 
                break;
            case 'd': 
                sscanf(str_read, "%*c %d", &element);
                Delete(element,list); 
                break;
            case 'f': 
                sscanf(str_read, "%*c %d", &element);
                FindPrevious(element,list); 
                break;
            case 'p': 
                PrintAll(list); 
                break;
        }
    }
    fclose(ifs);

}
int main(int argc, const char *argv[]){
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
