#include <stdio.h>
#include <stdlib.h>

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

struct AvlNode
{
    int element;
    AvlTree left;
    AvlTree right;
    int height;
};

int getHeight(Position node){
    if(node == NULL)
        return -1;
    else
        return node->height;
}

int Max(int a, int b){
    return (a >= b)? a : b;
}

// 왼쪽이 무거울 때 오른쪽으로 rotate하는 함수
Position SingleRotateWithLeft(Position k2){
    Position k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = Max(getHeight(k1->left), k2->height) + 1;

    return k1;
}

// 오른쪽이 무거울 때 왼쪽으로 rotate하는 함수
Position SingleRotateWithRight(Position k2){
    Position k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = Max(getHeight(k2->right), getHeight(k2->left)) + 1;
    k1->height = Max(getHeight(k1->right), k2->height) + 1;

    return k1;
}

// LR: 왼쪽노드의 오른쪽이 무거울 때
Position DoubleRotateWithLeft(Position k3){
    k3->left = SingleRotateWithRight(k3->left);
    return SingleRotateWithLeft(k3);
}

// RL: 오른쪽노드의 왼쪽이 무거울 때
Position DoubleRotateWithRight(Position k3){
    k3->right = SingleRotateWithLeft(k3->right);
    return SingleRotateWithRight(k3);
}

AvlTree Insert(int x, AvlTree T){
    if(T == NULL){
        T = malloc(sizeof(struct AvlNode));
        T->element = x;
        T->height = 0;
        T->left = NULL;
        T->right = NULL;
    }else if (x < T->element){
        T->left = Insert(x, T->left);
        if(getHeight(T->left) - getHeight(T->right) == 2){
            if(x < T->left->element) //LL
                T = SingleRotateWithLeft(T);
            else  //LR
                T = DoubleRotateWithLeft(T);
        }
    }else if (x > T->element){
        T->right = Insert(x, T->right);
        if(getHeight(T->right) - getHeight(T->left) == 2){
            if(x > T->right->element) //RR
                T = SingleRotateWithRight(T); 
            else //RL
                T = DoubleRotateWithRight(T);
        }
    }
    //height adjustment when inserted w/o rotation
    T->height = Max(getHeight(T->left), getHeight(T->right)) + 1;

    return T;
}
void PrintInorder(AvlTree T){ 
    if(T->left != NULL){
        PrintInorder(T->left);
    }
    printf("%d ", T->element);
    if(T->right != NULL){
        PrintInorder(T->right);
    }
}
int main(int argc, const char *argv[])
{
    if(argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if(fp){
            AvlTree tree = NULL;
            int input;
            while(fscanf(fp, "%d", &input) > 0){
                tree = Insert(input, tree);
                printf("height: %d\n", tree->height);
                PrintInorder(tree);
                printf("\n");
            }        
        }
        fclose(fp);
    }    
    return 0;
}

