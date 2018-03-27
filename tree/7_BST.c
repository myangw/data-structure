#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 128
#define MAX_ARGUMENT 3

struct Tree
{
	int element;
	struct Tree *left;
	struct Tree *right;
};

//BST functions

struct Tree *InsertNode(int key, struct Tree *tree)
{
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
    }
}

struct Tree *DeleteNode(int key, struct Tree *tree){

}

struct Tree *FindNode(int key, struct Tree *tree){
    if(tree == NULL)
        return NULL;
    if(key < (tree->element)){
        return FindNode(key, (tree->left));
    }else if(key > (tree->element)){
        return FindNode(key, (tree->right));
    }else{
        return tree;
    }
}

void PrintInorder(struct Tree *tree){
    printf("%d \t", tree->element);
}
void PrintPreorder(struct Tree *tree){
    printf("%d \t", tree->element);
    while(tree->left !=NULL){
        PrintPreorder(tree->left);
    }
    if(tree->right != NULL){
        printf("%d \t", (tree->right)->element);
    }
}
void PrintPostorder(struct Tree *tree){

}

//commandline --> Function
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
            if(letter=='i'){
                PrintInorder(*tree);
                printf("inorder\n");
			}else if(letter=='r'){
                PrintPreorder(*tree);
                printf("preorder\n");
			}else{
                PrintPostorder(*tree);
                printf("postorder\n");
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
                //tree = (struct Tree *)malloc(sizeof(struct Tree));
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
