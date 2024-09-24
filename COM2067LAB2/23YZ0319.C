#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int grid[MAX][MAX];
int visited[MAX][MAX];
int rows, cols;

void readGrid();
void initializeGrid();
int isSafe(int x, int y);
void DFS(int x, int y, int *blobSize);
void findBlobs();

int main() {
    readGrid();
    findBlobs();
    return 0;
}

void readGrid() {
    scanf("%d %d", &rows, &cols);
    initializeGrid();

    int x, y;
    while (scanf("%d", &x) && x != -1) {
        scanf("%d", &y);
        grid[x][y] = 1;
    }
}

void initializeGrid() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            grid[i][j] = 0;
            visited[i][j] = 0;
        }
    }
}

int isSafe(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] && !visited[x][y]);
}

void DFS(int x, int y, int *blobSize) {
    static int rowNum[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static int colNum[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    visited[x][y] = 1;
    (*blobSize)++;

    for (int k = 0; k < 8; k++) {
        if (isSafe(x + rowNum[k], y + colNum[k])) {
            DFS(x + rowNum[k], y + colNum[k], blobSize);
        }
    }
}

void findBlobs() {
    int blobSizes[MAX];
    int blobCount = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] && !visited[i][j]) {
                int blobSize = 0;
                DFS(i, j, &blobSize);
                blobSizes[blobCount++] = blobSize;
            }
        }
    }

    // Sort the blob sizes in increasing order
    for (int i = 0; i < blobCount - 1; i++) {
        for (int j = i + 1; j < blobCount; j++) {
            if (blobSizes[i] > blobSizes[j]) {
                int temp = blobSizes[i];
                blobSizes[i] = blobSizes[j];
                blobSizes[j] = temp;
            }
        }
    }

    printf("%d", blobCount);
    for (int i = 0; i < blobCount; i++) {
        printf(" %d", blobSizes[i]);
    }
    printf("\n");
}
