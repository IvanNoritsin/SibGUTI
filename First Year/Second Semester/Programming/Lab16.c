#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void clear_stdin() {
    int trash;
    do {
        trash = getchar();
    } while (trash != '\n' && trash != EOF);
}

typedef struct list{
    int val;
    struct list *next;
} list;

typedef struct svyaz{
    list *first;
    list *second;
    list *third;
} sv;

list *first, *second, *third;
list *p1, *p2, *p3;
sv *p;

int main(){
    int a, mn, n;
    int gc, num;
    sv *s = (sv*)malloc(sizeof(sv));
    s -> first = NULL;
    s -> second = NULL;
    s -> third = NULL;
    printf("Enter the numbers: \n");
    while (1){
        printf("-> ");
        scanf("%d", &a);
        printf("\n");
        if(a == 0){
            break;
        }

        if (a % 2 == 0){
            list *tmp = (list*)malloc(sizeof(list));
            tmp -> val = a;
            tmp -> next = NULL;
            if (first == NULL){
                first = tmp;
                s -> first = first;
            }
            else{
                first -> next = tmp;
                first = first -> next;
            }
        }

        if (a % 3 == 0){
            list *tmp = (list*)malloc(sizeof(list));
            tmp -> val = a;
            tmp -> next = NULL;
            if (second == NULL){
                second = tmp;
                s -> second = second;
            }
            else{
                second -> next = tmp;
                second = second -> next;
            }
        }

        if (a % 2 != 0 && a % 3 != 0){
            list *tmp = (list*)malloc(sizeof(list));
            tmp -> val = a;
            tmp -> next = NULL;
            if (third == NULL){
                third = tmp;
                s -> third = third;
            }
            else{
                third -> next = tmp;
                third = third -> next;
            }
        }

                
    }
    do {
                printf("----------------Menu----------------\nPress '1' to display the first list\nPress '2' to display the second list\nPress '3' to display the third list\n------------------------------------\n");
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
        
        
        printf("\n");
        p = s;
    
        switch (n){
            case 1:
            if (p -> first != NULL){
                p1 = p -> first;
                    printf("First list:\n");
                    while (p1 != NULL){
                        printf("|%d| ", p1 -> val);
                        p1 = p1 -> next;
                    }
            }
            else{
                printf("The first list is empty");
            }
                break;
            

            case 2:
            if (p -> second != NULL){
                p2 = p -> second;
                    printf("Second list:\n");
                    while (p2 != NULL){
                        printf("|%d| ", p2 -> val);
                        p2 = p2 -> next;
                    }
            }
            else{
                printf("The second list is empty");
            }
                break;

            case 3:
            if (p -> third != NULL){
                p3 = p -> third;
                    printf("Third list:\n");
                    while (p3 != NULL){
                        printf("|%d| ", p3 -> val);
                        p3 = p3 -> next;
                    }
            }
            else{
                printf("The third list is empty");
            }
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
