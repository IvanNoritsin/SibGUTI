#include <stdio.h>
#include <string.h>

struct toy{
    char name[20];
    float cost;
} toy;

void clear_stdin() {
    int trash;
    do {
        trash = getchar();
    } while (trash != '\n' && trash != EOF);
}

void newfile(FILE *t){ 
    char ch;
    do { 
        printf("\nName: "); 
        scanf("%s", toy.name);
        printf("Cost: "); 
        scanf("%f", &toy.cost);
        fwrite(&toy, sizeof(toy), 1, t);
        printf("\nEnd of entry? y/n ");
        scanf("\n%c",&ch); 
        } while (ch != 'y');
fclose(t);
}

void add(FILE *t){ 
    char ch;
    do { 
        printf("\nName: "); 
        scanf("%s", toy.name);
        printf("Cost: "); 
        scanf("%f", &toy.cost);
        fwrite(&toy, sizeof(toy), 1, t);
        printf("\nEnd of entry? y/n ");
        scanf("\n%c",&ch); 
        } while (ch != 'y');
fclose(t);
}

void max(FILE *t){
    float max = -10000000;
    char name[20];
    fread(&toy, sizeof(toy), 1, t);
    while (!feof(t)){
        if (toy.cost > max){
            strcpy(name, toy.name);
            max = toy.cost;
        }
        fread(&toy, sizeof(toy), 1, t);
    }
    printf("Name: %s %s\n", name, &name[10]);
    printf("Max cost: %f", max);
    fclose(t);
}

int main(){
    FILE *f;
    int n, gc, mn, num;
    do{
        printf("--------------------Menu--------------------\nPress '1' to create a new file\nPress '2' to add a new entry\nPress '3' to display the most expensive toy\n--------------------------------------------\n");
        do {
            printf("-> ");
            mn = scanf("%d", &n);
            if (mn == 0){
                clear_stdin();
            }
            if (mn == 1 && n >= 1 && n <= 3) {
                break;
            }
            printf("Invalid input, please try again\n");

        } while(1);
        switch(n){
            case 1: 
                f = fopen("PRICE.dat", "wb");
                newfile(f);
                break;

            case 2:
                f = fopen("PRICE.dat", "ab");
                add(f);
                break;

            case 3:
                f = fopen("PRICE.dat", "rb");
                max(f);
                break;
        }
        
        printf("\n\n");
        printf("------------------------------------\nTo open the menu, press '1'\nTo exit the program, press '0'\n------------------------------------\n");
        do {
            printf("-> ");
            gc = scanf("%d", &num);
            if (gc == 0){
                clear_stdin();
            }
            if (gc == 1 && num >= 0 && num <= 1) {
                break;
            }
            printf("Invalid input, please try again\n");

        } while(1);

    } while(num == 1);


    return 0;
}
