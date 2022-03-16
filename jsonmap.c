#include <string.h>

#define JSON_NULL ((void *) 0)

struct JSON_MAP_INFO{
    struct JSON_MAP_ELEMENT * start;
    unsigned int elements;
};

struct JSON_MAP_ELEMENT{
    char * key;
    void * thing;
    struct JSON_MAP_ELEMENT * next;
};

unsigned int getMapLength(struct JSON_MAP_INFO * map){
    return map->elements;
}

void * getKeyatIndex(struct JSON_MAP_INFO * map, unsigned int index){
    if(map == JSON_NULL) return JSON_NULL;
    if(index >= map->elements) return JSON_NULL;
    struct JSON_MAP_ELEMENT * current = map->start;
    for(int i = 0; i < index; i++){
        if(current->next == JSON_NULL) return JSON_NULL;
        current = current->next;
    }
    return current->key;

}

void * newMap(){
    struct JSON_MAP_INFO * i = malloc(sizeof(struct JSON_MAP_INFO));
    if(i == JSON_NULL) return JSON_NULL;
    i->elements = 0;
    i->start = JSON_NULL;
    return i;
}

void * getElementByKey(struct JSON_MAP_INFO * map, char * key){
    if(!(map && key)) return JSON_NULL;
    if(!map->elements) return JSON_NULL;


    struct JSON_MAP_ELEMENT * current = map->start;
    if(!strcmp(current->key, key)){
        return current->thing;
    }

    struct JSON_MAP_ELEMENT * previous = map->start;
    current = map->start->next;

    for(int i = 1; i < map->elements; i++){
        if(!strcmp(current->key, key)){
            return current->thing;
        }
    }
    return JSON_NULL;
}

void * getElementByIndex(struct JSON_MAP_INFO * map, unsigned int index){
    if(map == JSON_NULL) return JSON_NULL;
    if(index >= map->elements) return JSON_NULL;
    struct JSON_MAP_ELEMENT * current = map->start;
    for(int i = 0; i < index; i++){
        if(current->next == JSON_NULL) return JSON_NULL;
        current = current->next;
    }
    return current->thing;

}

int addElement(struct JSON_MAP_INFO * map, char * key, void * element){
    if(map == JSON_NULL) return JSON_NULL;
    unsigned int keylen = strlen(key) + 1;
    char * cpystring = malloc(keylen);
    if(cpystring == JSON_NULL) return 0;
    strcpy(cpystring, key);
    struct JSON_MAP_ELEMENT * newElement = malloc(sizeof(struct JSON_MAP_ELEMENT));
    if(newElement == JSON_NULL){
        free(cpystring);
        return 0;
    }
    newElement->key = cpystring;
    newElement->thing = element;
    newElement->next = map->start;
    map->elements++;
    map->start = newElement;
    return 1;

}

void * removeElementbyKey(struct JSON_MAP_INFO * map, char * key){
    if(!(map && key)) return JSON_NULL;
    if(!map->elements) return JSON_NULL;


    struct JSON_MAP_ELEMENT * current = map->start;
    if(!strcmp(current->key, key)){
        map->start = current->next;
        map->elements--;
        free(current->key);
        void * ret = current->thing;
        free(current);
        return ret;
    }

    struct JSON_MAP_ELEMENT * previous = map->start;
    current = map->start->next;

    for(int i = 1; i < map->elements; i++){
        if(!strcmp(current->key, key)){
            previous->next = current->next;
            map->elements--;
            free(current->key);
            void * ret = current->thing;
            free(current);
            return ret;
        }
    }
    return JSON_NULL;
}

void * removeElementbyIndex(struct JSON_MAP_INFO * map, unsigned int index){
    if(map == JSON_NULL) return JSON_NULL;
    if(index >= map->elements) return JSON_NULL;

    struct JSON_MAP_ELEMENT * current = map->start;
    if(!index){
        map->start = current->next;
        map->elements--;
        free(current->key);
        void * ret = current->thing;
        free(current);
        return ret;
    }

    struct JSON_MAP_ELEMENT * previous = map->start;
    current = map->start->next;

    for(int i = 1; i < index; i++){
        if(current->next == JSON_NULL) return JSON_NULL;
        current = current->next;
    }

    previous->next = current->next;
    map->elements--;
    free(current->key);
    void * ret = current->thing;
    free(current);
    return ret;
}

void deleteMap(struct JSON_MAP_INFO * map){
    if(map == JSON_NULL) return;
    for(int i = 0; i < map->elements; i++){
        JSONfreeThingRecursively(removeElementbyIndex(map, 0));
        if(map->start == JSON_NULL){
            return;
        }
    }
    return;
}