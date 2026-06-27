#include <stdio.h>
#include <stdlib.h>




typedef struct node{
    void* elem;
    struct node* prev;
    struct node* next;
} node;

typedef struct list{
    node* first_el;
    node* last_el;
    int len;
} list;


int new_list(list* list){
    if (list==NULL){
        return -1;
    }

    list->first_el = NULL;
    list->last_el = NULL;
    list->len = 0;

    return 0;
}


node* seek(list* list, int index){
    node* ret;
    if (list==NULL){
        return NULL;
    }

    if (index<0 || index>=list->len){
        return NULL;
    }


    if (index<list->len/2){
        ret = list->first_el;
        for (int i = 0; i<index; i++){
            ret = ret->next;
        }
    } else{
        ret = list->last_el;
        for (int i = list->len-1; i>index; i--){
            ret = ret->prev;
        }
    }
    return ret;
}


void* get(list* list, int index){
    node* res = seek(list, index);
    if (res==NULL){
        return NULL;
    }
    return res->elem;
}


int add_back(list* list, void* el){
    if (list==NULL || el==NULL){
        return -1;
    }

    node* new_node = malloc(sizeof(node));

    if (new_node == NULL){
        return -1;
    }
    
    new_node->elem = el;
    new_node->prev = list->last_el;
    new_node->next = NULL;
    if (list->len==0){
        list->first_el = new_node;
        list->last_el = new_node;
    }
    else{
    list->last_el->next = new_node;
    list->last_el = new_node;
    }
    list->len+=1;
    return 0;


}


int add_front(list* list, void* el){
    if (list==NULL || el==NULL){
        return -1;
    }

    node* new_node = malloc(sizeof(node));

    if (new_node == NULL){
        return -1;
    }
    
    new_node->elem = el;
    new_node->prev = NULL;
    new_node->next = list->first_el;

    if (list->len==0){
        list->first_el = new_node;
        list->last_el = new_node;
    }
    else{
    list->first_el->prev = new_node;
    list->first_el = new_node;
    }
    list->len+=1;
    return 0;
}

int add_in(list* list, int index, void* elem){
    if (list==NULL){
        return -1;
    }

    if (index<0 || index>list->len){
        return -1;
    }

    if (index==0){
        return add_front(list, elem);
    }

    if (index==list->len){
        return add_back(list, elem);
    }

    node* new_node = malloc(sizeof(node));
    if (new_node==NULL){
        return -1;
    }
    new_node->elem = elem;
    new_node->next = seek(list, index);
    new_node->prev = new_node->next->prev;
    new_node->next->prev = new_node;
    new_node->prev->next = new_node;
    list->len+=1;
    return 0;
}

void* pop_back(list* list){
    if (list==NULL){
        return NULL;
    }

    if (list->len==0){
        return NULL;
    }
    node* node_to_del = list->last_el;
    void* ret = list->last_el->elem;
    if (list->len==1){
        list->first_el = NULL;
        list->last_el = NULL;
    } else{
        node* new_last = node_to_del->prev;
        new_last->next = NULL;
        list->last_el = new_last;
    }
    list->len-=1;
    free(node_to_del);
    return ret;
}



void* pop_front(list* list){
    if (list==NULL){
        return NULL;
    }

    if (list->len==0){
        return NULL;
    }
    node* node_to_del = list->first_el;
    void* ret = list->first_el->elem;
    if (list->len==1){
        list->first_el = NULL;
        list->last_el = NULL;
    } else{
        node* new_first = node_to_del->next;
        new_first->prev = NULL;
        list->first_el = new_first;
    }

    list->len-=1;
    free(node_to_del);
    return ret;
}



void* pop_in(list* list, int index){
    if (list==NULL){
        return NULL;
    }

    if (index<0 || index>=list->len){
        return NULL;
    }

    if (index==0){
        return pop_front(list);
    }

    if (index==list->len-1){
        return pop_back(list);
    }


    node* node_to_del = seek(list, index);
    void* ret = node_to_del->elem;
    node_to_del->next->prev = node_to_del->prev;
    node_to_del->prev->next = node_to_del->next;
    free(node_to_del);
    list->len-=1;
    return ret;
    
}

void** clear_list(list* list){
    if (list==NULL){
        return NULL;
    }

    if (list->len==0){
        return NULL;
    }
    void** mass = malloc(list->len*sizeof(void*));
    if (mass==NULL){
        return NULL;
    }

    node* current = list->first_el;
    node* next = current->next;
    int i = 0;
    while(current!=NULL){
        mass[i] = current->elem;
        next = current->next;

        free(current);

        current = next;
        i+=1;
    }
    

    list->first_el = NULL;
    list->last_el = NULL;
    list->len = 0;
    return mass;
}