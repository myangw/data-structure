#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 128
#define MAX_ARGUMENT 3

struct Tree{
	int element;
	struct Tree *left;
	struct Tree *right;
};

struct Tree *InsertNode(int key, struct Tree *tree){
    if(tree == NULL){
        tree = (struct Tree *)malloc(sizeof(struct Tree));
        tree->element = key;
        tree->left = NULL;
        tree->right = NULL;
        return tree;
    }else if(key < (tree->element)){
        tree->left = InsertNode(key, tree->left);
    }else if(key > (tree->element)){
        tree->right = InsertNode(key, tree->right);
    }else{
        printf("element %d already exists!\n", key);
        return tree;
    }
}

struct Tree *FindMax(struct Tree *tree){
    if(tree != NULL){
        while(tree->right != NULL)
            tree = tree->right;
    }
    return tree;
}

struct Tree *FindNode(int key, struct Tree *tree){
    if(tree == NULL){
        printf("Element %d is not in the tree\n", key);
        return NULL;
    }
    if(key < (tree->element)){
        return FindNode(key, (tree->left));
    }else if(key > (tree->element)){
        return FindNode(key, (tree->right));
    }else{
        printf("Element %d is in the tree\n", key);
        return tree;
    }
}

struct Tree *DeleteNode(int key, struct Tree *tree){
    if (tree) {
        if (key < tree->element) {
            tree->left = DeleteNode(key, tree->left);
        } else if (key > tree->element) {
            tree->right = DeleteNode(key, tree->right);
        } else {
            /* 2 children */
            if (tree->left && tree->right) {
                struct Tree *replacement = FindMax(tree->left);
                tree->element = replacement->element;
                tree->left = DeleteNode(replacement->element, tree->left);
            /* 1 child (left) */
            } else if (tree->left) {
                struct Tree *left = tree->left;
                free(tree);
                return left;
            /* 1 child (right) */
            } else if (tree->right) {
                struct Tree *right = tree->right;
                free(tree);
                return right;
            /* leaf */
            } else {
                free(tree);
                return NULL;
            }
        }
    } else { // not matched
        printf("element %d not found!\n", key);
        return NULL;
    }
}

void PrintInorder(struct Tree *tree){
    if(tree->left != NULL){
        PrintInorder(tree->left);
    }
    printf("%d\t", tree->element);
    if(tree->right != NULL){
        PrintInorder(tree->right);
    }
}

void PrintPreorder(struct Tree *tree){
    printf("%d\t", tree->element);
    if(tree->left !=NULL){
        PrintPreorder(tree->left);
    }
    if(tree->right != NULL){
        PrintPreorder(tree->right);
    }
}

void PrintPostorder(struct Tree *tree){
    if(tree->left !=NULL){
        PrintPostorder(tree->left);
    }
    if(tree->right !=NULL){
        PrintPostorder(tree->right);
    }
    printf("%d\t", tree->element);
}

struct commandline_t 
{
	char buf[MAX_BUF];
	int arguments[MAX_ARGUMENT];
};

void ParseCommandLine(struct commandline_t *commandline, struct Tree **tree){
	char command = commandline->buf[0];
	int num;
	char letter;
	switch(command){
		case 'i':
			sscanf(commandline->buf, "%*c %d", &num);
			*tree = InsertNode(num, *tree);
            break;
		case 'd':
			sscanf(commandline->buf, "%*c %d", &num);
			DeleteNode(num, *tree);
            break;
		case 'f':
			sscanf(commandline->buf, "%*c %d", &num);
			*tree = FindNode(num, *tree);
            break;
		case 'p':
			sscanf(commandline->buf, "%*c%c", &letter);
            if(letter =='i'){
                PrintInorder(*tree);
                printf("\n");
			}else if(letter =='r'){
                PrintPreorder(*tree);
                printf("\n");
			}else{
                PrintPostorder(*tree);
                printf("\n");
			}
			break;
	}
}

int main(int argc, char const *argv[])
{
	if(argc ==2){
		FILE *fp = fopen(argv[1], "r");
		if(fp){
			struct commandline_t commandline;
            struct Tree *tree = NULL;
			while(fgets(commandline.buf, sizeof(commandline.buf), fp)){
				ParseCommandLine(&commandline, &tree);
			}
		}else{
			printf("file open error\n"); 
		}
	}else{
		printf("There was no input\n");
	}
	return 0;
}
