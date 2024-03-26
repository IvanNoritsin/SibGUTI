#include <stdlib.h>
#include <string.h>

struct listnode{
    char *key;
    int value;
    struct listnode *next;
};

const unsigned FNV_32_PRIME = 0x01000193;

unsigned int hashtab_hash(char *key, int size);
unsigned int add_hash(char *key, int size);
void hashtab_init(struct listnode **hashtab, int size);
void hashtab_add(struct listnode **hashtab, char *key, int value, int size);
void hashtab_add_ADD(struct listnode **hashtab, char *key, int value, int size);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int size);
struct listnode *hashtab_lookup_ADD(struct listnode **hashtab, char *key, int size);
void hashtab_delete(struct listnode **hashtab, char *key, int size);