#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "func.h"

void clear_stdin() {
    int trash;
    do {
        trash = getchar();
    } while (trash != '\n' && trash != EOF);
}


void removeDuplicates(char* str) {
    int len = strlen(str);
    bool seen[256] = {false}; // создаем массив флагов для отслеживания уже встреченных символов

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (!seen[str[i]]) { // если символ еще не встречался
            seen[str[i]] = true; // помечаем его как встреченный
            str[j++] = str[i]; // добавляем символ в новую строку
        }
    }
    str[j] = '\0'; // добавляем нулевой символ в конец новой строки

}

int compare(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}


void Cipher(char* key, char* text, char* ciptext){
    int col = strlen(key) - 1;
    int row = ((strlen(text) - 1) % col) ? (((strlen(text) - 1) / col) + 1) : ((strlen(text) - 1) / col);


    char** cipher;
    cipher = (char**)malloc(sizeof(char*) * row);
    for (int i = 0; i <  row; i++){
        cipher[i] = (char*)malloc(sizeof(char) * col);
    }

    char* ctext;
    ctext = (char*)malloc(sizeof(char) * MAX);

     for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            cipher[i][j] = text[(i*col)+j];
        }
    }
    
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (cipher[i][j] == '\n' || cipher[i][j] == '\0'){
                cipher[i][j] = ' ';
            }
        }
    }


     for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%c ", cipher[i][j]);
        }
        printf("\n");
    } 

    printf("\n");

    char temp;
    for (int i = 0; i < col; i++){
        for (int j = i + 1; j < col; j++){
            if (key[i] > key[j]){
                temp = key[i];
                key[i] = key[j];
                key[j] = temp;
                for (int k = 0; k < row; k++){
                    temp = cipher[k][i];
                    cipher[k][i] = cipher[k][j];
                    cipher[k][j] = temp;
                }
            }
        }
    }

     for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%c ", cipher[i][j]);
        }
        printf("\n");
    } 

    int index = 0;
    for (int i = 0; i < col; i++){
        for (int j = 0; j < row; j++){
            ctext[index++] = cipher[j][i];
        }
    }


    printf("\nЗашифрованный текст: ");
    printf("%s", ctext);

    strcpy(ciptext, ctext);

    for (int i = 0; i <  row; i++){
        free(cipher[i]);
    }
    free(cipher);
    free(ctext);
}

void DeCipher(char* key, char* keycpy, char* text, char* deciptext){
    int col = strlen(key) - 1;
    int row = ((strlen(text) - 1) % col) ? (((strlen(text) - 1) / col) + 1) : ((strlen(text) - 1) / col);

    char** decipher;
    decipher = (char**)malloc(sizeof(char*) * row);
    for (int i = 0; i <  row; i++){
        decipher[i] = (char*)malloc(sizeof(char) * col);
    }

    char* detext;
    detext = (char*)malloc(sizeof(char) * MAX);

    int k = 0;
    for(int j = 0; j < col; j++){
        for (int i = 0; i < row; i++){
            decipher[i][j] = text[k++];
        }
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (decipher[i][j] == '\n' || decipher[i][j] == '\0'){
                decipher[i][j] = ' ';
            }
        }
    }


     for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%c ", decipher[i][j]);
        }
        printf("\n");
    } 

    printf("\n");

    char temp;
    for (int i = 0; i < col; i++){
        for (int j = 0; j < col; j++){
            if (key[i] == keycpy[j]){
                temp = key[i];
                key[i] = key[j];
                key[j] = temp;
                for (int k = 0; k < row; k++){
                    temp = decipher[k][i];
                    decipher[k][i] = decipher[k][j];
                    decipher[k][j] = temp;
                }
            }
        }
    }



     for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%c ", decipher[i][j]);
        }
        printf("\n");
    } 

    int index = 0;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            detext[index++] = decipher[i][j];
        }
    }



    printf("\nДешифрованный текст: ");
    printf("%s", detext);
    printf("\n");

    strcpy(deciptext, detext);

    for (int i = 0; i <  row; i++){
        free(decipher[i]);
    }
    free(decipher);
    free(detext);

}

void File_Cipher(FILE *ftext, char* text, char* key){
    int index = 0;
    char* text_file;
    char ch;

    text_file = (char*)malloc(sizeof(char) * MAX);

    while ((text_file[index] = fgetc(ftext)) != EOF && index < MAX){
        index++;
    }

    text_file[index] = '\0';
    fclose(ftext);

    if((strlen(key) - 1) > (strlen(text_file) - 1)){
        printf("Размер текста для шифрования должен быть больше размера ключа. Пожалуйста, повторите попытку\n");
        exit(1);
    }
    else if ((strlen(text_file) - 1) < 10){
        printf("Размер текста для шифрования должен быть больше иил равен 10 символам. Пожалуйста, повторите попытку\n");
        exit(1);
    }
    else if ((strlen(text_file) - 1) > 250){
        printf("Размер текста для шифрования не может превышать 250 символов. Пожалуйста, повторите попытку\n");
        exit(1);
    }    
    
    strcpy(text, text_file);
    free(text_file);
}