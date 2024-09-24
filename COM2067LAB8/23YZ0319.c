/*
* @author Busra Zenbilci
* student number: 23YZ0319
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

struct RBNode {
    int data;
    NodeColor color;
    struct RBNode *left, *right, *parent;
};


struct RBNode* createNode(int data);
void rotateLeft(struct RBNode **root, struct RBNode *x);
void rotateRight(struct RBNode **root, struct RBNode *y);
void fix_vio(struct RBNode **root, struct RBNode *z);
void insertNode(struct RBNode **root, int data);
void inorderTraversal(struct RBNode *root);
void printTreeLevel(struct RBNode* node, int level, int isFirst);
void printTreeStr(struct RBNode* root);
int getTreeHeight(struct RBNode *node);

struct RBNode *root = NULL;


int main() {
    int value;
    while (1) {
        scanf("%d", &value);
        if (value == -1)
            break;
        insertNode(&root, value);
    }

    inorderTraversal(root);
    printf("\n");
    printTreeStr(root);

    return 0;
}


struct RBNode* createNode(int data) {

    struct RBNode *node = (struct RBNode*)malloc(sizeof(struct RBNode));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void rotateLeft(struct RBNode **root, struct RBNode *x) {

    struct RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == NULL)
        (*root) = y;

    else if (x == x->parent->left)
        x->parent->left = y;

    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(struct RBNode **root, struct RBNode *y) {

    struct RBNode *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        (*root) = x;

    else if (y == y->parent->left)
        y->parent->left = x;
        
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;

}

void fix_vio(struct RBNode **root, struct RBNode *z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct RBNode *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        } else {
            struct RBNode *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertNode(struct RBNode **root, int data) {
    struct RBNode *z = createNode(data);
    struct RBNode *y = NULL;
    struct RBNode *x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fix_vio(root, z);
}

void inorderTraversal(struct RBNode *root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d\n", root->data);
    inorderTraversal(root->right);
}

int getTreeHeight(struct RBNode *node) {
    if (node == NULL)
        return 0;
    int leftHeight = getTreeHeight(node->left);
    int rightHeight = getTreeHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


void printTreeStr(struct RBNode* root) {
    int totalHeight = getTreeHeight(root);
    for (int i = 1; i <= totalHeight; i++) {
        printTreeLevel(root, i, 1);
        printf("\n");
    }
}

void printTreeLevel(struct RBNode* node, int level, int isFirst) {
    if (node == NULL)
        return;

    if (level == 1) {
        if (!isFirst) {
            printf(" ");
        }
        printf("%d %c", node->data, node->color == RED ? 'R' : 'B');
        if (node->parent != NULL) {
            printf(" (%d %c)", node->parent->data, node == node->parent->left ? 'L' : 'R');
        }
    } else if (level > 1) {
        printTreeLevel(node->left, level - 1, isFirst);
        if (node->left == NULL && node->right != NULL && isFirst) {
            isFirst = 1;
        } else {
            isFirst = 0;
        }
        printTreeLevel(node->right, level - 1, isFirst);
    }
}


