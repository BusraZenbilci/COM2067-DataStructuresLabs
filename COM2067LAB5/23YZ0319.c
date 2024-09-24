/**
 * Busra Zenbilci
 * 23YZ319
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CALLS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int priority;
} CallLogEntry;

int getPriority(const char *name) {
    if (strcmp(name, "Annem") == 0 || strcmp(name, "Babam") == 0 || strcmp(name, "Kardesim") == 0) return 1;
    if (strcmp(name, "Amcam") == 0 || strcmp(name, "Teyzem") == 0 || strcmp(name, "Dayim") == 0 || strcmp(name, "Halam") == 0) return 2;
    if (strcmp(name, "Isyeri") == 0 || strcmp(name, "Okul") == 0) return 3;
    if (strncmp(name, "Arkadasim", 9) == 0) return 4;
    if (strcmp(name, "Banka") == 0 || strcmp(name, "Kargo") == 0) return 5;
    if (strcmp(name, "Reklam") == 0) return 6;
    return 7; // Default priority for unknown names
}

int compare(const void *a, const void *b) {
    CallLogEntry *entryA = (CallLogEntry *)a;
    CallLogEntry *entryB = (CallLogEntry *)b;
    
    if (entryA->priority != entryB->priority) {
        return entryA->priority - entryB->priority;
    }
    
    return strcmp(entryA->name, entryB->name);
}

void sortCallLog(CallLogEntry callLog[], int size) {
    qsort(callLog, size, sizeof(CallLogEntry), compare);
}

int main() {
    CallLogEntry callLog[MAX_CALLS];
    int numCalls = 0;

    while (1) {
        char input[MAX_NAME_LENGTH];
        scanf("%s", input);
        if (strcmp(input, "-1") == 0) {
            break;
        }
        strcpy(callLog[numCalls].name, input);
        callLog[numCalls].priority = getPriority(input);
        numCalls++;
    }

    sortCallLog(callLog, numCalls);

    for (int i = 0; i < numCalls; i++) {
        printf("%s\n", callLog[i].name);
    }

    return 0;
}
