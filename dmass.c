
#include <stdio.h>
#include <stdlib.h>


typedef struct dmass{
    int* mass;
    int len;
    size_t cap;
} dmass;


int new_mass(dmass* mass){
    if(mass==NULL){
        return -1;
    }
    mass->mass = malloc(sizeof(int)*4);
    if (mass->mass==NULL){
        return -1;
    }
    mass->len = 0;
    mass->cap = 4;
    return 0;
}


int push_back(dmass* mass, int elem){
    if (mass==NULL){
        return -1;
    }

    if (mass->cap==mass->len){
        int* old = mass->mass;
        mass->mass = realloc(mass->mass, sizeof(int)*(mass->cap)*2);
        if (mass->mass==NULL){
            mass->mass = old;
            return -1;
        } else{
            mass->cap = mass->cap*2;
        }
    }
    mass->mass[mass->len] = elem;
    mass->len+=1;
    return 0;
}

int push_in(dmass* mass, int elem, int index){
    if (mass==NULL){
        return -1;
    }

    if (index>mass->len || index<0){
        return -1;
    }

    if (mass->cap==mass->len){
        int* old = mass->mass;
        mass->mass = realloc(mass->mass, sizeof(int)*(mass->cap)*2);
        if (mass->mass==NULL){
            mass->mass = old;
            return -1;
        } else{
            mass->cap = mass->cap*2;
        }
    }


    for(int i = mass->len; i>index; i--){
        mass->mass[i] = mass->mass[i-1];
    }
    mass->mass[index] = elem;
    mass->len+=1;
    return 0;
}


int reserve(dmass* mass, size_t size){
    if (mass==NULL){
        return -1;
    }
    if (size<=0){
        return -1;
    }

    int* old = mass->mass;
    mass->mass = realloc(mass->mass, sizeof(int)*size);
    if (mass->mass==NULL){
        mass->mass = old;
        return -1;
    }
    
    mass->cap = size;
    if (mass->len>size){
        mass->len = size;
    }
    return 0;
}


int del_back(dmass* mass){
    if (mass==NULL){
        return -1;
    }

    if (mass->len==0){
        return -1;
    }


    mass->len-=1;
    if (mass->cap/2==mass->len && mass->cap!=4){
        int* old = mass->mass;
        mass->mass = realloc(mass->mass, sizeof(int)*(mass->cap)/2);
        if (mass->mass==NULL){
            mass->mass = old;
            mass->len+=1;
            return -1;
        } else{
            mass->cap = mass->cap/2;
        }
    }
    return 0;
}


int del_in(dmass* mass, int index){
    if (mass==NULL){
        return -1;
    }

    if (mass->len==0){
        return -1;
    }

    if (index<0 || index>=mass->len){
        return -1;
    }


    mass->len-=1;
    for (int i = index; i<mass->len; i++){
        mass->mass[i] = mass->mass[i+1];
    }
    if (mass->cap/2==mass->len && mass->cap!=4){
        int* old = mass->mass;
        mass->mass = realloc(mass->mass, sizeof(int)*(mass->cap)/2);
        if (mass->mass==NULL){
            mass->mass = old;
            mass->len+=1;
            return -1;
        } else{
            mass->cap = mass->cap/2;
        }
    }

    return 0;
}


int get(dmass* mass, int index, int* res){
    if (mass==NULL){
        return -1;
    }
    if (index<0 || index>=mass->len){
        return -1;
    }
    res[0] = mass->mass[index];
    return 0;
}


int del_mass(dmass* mass){
    if (mass==NULL){
        return -1;
    }
    free(mass->mass);
    mass->mass = NULL;
    mass->len = 0;
    mass->cap = 0;
    return 0;
}



