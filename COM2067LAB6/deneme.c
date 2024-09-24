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

// Function to print the tree structure
void printTree(Node* root) {
    if (root != NULL) {
        printf("%d %d", root->student_id, root->grade);
        if (root->parent != NULL) {
            printf(" (%d %s)", root->parent->grade, (root == root->parent->left) ? "L" : "R");
        }
        printf("\n");
        printTree(root->left);
        printTree(root->right);
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
