#include "hashtab.h"

unsigned int hashtab_hash(char *key, int size){
    unsigned int h = 0, hash_mul = 31;

    while(*key){
        h = h * hash_mul + (unsigned int)*key++;
    }

    return h % size;
}

unsigned int add_hash(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash += (unsigned char)(*key);
        key++;
    }
    return hash % size;
}

void hashtab_init(struct listnode **hashtab, int size){
    for(int i = 0; i < size; i++){
        hashtab[i] = NULL;
    }
}

void hashtab_add(struct listnode **hashtab, char *key, int value, int size){
    struct listnode *node;

    int index = hashtab_hash(key, size);
    node = malloc(sizeof(*node));
    if(node != NULL){
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

void hashtab_add_ADD(struct listnode **hashtab, char *key, int value, int size){
    struct listnode *node;
    
    int index = add_hash(key, size);
    node = malloc(sizeof(*node));
    if(node != NULL){
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int size){
    struct listnode *node;

    int index = hashtab_hash(key, size);
    for(node = hashtab[index]; node != NULL; node = node->next){
        if(0 == strcmp(node->key, key)){
            return node;
        }
    }
    return NULL;
}

struct listnode *hashtab_lookup_ADD(struct listnode **hashtab, char *key, int size){
    struct listnode *node;

    int index = add_hash(key, size);
    for(node = hashtab[index]; node != NULL; node = node->next){
        if(0 == strcmp(node->key, key)){
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key, int size){
    struct listnode *node, *prev = NULL;
    int index = hashtab_hash(key, size);
    for(node = hashtab[index]; node != NULL; node = node->next){
        if(0 == strcmp(node->key, key)){
            hashtab[index] = node->next;
        }else{
            prev->next = node->next;
        }
        free(node);
        return;
    }
    prev = node;
}
