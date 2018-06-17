#include <stdio.h>
#include <stdlib.h>

struct stack_t{
    char *key;
    int top;
    int capacity;
};

/* stack functions */

struct stack_t *CreateStack(int capacity){
    struct stack_t *new = (struct stack_t *)malloc(sizeof(struct stack_t));

    new->capacity = capacity;
    new->top = -1;
    new->key = (char *)malloc(sizeof(char) * new->capacity);

    return new;
}

int IsFull(struct stack_t *stack){
    int top = stack->top;
    return ++top == stack->capacity;
}

int IsEmpty(struct stack_t *stack){
    return stack->top == -1;
}

void Push(struct stack_t *stack, char element){
    if(!IsFull(stack)){
        stack->key[++stack->top] = element;
    }
}

char Pop(struct stack_t *stack){
    if(!IsEmpty(stack)){
        return stack->key[stack->top--];
    }
}

char Top(struct stack_t *stack){
    if(!IsEmpty(stack)){
        return stack->key[stack->top];
    }
}

void PrintStack(struct stack_t *stack){
    if(!IsEmpty(stack)){
        for(int i = 0; i < stack->top; i++){
            printf("%d", stack->key[i]);
        }
    }
}

void FreeStack(struct stack_t *stack){
    free(stack->key);
    free(stack);
}

/* Functions for conversion to postfix */

void Printout(char *converted){
    printf("\nconverted postfix form:");
    for (int i = 0; i < 64; i++) {
        printf("%c",converted[i]);
    }
    printf("\n");
}

int CharToInt(char *letter){
    return *letter - 48;
} 
int Priority(char *operator){
    switch(*operator){
        case '+': return 1; break;
        case '-': return 1; break;
        case '*': return 2; break;
        case '/': return 2; break;
        case '%': return 2; break;
        case '(': return 3; break;
        case ')': return 3; break;
        default: return 0; break;
    }
}

void ConvertToPostfix(char *letter, char *output, int *count, struct stack_t *stack){
    //operands ==> output array
    if(*letter > 48 && *letter < 58){
        output[*count] = *letter;
    }else{
        //operators ==> stack
        char top = Top(stack);
        if(IsEmpty(stack) || Priority(letter) > Priority(&top) || top == '('){
            Push(stack, *letter);
        }else{
            while(!IsEmpty(stack) && Priority(letter) <= Priority(&top)){
                if(Top(stack) == '(' || Top(stack) == ')'){
                    Pop(stack);
                }else{
                    output[*count] = Pop(stack);
                    *count = *count + 1;
                }
            }  
            Push(stack, *letter);
        } 
    }
}

int main(int argc, const char *argv[])
{
    if(argc == 2){
        FILE *fp = fopen(argv[1], "r");
        char buf;
        char *output = (char *)malloc(sizeof(char) * 64);
        int count = 0;
        struct stack_t *stack = CreateStack(10);
        printf("Original infix form:");
        if(fp){
            while(buf != '#'){
                buf = fgetc(fp);
                printf("%c",buf);
                ConvertToPostfix(&buf,output,&count,stack);
                count++;
            }
            Printout(output);
            FreeStack(stack);
            free(output);
        }else{
            printf("Cannot open file\n");
        }
    }else{
       printf("Wrong argument\n");
    }
    return 0;
}
