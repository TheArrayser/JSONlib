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

unsigned int getMapLength(struct JSON_MAP_INFO * map);

void * getKeyatIndex(struct JSON_MAP_INFO * map, unsigned int index);

void * newMap();

void * getElementByKey(struct JSON_MAP_INFO * map, char * key);

void * getElementByIndex(struct JSON_MAP_INFO * map, unsigned int index);

int addElement(struct JSON_MAP_INFO * map, char * key, void * element);

void * removeElementbyKey(struct JSON_MAP_INFO * map, char * key);

void * removeElementbyIndex(struct JSON_MAP_INFO * map, unsigned int index);

void deleteMap(struct JSON_MAP_INFO * map);