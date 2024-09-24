#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    char songName[50];
    int songNumber;
    struct node* prev;
    struct node* next;
};


struct node* createNode(char* name, int number) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->songName, name);
    newNode->songNumber = number;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void addNode(struct node** head, char* name, int number) {
    struct node* newNode = createNode(name, number);
    struct node* temp = *head;
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}


void printSongs(struct node* head, char start, int steps) {
    struct node* temp = head;
    int count = 0;

    // Başlangıç noktasını ayarla
    if (start == 'L') {
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }

    while (temp != NULL) {
        printf("%s\n", temp->songName);

        // steps kadar ileri veya geri git
        for (int i = 0; i < steps; i++) {
            if (start == 'F') {
                temp = temp->next;
            } else if (start == 'L') {
                temp = temp->prev;
            }
            if (temp == NULL) break;
        }

        count++;
    }
}

int main() {
    struct node* head = NULL;
    char songName[50];
    int songNumber = 1;
    
    
    while (1) {
        if (fgets(songName, sizeof(songName), stdin) == NULL) {
            break;
        }
        
        // fgets satır sonu karakterini de alır, bu yüzden kaldırmamız gerekiyor
        songName[strcspn(songName, "\n")] = '\0';

        if (strcmp(songName, "-1") == 0) break;
        addNode(&head, songName, songNumber);
        songNumber++;
    }
    
   
    char start;
    int steps;
    scanf(" %c %d", &start, &steps);
    
    
    printSongs(head, start, steps);
    
    return 0;
}