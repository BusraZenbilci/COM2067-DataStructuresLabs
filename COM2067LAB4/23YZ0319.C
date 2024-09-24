#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAG_SIZE 50
#define MAX_STACK_SIZE 100

typedef struct {
    char tags[MAX_STACK_SIZE][MAX_TAG_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack* s, char* tag) {
    if (!isFull(s)) {
        s->top++;
        strcpy(s->tags[s->top], tag);
    }
}

void pop(Stack* s) {
    if (!isEmpty(s)) {
        s->top--;
    }
}

char* peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->tags[s->top];
    }
    return NULL;
}

int main() {
    Stack stack;
    initStack(&stack);
    
    char html[10000]; // Assuming the input size won't exceed this limit
    scanf("%[^\n]", html); // Read the entire input as a single string
    
    char tag[MAX_TAG_SIZE];
    int i = 0, j;
    int isCorrect = 1; // Flag to check if the HTML is correct
    
    while (html[i] != '\0') {
        if (html[i] == '<') {
            i++;
            if (html[i] == '/') { // Closing tag
                i++;
                j = 0;
                while (html[i] != '>') {
                    tag[j++] = html[i++];
                }
                tag[j] = '\0';
                
                if (isEmpty(&stack) || strcmp(peek(&stack), tag) != 0) {
                    isCorrect = 0;
                    printf("error <%s>\n", tag);
                    break;
                } else {
                    pop(&stack);
                }
            } else { // Opening tag
                j = 0;
                while (html[i] != '>') {
                    tag[j++] = html[i++];
                }
                tag[j] = '\0';
                push(&stack, tag);
            }
        }
        i++;
    }
    
    if (isCorrect && isEmpty(&stack)) {
        printf("correct\n");
    } else if (isCorrect && !isEmpty(&stack)) {
        printf("error <%s>\n", peek(&stack));
    }
    
    return 0;
}
