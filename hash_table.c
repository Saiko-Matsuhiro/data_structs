#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.c"



struct hnode{
    char* key;
    void* val;
};

typedef struct htable{
    list* mass;
    size_t len;
    size_t cap;
} htable;

int hnew(htable* table){
    if (table==NULL){
        return -1;
    }
    table->mass = malloc(sizeof(list)*4);

    if (table->mass==NULL){
        return -1;
    }

    for (int i = 0; i<4; i++){
        new_list(table->mass+i);
    }
    table->len = 0;
    table->cap = 4;
    return 0;
}





int hash_place(char* key, size_t cap){
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash%cap;

}



int resize(htable* table, size_t new_size){
    if (table==NULL){
        return -1;
    }

    if (new_size == 0){
        return -1;
    }

    struct hnode* elem;
    size_t place;
    list* ptr = malloc(new_size*sizeof(list));
    if (ptr == NULL){
        return -1;
    }

    for (int i = 0; i<new_size; i++){
        new_list(&ptr[i]);
    }

    for (int i = 0; i<table->cap; i++){
        size_t len = table->mass[i].len;
        for (int j = 0; j<len; j++){
            elem = pop_back(&table->mass[i]);
            place = hash_place(elem->key, new_size);
            add_back(&ptr[place], elem);
            
        }
    }

    free(table->mass);
    table->mass = ptr;
    table->cap = new_size;
    return 0;
    

}

struct hnode* hseek(htable* table, char* key){
    if (table==NULL){
        return NULL;
    }
    size_t place = hash_place(key, table->cap);
    struct hnode* elem;
    node* el = table->mass[place].first_el;
    for (int i = 0; i<table->mass[place].len; i++){
        elem = el->elem;
        if (strcmp(elem->key, key)==0){
            return elem;
        }
        el = el->next;
    }

    return NULL;
}

void* hget(htable* table, char* key){
    struct hnode* elem = hseek(table, key);
    if (elem==NULL){
        return NULL;
    }
    return elem->val;
}


void* pop(htable* table, char* key){
    if (table==NULL){
        return NULL;
    }

    if (key==NULL){
        return NULL;
    }
    if (((float)(table->len-1)/table->cap)<=0.2 && table->cap>4){
        resize(table, table->cap/2);
    }

    struct hnode* nod;
    int flag = 0;
    size_t place = hash_place(key, table->cap);
    node* el = table->mass[place].first_el;
    for (int i = 0; i<table->mass[place].len; i++){
        nod = el->elem;
        if (strcmp(nod->key, key)==0){
            pop_in(&table->mass[place], i);
            flag+=1;
            break;
        }
        el = el->next;
    }
    if (!flag){
        return NULL;
    }

    void* elem = nod->val;
    free(nod->key);
    free(nod);
    table->len-=1;
    return elem;

}



int add(htable* table, void* elem, char* key){
    if (table==NULL){
        return -1;
    }
    if (elem==NULL){
        return -1;
    }
    if (key==NULL){
        return -1;
    }
    if (hseek(table, key)!=NULL){
        return -1;
    }
    if (((float)(table->len+1)/table->cap)>=0.8){
        resize(table, table->cap*2);
    }
    struct hnode* new_node = malloc(sizeof(struct hnode));
    if (new_node==NULL){
        return -1;
    }
    new_node->key = malloc(sizeof(char)*strlen(key)+1);
    if (new_node->key==NULL){
        free(new_node);
        return -1;
    }
    memcpy(new_node->key, key, strlen(key)+1);
    new_node->val = elem;
    int place = hash_place(key, table->cap);
    if (add_back(&table->mass[place], new_node)==-1){
        free(new_node->key);
        free(new_node);
        return -1;
    }
    table->len+=1;
    return 0;
}



