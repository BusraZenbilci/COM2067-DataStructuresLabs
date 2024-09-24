/**
 * @author Busra Zenbilci
 * student number: 23YZ0319
 */

#include <stdio.h>
#include <stdlib.h>

// Struct for AVL tree nodes
struct AVLNode {
    int key;
    int value;
    struct AVLNode *right;
    struct AVLNode *left;
    int height;
};


int getHeight(struct AVLNode *node);
void updateHeight(struct AVLNode *node);
struct AVLNode* rotateRight(struct AVLNode *y);
struct AVLNode* rotateLeft(struct AVLNode *x);
int getBalanceFactor(struct AVLNode *node);
struct AVLNode* balanceNode(struct AVLNode *node);
struct AVLNode *insertNode(struct AVLNode *node, int key, int value);
void printInOrder(struct AVLNode *node);
int getTreeHeight(struct AVLNode *node);
void printTreeLevel(struct AVLNode* node, int level, char direction, int parentValue);
void printTreeStr(struct AVLNode* node);


int main() {
    struct AVLNode *root = NULL;
    int key, value;
    scanf("%d", &key);

    while (key != -1) {
        value = key;  // key and value are the same in this case
        root = insertNode(root, key, value);
        scanf("%d", &key);
    }

    printInOrder(root);
    printf("\n");
    printTreeStr(root);

    return 0;
}


int getHeight(struct AVLNode *node) {
    return node ? node->height : 0;
}

void updateHeight(struct AVLNode *node) {
    if (node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

struct AVLNode* rotateRight(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

struct AVLNode* rotateLeft(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

int getBalanceFactor(struct AVLNode *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

struct AVLNode *insertNode(struct AVLNode *node, int key, int value) {

    if (node == NULL) {
        struct AVLNode *newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
        newNode->value = value;
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (value < node->value) {

        node->left = insertNode(node->left, key, value);

    } else if (value > node->value) {

        node->right = insertNode(node->right, key, value);

    } else {

        return node;
    }

    return balanceNode(node);
}

struct AVLNode* balanceNode(struct AVLNode *node) {
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {

        return rotateRight(node);
    }

    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {

        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {

        return rotateLeft(node);
    }

    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {

        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}



void printInOrder(struct AVLNode *node) {
    if (node != NULL) {
        printInOrder(node->left);
        printf("%d\n", node->value);
        printInOrder(node->right);
    }
}

int getTreeHeight(struct AVLNode *node) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = getTreeHeight(node->left);
    int rightHeight = getTreeHeight(node->right);

    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}


void printTreeLevel(struct AVLNode* node, int level, char direction, int parentValue) {
    if (node == NULL) {
        return;
    }

    if (level == 1) {
        int balance = getBalanceFactor(node);
        if (node->value != parentValue) {
            printf("%d (%d %c) (%d B) ", node->value, parentValue, direction, balance);
        } else {
            printf("%d (%d B) ", node->value, balance);
        }
        return;
    }

    printTreeLevel(node->left, level - 1, 'L', node->value);
    printTreeLevel(node->right, level - 1, 'R', node->value);
}



void printTreeStr(struct AVLNode* node) {
    int currentLevel = 1;
    int totalHeight = getTreeHeight(node);

    while (currentLevel <= totalHeight) {
        printTreeLevel(node, currentLevel, '\0', node->value);
        printf("\n");
        currentLevel++;
    }
}
