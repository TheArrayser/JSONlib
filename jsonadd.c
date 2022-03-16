#include "jsonlib.h"
#include "jsonmap.h"

JSON_RET JSONaddElementToObject     (JSON_THING_t object, char * key, JSON_THING_t value){
    if(object == JSON_NULL) return JSON_ERROR_NULL;
    if(key == JSON_NULL) return JSON_ERROR_NULL;
    if(value == JSON_NULL) return JSON_ERROR_NULL;
    if(object->type != JSON_e_OBJECT) return JSON_ERROR_INCORRECT_TYPE;

    if(!addElement(object->thing.pointer, key, value)) return JSON_ERROR_OUT_OF_MEMORY;
    return JSON_SUCCESS;
}

JSON_RET JSONaddElementToArray      (JSON_THING_t object, JSON_THING_t value){
    if(object == JSON_NULL) return JSON_ERROR_NULL;
    char * key = JSON_NULL;
    if(value == JSON_NULL) return JSON_ERROR_NULL;
    if(object->type != JSON_e_ARRAY) return JSON_ERROR_INCORRECT_TYPE;

    if(!addElement(object->thing.pointer, key, value)) return JSON_ERROR_OUT_OF_MEMORY;
    return JSON_SUCCESS;
}