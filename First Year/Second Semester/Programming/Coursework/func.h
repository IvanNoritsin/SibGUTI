#include <stdio.h>

#define MAX 1000

void clear_stdin();
void removeDuplicates(char* str);
int compare(const void *a, const void *b);
void Cipher(char* key, char* text, char* ciptext);
void DeCipher(char* key, char* keycpy, char* text, char* deciptext);
void File_Cipher(FILE *ftext, char* text, char* key);