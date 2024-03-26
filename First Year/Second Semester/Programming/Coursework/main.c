#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <windows.h>
#include "func.h"


int main(int argc, char **argv){
    setlocale(LC_ALL, "");
    system("chcp 1251");

    int choice;
    char tmp[2];

    char* key;
    char* keycpy;
    char* text;
    char* ciptext;
    char* deciptext;
    FILE *ftext;


    key = (char*)malloc(sizeof(char) * MAX);
    keycpy = (char*)malloc(sizeof(char) * MAX);
    text = (char*)malloc(sizeof(char) * MAX);
    ciptext = (char*)malloc(sizeof(char) * MAX);
    deciptext = (char*)malloc(sizeof(char) * MAX);

        printf("------------------------------МЕНЮ------------------------------\n");
    printf("Нажмите '1' чтобы выполнить шифрование и дешифрование текста (В консоли)\n");
    printf("Нажмите '2' чтобы выполнить только шифрование текста (В консоли)\n");
    printf("Нажмите '3' чтобы выполнить только дешифрование текста (В консоли)\n");
    printf("Нажмите '4' чтобы выполнить шифрование и дешифрование текста (Используя файл)\n");
    printf("Нажмите '5' чтобы выполнить только шифрование текста (Используя файл)\n");
    printf("Нажмите '6' чтобы выполнить только дешифрование текста (Используя файл)\n");
    printf("Нажмите '0' для выхода из программы\n");
    printf("----------------------------------------------------------------\n");

    do{
        printf("-> ");
        int mn = scanf("%d", &choice);
        if (mn == 0){
            clear_stdin();
        }
        if (mn == 1 && choice >= 0 && choice <= 6) {
                break;
            }
        printf("Неверный ввод. Пожалуйста, повторите попытку\n");
    } while(1);


    fgets(tmp, 2, stdin);
    printf("\n");

    switch(choice){
        case 0:
            exit(1);
        break;
        
        case 1:
            do{
                printf("Введите ключ: ");
                fgets(key, MAX, stdin);
                removeDuplicates(key);
                if (strlen(key) - 1 <= 2){
                    printf("Неверный ввод. Минимальный размер ключа: 3 символа. Пожалуйста, повторите попытку\n");
                }
            } while (strlen(key) - 1 <= 2);
            strcpy(keycpy, key);
            printf("\n");
            do{
                printf("Введите текст для шифрования: ");
                fgets(text, MAX, stdin);
                if((strlen(key) - 1) > (strlen(text) - 1)){
                    printf("Размер текста для шифрования должен быть больше размера ключа. Пожалуйста, повторите попытку\n");
                }
                else if ((strlen(text) - 1) < 10){
                    printf("Размер текста для шифрования должен быть больше иил равен 10 символам. Пожалуйста, повторите попытку\n");
                }
                else if ((strlen(text) - 1) > 250){
                    printf("Размер текста для шифрования не может превышать 250 символов. Пожалуйста, повторите попытку\n");
                }
            } while ((strlen(key) - 1) > (strlen(text) - 1) || (strlen(text) - 1) < 10 || (strlen(text) - 1) > 250);
            Cipher(key, text, ciptext);
            printf("\n");
            DeCipher(key, keycpy, ciptext, deciptext);
            printf("\n");
            for (int i = 0; i <= strlen(text); i++){
                if (text[i] == '\n'){
                    text[i] = ' ';
                }
            }
        break;

        case 2:
            do{
                printf("Введите ключ: ");
                fgets(key, MAX, stdin);
                removeDuplicates(key);
                if (strlen(key) - 1 <= 2){
                    printf("Неверный ввод. Минимальный размер ключа: 3 символа. Пожалуйста, повторите попытку\n");
                }
            } while (strlen(key) - 1 <= 2);        
            printf("\n");
            do{
                printf("Введите текст для шифрования: ");
                fgets(text, MAX, stdin);
                if((strlen(key) - 1) > (strlen(text) - 1)){
                    printf("Размер текста для шифрования должен быть больше размера ключа. Пожалуйста, повторите попытку\n");
                }
                else if ((strlen(text) - 1) < 10){
                    printf("Размер текста для шифрования должен быть больше иил равен 10 символам. Пожалуйста, повторите попытку\n");
                }
                else if ((strlen(text) - 1) > 250){
                    printf("Размер текста для шифрования не может превышать 250 символов. Пожалуйста, повторите попытку\n");
                }
                
            } while ((strlen(key) - 1) > (strlen(text) - 1) || (strlen(text) - 1) < 10 || (strlen(text) - 1) > 250);
            Cipher(key, text, ciptext);
            printf("\n");
        break;

        case 3:
            do{
                printf("Введите ключ: ");
                fgets(keycpy, MAX, stdin);
                removeDuplicates(keycpy);
                if (strlen(keycpy) - 1 <= 2){
                    printf("Неверный ввод. Минимальный размер ключа: 3 символа. Пожалуйста, повторите попытку\n");
                }
            } while (strlen(keycpy) - 1 <= 2);
            strcpy(key, keycpy);
            do{
                printf("Введите текст для шифрования: ");
                fgets(text, MAX, stdin);
                if((strlen(key) - 1) > (strlen(text) - 1)){
                    printf("Размер текста для шифрования должен быть больше размера ключа. Пожалуйста, повторите попытку\n");
                }
                else if ((strlen(text) - 1) < 10){
                    printf("Размер текста для шифрования должен быть больше иил равен 10 символам. Пожалуйста, повторите попытку\n");
                }
                else if ((strlen(text) - 1) > 250){
                   printf("Размер текста для шифрования не может превышать 250 символов. Пожалуйста, повторите попытку\n");
                }
                
            } while ((strlen(key) - 1) > (strlen(text) - 1) || (strlen(text) - 1) < 10 || (strlen(text) - 1) > 250);
            int n = sizeof(key) / sizeof(key[0]);
            qsort(key, n, sizeof(char), compare);
            printf("\n");
            DeCipher(key, keycpy, text, deciptext);
        break;

        case 4:
            ftext = fopen(argv[1], "r");
            if (ftext == NULL){
                printf("Файл не был обнаружен\n");
                return 1;
            }
            do{
                printf("Введите ключ: ");
                fgets(key, MAX, stdin);
                removeDuplicates(key);
                if (strlen(key) - 1 <= 2){
                    printf("Неверный ввод. Минимальный размер ключа: 3 символа. Пожалуйста, повторите попытку\n");
                }
            } while (strlen(key) - 1 <= 2);
            strcpy(keycpy, key);
            printf("\n");
            File_Cipher(ftext, text, key);
            Cipher(key, text, ciptext);
            printf("\n");
            DeCipher(key, keycpy, ciptext, deciptext);
        break;

        case 5:
            ftext = fopen(argv[1], "r");
            if (ftext == NULL){
                printf("Файл не был обнаружен\n");
                return 1;
            }
            do{
                printf("Введите ключ: ");
                fgets(key, MAX, stdin);
                removeDuplicates(key);
                if (strlen(key) - 1 <= 2){
                    printf("Неверный ввод. Минимальный размер ключа: 3 символа. Пожалуйста, повторите попытку\n");
                }
            } while (strlen(key) - 1 <= 2);
            printf("\n");
            File_Cipher(ftext, text, key);
            Cipher(key, text, ciptext);
        break;

        case 6:
            ftext = fopen(argv[1], "r");
            if (ftext == NULL){
                printf("Файл не был обнаружен\n");
                return 1;
            }
            do{
                printf("Введите ключ: ");
                fgets(keycpy, MAX, stdin);
                removeDuplicates(keycpy);
                if (strlen(keycpy) - 1 <= 2){
                    printf("Неверный ввод. Минимальный размер ключа: 3 символа. Пожалуйста, повторите попытку\n");
                }
            } while (strlen(keycpy) - 1 <= 2);
            strcpy(key, keycpy);
            File_Cipher(ftext, text, keycpy);
            int n1 = sizeof(key) / sizeof(key[0]);
            qsort(key, n1, sizeof(char), compare);
            printf("\n");
            DeCipher(key, keycpy, text, deciptext); 
        break;
    }

    free(key);
    free(keycpy); 
    free(text); 
    free(ciptext); 
    free(deciptext);

    return 0;
}