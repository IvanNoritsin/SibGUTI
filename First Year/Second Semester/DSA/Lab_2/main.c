#include <stdio.h>
#include <time.h>
#include "bstree.h"
#include "hashtab.h"

struct words{
    char word[100];
};

// функция для подсчета коллизий
int count_collisions(struct listnode **hashtab, int HASHTAB_SIZE) {
    int count = 0;
    for(int i = 0; i < HASHTAB_SIZE; i++){
        if(hashtab[i] != NULL){
            struct listnode* cur = hashtab[i];
            while(cur != NULL && cur->next != NULL){
                count++;
                cur = cur->next;
            }
        }
    }
    return count;
}

int main(){
    srand(time(NULL));

    struct bstree* tree = NULL;
    struct bstree* treeSort = NULL;

    FILE *file = fopen("data.txt", "r");
    FILE *sortFile = fopen("dataSorting.txt", "r");
    FILE *res = fopen("result.txt", "w+");
    if(file == NULL || sortFile == NULL){
        printf("Open error!\n");
        return 1;
    }

    double time_spent;
    clock_t start, end;
    int size = 10000;

    for(int i = 0; i < 20; i++){
        struct words* list = (struct words*)malloc(size * sizeof(struct words)); // список для среднего случая
        struct words* listSort = (struct words*)malloc(size * sizeof(struct words)); // список для худшего случая

        printf("SIZE = %d\n", size);
        fprintf(res, "SIZE = %d\n", size);

        // заполнение среднего списка
        for(int j = 0; j < size; j++){
           fscanf(file, "%s", list[j].word);
        }

        // заполнение худшего списка
        for(int j = 0; j < size; j++){
           fscanf(sortFile, "%s", listSort[j].word);
        }

        // создание и добавление значений в бинарное дерево (средний случай)
        int k = 0;
        tree = bstree_create(list[0].word, k);
        for(k = 1; k < size; k++){
            bstree_add(tree, list[k].word, k);
        }

        // создание и добавление значений в бинарное дерево (худший случай)
        k = 0;
        treeSort = bstree_create(listSort[0].word, k);
        for(k = 1; k < size; k++){
            bstree_add(treeSort, listSort[k].word, k);
        }

        // поиск в бинарном дереве (средний случай)
        time_spent = 0.0;
        for(int l = 0; l < size; l++){
            struct bstree* node;
            char* w = list[rand() % size].word;
            start = clock();
            node = bstree_lookup(tree, w);
            end = clock();
            time_spent +=  (double)(end - start) / CLOCKS_PER_SEC;
        }
        printf("TIME BSTREE_LOOKUP = %f\n", time_spent);
        fprintf(res, "TIME BSTREE_LOOKUP = %f\n", time_spent);

        // создание и добавление значений в хеш-таблицу
        struct listnode** hashtab = (struct listnode**)malloc(size * sizeof(struct listnode));
        hashtab_init(hashtab, size);
        for(int p = 0; p < size; p++){
            hashtab_add(hashtab, list[p].word, p, size);
        }

        // поиск значений в хеш-таблице
        for(int t = 0; t < size; t++){
            struct listnode* node;
            start = clock();
            node = hashtab_lookup(hashtab, list[rand() % size].word, size);
            end = clock();
            time_spent +=  (double)(end - start) / CLOCKS_PER_SEC;
        }
        printf("TIME HASHTAB_LOOKUP = %f\n", time_spent);
        fprintf(res, "TIME HASHTAB_LOOKUP = %f\n", time_spent);

        // поиск минимального значения в бинарном дереве (средний случай)
        time_spent = 0.0;
        for(int t = 0; t < size; t++){
            struct listnode* node;
            start = clock();
            node = bstree_min(tree);
            end = clock();
            time_spent +=  (double)(end - start) / CLOCKS_PER_SEC;
        }
        printf("TIME MIN NOWORST = %f\n", time_spent);
        fprintf(res, "TIME MIN NOWORST = %f\n", time_spent);

        // поиск минимального значения в бинарном дереве (худший случай)
        time_spent = 0.0;
        for(int t = 0; t < size; t++){
            struct listnode* node;
            start = clock();
            node = bstree_min(treeSort);
            end = clock();
            time_spent +=  (double)(end - start) / CLOCKS_PER_SEC;
        }
        printf("TIME MIN WORST = %f\n", time_spent);
        fprintf(res, "TIME MIN WORST = %f\n", time_spent);

        // новая хеш-таблица, но с новой хеш-функцией
        struct listnode** hashtabADD = (struct listnode**)malloc(size * sizeof(struct listnode));
        hashtab_init(hashtabADD, size);
        for(int p = 0; p < size; p++){
            hashtab_add_ADD(hashtabADD, list[p].word, p, size);
        }

        // поиск значений в хеш-таблице
        for(int t = 0; t < size; t++){
            struct listnode* node;
            start = clock();
            node = hashtab_lookup_ADD(hashtabADD, list[rand() % size].word, size);
            end = clock();
            time_spent +=  (double)(end - start) / CLOCKS_PER_SEC;
        }
        printf("TIME HASHTAB_LOOKUP_ADD = %f\n", time_spent);
        fprintf(res, "TIME HASHTAB_LOOKUP_ADD = %f\n", time_spent);

        // подсчет коллизий
        int collisions1 = 0, collisions2 = 0;
        collisions1 = count_collisions(hashtab, size);
        collisions2 = count_collisions(hashtabADD, size);
        printf("COLLISIONS KP = %d | COLLISIONS ADD = %d\n", collisions1, collisions2);
        fprintf(res, "COLLISIONS KP = %d | COLLISIONS ADD = %d\n", collisions1, collisions2);

        printf("============================\n");
        fprintf(res, "============================\n");
        size+=10000;

        free(list);
        free(listSort);
        free(hashtab);
        
        // возврат коретки в начало файла
        rewind(file);
        rewind(sortFile);
    } 

    fclose(file);
    fclose(sortFile);
    fclose(res);

    return 0;   
}