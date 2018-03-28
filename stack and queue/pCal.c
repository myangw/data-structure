#include <stdio.h>
#include <stdlib.h>

/* stack */
struct stack_t{
    char *key;
    int top;
    int capacity;
};
//Stack Function
struct stack_t *CreateStack(int capacity){
    struct stack_t *new = (struct stack_t *)malloc(sizeof(struct stack_t));

    new->capacity = capacity;
    new->top = -1;
    new->key = (char *)malloc(sizeof(char)* new->capacity);

    return new;
}

int IsFull(struct stack_t *stack){
    int top = stack->top;
    return ++top == stack->capacity;
}

int IsEmpty(struct stack_t *stack){
    return stack->top == -1;
}
void Push(struct stack_t *stack, int element){
    if(!IsFull(stack)){
        stack->key[++stack->top] = element;
    }
}
int Pop(struct stack_t *stack){
    if(!IsEmpty(stack)){
        return stack->key[stack->top--];
    }
}
int Top(struct stack_t *stack){
    if(!IsEmpty(stack)){
        return stack->key[stack->top];
    }
}
void PrintStack(struct stack_t *stack){
    if(!IsEmpty(stack)){
        for(int i=0;i<stack->top;i++){
            printf("%d", stack->key[i]);
        }
    }
}
void FreeStack(struct stack_t *stack){
    free(stack->key);
    free(stack);
}

int CalTwo(struct stack_t *stack, char *letter, int *result){
    int operand1 = Pop(stack);
    int operand2 = Pop(stack);

   // if(operand2 > operand1){
      //  int tmp = operand2;
       // operand2 = operand1;
       // operand1 = tmp;
    //}

    switch(*letter){
        case '+': return operand2 + operand1; break;
        case '-': return operand2 - operand1; break;
        case '*': return operand2 * operand1; break;
        case '/': return operand2 / operand1; break;
        case '%': return operand2 % operand1; break;
    }
}
int CharToInt(char *letter){
    return *letter -48;
}
void Calculate(struct stack_t *stack, char *letter){
    int result = 0;
    if(*letter>48 && *letter<58){
        Push(stack, CharToInt(letter));
    }else{
        result = CalTwo(stack,letter,&result);
        Push(stack, result);
    }
}
/* Conversion from infix to postfix */
int main(int argc, const char *argv[])
{
    if(argc ==2){
        FILE *fp = fopen(argv[1], "r");
        char buf;
        struct stack_t *stack = CreateStack(10);
        printf("Converted postfix form: ");
        if(fp){
            while(1){
                buf = fgetc(fp);
                if(buf=='#'){
                    break;
                }
                printf("%c",buf);
                Calculate(stack, &buf);
            }
        printf("\nevaluation result:%d\n",Top(stack));
        FreeStack(stack);
       }else{
            printf("Cannot open file\n");
        }
    }else{
       printf("Wrong argument\n");
    }
    return 0;
}
