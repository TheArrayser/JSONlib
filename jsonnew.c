#include "jsonlib.h"
#include "jsonmap.h"
#include <string.h>
#include <stdlib.h>

#define checkOut {if(out == JSON_NULL){return JSON_SUCCESS;}}

JSON_RET JSONnewThingString (char * string, JSON_THING_t * out){
    checkOut;
    if(string == JSON_NULL){
        return JSON_ERROR_NULL;
    }
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.pointer = malloc(strlen(string)+1);
    if(ret->thing.pointer == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->type = JSON_e_STRING;
    strcpy(ret->thing.pointer, string);
    *out = ret;
    return JSON_SUCCESS;
}

JSON_RET JSONnewThingInt    (long long integer, JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.intvalue = integer;
    ret->type = JSON_e_INTEGER;
    *out = ret;
    return JSON_SUCCESS;
}

JSON_RET JSONnewThingBoolean(JSON_BOOLEAN_t boolean, JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.boolean = boolean;
    ret->type = JSON_e_BOOLEAN;
    *out = ret;
    return JSON_SUCCESS;
}

JSON_RET JSONnewThingDouble (double doubleval, JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.doubleval = doubleval;
    ret->type = JSON_e_DOUBLE;
    *out = ret;
    return JSON_SUCCESS;
}

JSON_RET JSONnewThingFloat  (float floatval, JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.doubleval = (double)floatval;
    ret->type = JSON_e_DOUBLE;
    *out = ret;
    return JSON_SUCCESS;
}

JSON_RET JSONnewThingNull   (JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->type = JSON_e_NULL;
    *out = ret;
    return JSON_SUCCESS;
}

//TODO
JSON_RET JSONnewEmptyObject (JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.pointer = newMap();
    if(ret->thing.pointer == JSON_NULL){
        free(ret);
        return JSON_ERROR_NULL;
    }

    ret->type = JSON_e_OBJECT;
    *out = ret;
    return JSON_SUCCESS;
}


JSON_RET JSONnewEmptyArray  (JSON_THING_t * out){
    checkOut;
    JSON_THING_t ret = malloc(sizeof(JSON_THING_t));
    if(ret == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
    ret->thing.pointer = newMap();
    if(ret->thing.pointer == JSON_NULL){
        free(ret);
        return JSON_ERROR_NULL;
    }

    ret->type = JSON_e_ARRAY;
    *out = ret;
    return JSON_SUCCESS;
}