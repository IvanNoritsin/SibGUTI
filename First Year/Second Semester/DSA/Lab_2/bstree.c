#include "bstree.h"

typedef struct bstree{
    char *key;
    int value;
    struct bstree *left;
    struct bstree *right;
} bstree;

struct bstree *bstree_create(char *key, int value){
    struct bstree *node;
    node = malloc(sizeof(*node));
    if(node != NULL){
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void bstree_add(struct bstree *tree, char *key, int value){
    if (tree == NULL){
        return;
    }
    struct bstree *parent, *node;
    while(tree != NULL){
        parent = tree;
        if(strcmp(key, tree->key) < 0){
             tree = tree->left;
        }else if(strcmp(key, tree->key) > 0){
            tree = tree->right;
        }else{
            return;
        }
    }
    node = bstree_create(key, value);
    if(strcmp(key, parent->key) < 0){
        parent->left = node;
    }else{
        parent->right = node;
    }
}

struct bstree *bstree_lookup(struct bstree *tree, char *key){
    while(tree != NULL){
        if(strcmp(key, tree->key) == 0){
            return tree;
        }else if(strcmp(key, tree->key) < 0){
            tree = tree->left;
        }else{
            tree = tree->right;
        }
    }
    return tree;
}

void replaceNode(struct bstree *parent, struct bstree *node, struct bstree *child){
    if(parent != NULL){
        if(strcmp(node->key, parent->key) < 0){
            parent->left = child;
        }else{
            parent->right = child;
        }
    }
}

struct bstree *deleteNode(struct bstree *tree, struct bstree *node, struct bstree *parent){

    struct bstree *min, *minparent;

    if(node->left == NULL){
        replaceNode(parent, node, node->right);
        if(parent == NULL){
            tree = node->right;
        }
    }else if(node->right == NULL){
        replaceNode(parent, node, node->left);
        if(parent == NULL){
            tree = node->left;
        }
    }else{
        min = node->right;
        minparent = min;
        while(min->left != NULL){
            minparent = min;
            min = min->left;
        }
        replaceNode(parent, node, min);
        if(node->right != min){
            minparent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        }else{
            min->left = node->left;
        }
        free(node);
        
        return tree;
    }
}

struct bstree *bstree_delete(struct bstree *tree, char *key){
    struct bstree *parent, *node;
    while(node != NULL && node->key != key){
        parent = node;

        if(strcmp(key, node->key) < 0){
            node = node->left;
        }else{
            node = node->right;
        }
    }

    if(node == NULL){
        return tree;
    }

    return deleteNode(tree, node, parent);
}

struct bstree *bstree_min(struct bstree *tree){
    if(tree == NULL){
        return NULL;
    }

    while(tree->left != NULL){
        tree = tree->left;
    }

    return tree;
}

struct bstree *bstree_max(struct bstree *tree){
    if(tree == NULL){
        return NULL;
    }

    while(tree->right != NULL){
        tree = tree->right;
    }

    return tree;
}
