
#include <stdio.h>
#include <stdlib.h>

int flag = 0;
int rightToLeft(char letters[][15], int rows, int cols, char name[50], int size_name);
void printer_1(int found_row, int found_col, char name[50], int size_name);
int upToDown(char letters[][15], int rows, int cols, char name[50], int size_name);
void printer_2(int found_row, int found_col, char name[50], int size_name);
int diagonally_1(char letters[][15], int rows, int cols, char name[50], int size_name);
void printer_3(int found_row, int found_col, char name[50], int size_name);
int diagonally_2(char letters[][15], int rows, int cols, char name[50], int size_name);
void printer_4(int found_row, int found_col, char name[50], int size_name);
void printer_all(int row, int col);

int main()
{
    int row = 15;
    int col = 15;
    int size_of_word = 50;
    char array_of_letters[row][col];
    char word[size_of_word];
    char temp; // garbage yerine temp

    // Kare ızgara için karakterleri kullanıcıdan al
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%c", &array_of_letters[i][j]);
            scanf("%c", &temp); // Her harften sonra boşluk veya yeni satır karakterini temizle
        }
    }
    // Aranacak kelimeyi al
    scanf("%s", word);

    // Kelimenin gerçek boyutunu bul
    int size_of_real_word = 0;
    while (word[size_of_real_word] != '\0') {
        size_of_real_word++;
    }

    // Sağdan sola arama
    rightToLeft(array_of_letters, row, col, word, size_of_real_word);

    // Kelimenin tersini oluştur
    char reverse_word[size_of_real_word + 1];
    for (int i = 0; i < size_of_real_word; i++) {
        reverse_word[i] = word[size_of_real_word - 1 - i];
    }
    reverse_word[size_of_real_word] = '\0';

    // Soldan sağa ve ters kelime ile arama
    rightToLeft(array_of_letters, row, col, reverse_word, size_of_real_word);

    // Yukarıdan aşağıya arama
    upToDown(array_of_letters, row, col, word, size_of_real_word);
    upToDown(array_of_letters, row, col, reverse_word, size_of_real_word);

    // Çapraz arama
    diagonally_1(array_of_letters, row, col, word, size_of_real_word);
    diagonally_1(array_of_letters, row, col, reverse_word, size_of_real_word);
    diagonally_2(array_of_letters, row, col, word, size_of_real_word);
    diagonally_2(array_of_letters, row, col, reverse_word, size_of_real_word);

    // Eğer kelime bulunamazsa tüm karakterleri '*' ile yazdır
    if (flag == 0) {
        printer_all(row, col);
    }
    return 0;
}

int rightToLeft(char letters[][15], int rows, int cols, char name[50], int size_name) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - size_name + 1; j++) {
            int found = 1;
            for (int w = 0; w < size_name; w++) {
                if (letters[i][j + w] != name[w]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                printer_1(i, j, name, size_name);
                flag = 1;
                return 1;
            }
        }
    }
    return 0;
}

void printer_1(int found_row, int found_col, char name[50], int size_name) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (i == found_row && j >= found_col && j < found_col + size_name) {
                printf("%c", name[j - found_col]);
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}

int upToDown(char letters[][15], int rows, int cols, char name[50], int size_name) {
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows - size_name + 1; i++) {
            int found = 1;
            for (int w = 0; w < size_name; w++) {
                if (letters[i + w][j] != name[w]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                printer_2(i, j, name, size_name);
                flag = 1;
                return 1;
            }
        }
    }
    return 0;
}

void printer_2(int found_row, int found_col, char name[50], int size_name) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (j == found_col && i >= found_row && i < found_row + size_name) {
                printf("%c", name[i - found_row]);
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}

int diagonally_1(char letters[][15], int rows, int cols, char name[50], int size_name) {
    for (int i = 0; i < rows - size_name + 1; i++) {
        for (int j = 0; j < cols - size_name + 1; j++) {
            int found = 1;
            for (int w = 0; w < size_name; w++) {
                if (letters[i + w][j + w] != name[w]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                printer_3(i, j, name, size_name);
                flag = 1;
                return 1;
            }
        }
    }
    return 0;
}

void printer_3(int found_row, int found_col, char name[50], int size_name) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            int print_flag = 0;
            for (int w = 0; w < size_name; w++) {
                if (i == found_row + w && j == found_col + w) {
                    printf("%c", name[w]);
                    print_flag = 1;
                    break;
                }
            }
            if (!print_flag) {
                printf("*");
            }
        }
        printf("\n");
    }
}

int diagonally_2(char letters[][15], int rows, int cols, char name[50], int size_name) {
    for (int i = 0; i < rows - size_name + 1; i++) {
        for (int j = size_name - 1; j < cols; j++) {
            int found = 1;
            for (int w = 0; w < size_name; w++) {
                if (letters[i + w][j - w] != name[w]) {
                    found = 0;
                    break;
                }
            }
            if (found) {
                printer_4(i, j, name, size_name);
                flag = 1;
                return 1;
            }
        }
    }
    return 0;
}

void printer_4(int found_row, int found_col, char name[50], int size_name) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            int print_flag = 0;
            for (int w = 0; w < size_name; w++) {
                if (i == found_row + w && j == found_col - w) {
                    printf("%c", name[w]);
                    print_flag = 1;
                    break;
                }
            }
            if (!print_flag) {
                printf("*");
            }
        }
        printf("\n");
    }
}

void printer_all(int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("*");
        }
        printf("\n");
    }
}
