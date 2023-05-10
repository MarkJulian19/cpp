#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;


Node* getFreeNode(int value, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void insert(Node **head, int value) {
    Node *tmp = NULL;
    Node *ins = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }
     
    tmp = *head;
    while (tmp) {
        if ((value >= tmp->data)) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        } else if ((value < tmp->data)) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
    }
}


void printTree(Node *root, const char *dir, int level) {
    if (root) {
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }
}

void delltree(Node* root){
    if (root->left) delltree(root->left);
    if (root->right) delltree(root->right);
    free(root);
}


int getNodeByValue(Node *root, int value) {
    int i=1;
    while (root) {
        if (root->data > value) {
            root = root->left;
            i++;
            continue;
        } else if (root->data < value) {
            root = root->right;
            i++;
            continue;
        } else {
            return i;
        }
    }
    return -1;
}

int main(){
    Node *root = NULL;
    insert(&root, 1);
    insert(&root, 1);
    insert(&root, 8);
    insert(&root, 9);
    insert(&root, 7);
    insert(&root, 3);
    insert(&root, 4);
    printTree(root, "root", 0);
    printf("%d\n",getNodeByValue(root, 1));
    delltree(root);
    return 0;
}