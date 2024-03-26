#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f = NULL;
    FILE *s = NULL;
    char ch;
    int k = 0;

    f = fopen("text.txt", "r");
    s = fopen("newtext.txt", "w");

    if (f == NULL){
        printf("File opening error 'text.txt'\n");
        exit(1);
    }

    if (s == NULL){
        printf("File opening error 'newtext.txt'\n");
        exit(1);
    }

    while(!feof(f)){
        ch = fgetc(f);
        if (k == 0){
            if (ch >= 97 && ch <= 122){
                fputc(ch - 32, s);
                k = 1;
            }
            else{
                fputc(ch, s);
                k = 1;
            }
        }

        else{
            if (ch == ' '){
                if(ch != -1)
                fputc(ch, s);
                k = 0;
            }
            else{
                if(ch != -1)
                fputc(ch, s);
            }
        }
    }
    fclose(f);
    fclose(s);

    return 0;
}
