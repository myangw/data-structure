#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 128
#define MAX_ARGUMENT 2
#define MAX_ENROLLMENT 30

enum command_t{
    UNKNOWN,
    INSERT,
    DELETE,
    PRINT,
};

struct commandline_t{
    char buf[MAX_BUF];
    enum command_t command;
    int arguments[MAX_ARGUMENT];
};

struct student_t{ 
    char studentID[12];
    char studentName[20];
};

struct node_t{
    struct student_t student;
    struct node_t *next;
};

struct node_t *CreateNode(struct student_t *student){
    struct node_t *pos = (struct node_t*)malloc(sizeof(struct node_t));
    memcpy((pos->student).studentID, student->studentID, sizeof(student->studentID));
    memcpy((pos->student).studentName, student->studentName, sizeof(student->studentName));
    pos->next = NULL;

    return pos;
}

void *CreateList(struct node_t **listPtr){
   struct student_t header = {
       .studentID = "-1",
       .studentName = "header",
   };
   *listPtr = CreateNode(&header);
}

struct node_t *Find(struct student_t *student, struct node_t *list){
    struct node_t *pos = list;
    
    while(pos != NULL){
        if(strcmp(student->studentID, (pos->student).studentID) ==0){
            break;
        }
        pos = pos->next;
    }

    return pos;
}

void PrintList(struct node_t *list){
    struct node_t *pos = list;
    pos = pos->next;
    while(pos != NULL){
        printf("%s %s  ",(pos->student).studentID, (pos->student).studentName);
        pos = pos->next;
    }
    printf("\n");
}

void Insert(struct student_t *student, struct node_t *list, int *enroll_num){
    if(Find(student, list) == NULL & *enroll_num < MAX_ENROLLMENT){
        struct node_t *pos = list;
        struct node_t *prev;
        struct node_t *new = CreateNode(student);
        while(pos->next != NULL & atoi((pos->student).studentID) < atoi(student->studentID)){
            prev = pos;
            pos = pos->next;
        }
        if(atoi(pos->student.studentID) == -1){
            new->next = pos->next;
            pos->next = new;
        }else{
            new->next = prev->next;
            prev->next = new;
        }

        PrintList(list);
        *enroll_num += 1;
    }else{
        printf("There already is an element with key %s. Insertion failed.\n",student->studentID);    
    }  
}

void Delete(struct student_t *student, struct node_t *list, int *enroll_num){
    struct node_t *del = Find(student,list);
    if(del == NULL){
        printf("Deletion failed: %s is not in the list\n",student->studentID);
    }else{
        struct node_t *pos = list;
        while(pos->next != del){
            pos = pos->next;
        }
        pos->next = del->next;
        free(del);
        *enroll_num -= 1;
    }

}

void FreeAll(struct node_t *list){
    struct node_t *pos = list;
    struct node_t *freeNode;
    while(pos != NULL){
        freeNode = pos;
        pos = pos->next;
        free(freeNode);
    }
}

void *ParseCommandLine(struct commandline_t *commandline, struct student_t **stPtr){
    char command = commandline->buf[0];
    *stPtr = malloc(sizeof(struct student_t));

    switch(command){
        case 'i':
            commandline->command = INSERT;
            sscanf(commandline->buf, "%*c %s %[^\n]s", ((*stPtr)->studentID), ((*stPtr)->studentName));
            break;
        case 'd':
            commandline->command = DELETE;
            sscanf(commandline->buf, "%*c %s", ((*stPtr)->studentID));
            break;
        case 'p':
            commandline->command = PRINT;
            break;
    }
}

int main(int argc, const char *argv[]){
    if(argc ==2){
        FILE *fp = fopen(argv[1], "r");
        if(fp){
            struct commandline_t commandline;
            struct student_t *student;
            struct node_t *list;
            CreateList(&list);
            int enroll_num = 0;
            while(fgets(commandline.buf, sizeof(commandline.buf), fp)){
                ParseCommandLine(&commandline, &student);
                switch(commandline.command){
                    case INSERT:
                        Insert(student,list, &enroll_num); break;
                    case DELETE:
                        Delete(student,list, &enroll_num); break;
                    case PRINT:
                        PrintList(list); break;
                    case UNKNOWN:
                        printf("wrong command!");break;
                }
            }
            fclose(fp);
        }else{
            printf("file open error \n");
        }
    }else{
        printf("usage: {executable} {input text file_ex.lab3_input.txt}\n");
    }

    
    return 0;
}
