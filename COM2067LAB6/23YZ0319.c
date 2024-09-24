#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int student_id;
    int grade;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Function to create a new node
Node* createNode(int student_id, int grade, Node* parent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->student_id = student_id;
    newNode->grade = grade;
    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

// Function to insert a new node into the BST
Node* insertNode(Node* root, int student_id, int grade, Node* parent) {
    if (root == NULL) {
        return createNode(student_id, grade, parent);
    }
    if (grade < root->grade) {
        root->left = insertNode(root->left, student_id, grade, root);
    } else if (grade > root->grade) {
        root->right = insertNode(root->right, student_id, grade, root);
    }
    return root;
}

// In-order traversal to print the sorted grades and IDs
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d %d\n", root->student_id, root->grade);
        inorderTraversal(root->right);
    }
}

// Function to print the tree structure at each level
void printCurrentLevel(Node* root, int level, int isLastNode) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d %d", root->student_id, root->grade);
        if (root->parent != NULL) {
            printf(" (%d %s)", root->parent->grade, (root == root->parent->left) ? "L" : "R");
        }
        if (!isLastNode) {
            printf(" "); 
        }
    } else if (level > 1) {
        printCurrentLevel(root->left, level-1, root->right == NULL && isLastNode);
        printCurrentLevel(root->right, level-1, isLastNode);
    }
}

// Function to calculate the height of the tree
int height(Node* node) {
    if (node == NULL) return 0;
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);

        if (lheight > rheight) return(lheight + 1);
        else return(rheight + 1);
    }
}

// Function to print the tree structure in level order
void printTree(Node* root) {
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        printCurrentLevel(root, i, 1);
        printf("\n");
    }
}

// Main function
int main() {
    Node* root = NULL;
    int student_id, grade;

    while (1) {
        scanf("%d", &student_id);
        if (student_id == -1) break; // End input
        scanf("%d", &grade);
        root = insertNode(root, student_id, grade, NULL);
    }

    // Print sorted grades and IDs
    inorderTraversal(root);
    
    printf("\n");
    
    // Print tree structure
    printTree(root);

    return 0;
}
