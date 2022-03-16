#include "jsonlib.h"
#include "jsonmap.h"
#include <string.h>
#include <stdlib.h>

JSON_RET JSONremoveElementFromObject (JSON_THING_t object, char * key, JSON_THING_t * removed){
    if(object == JSON_NULL) return JSON_ERROR_NULL;
    if(key == JSON_NULL) return JSON_ERROR_KEY_NOT_FOUND;
    if(object->type != JSON_e_OBJECT) return JSON_ERROR_INCORRECT_TYPE;
    if(object->thing.pointer == JSON_NULL) return JSON_NULL;

    *removed = removeElementbyKey(object->thing.pointer, key);
    if(*removed == JSON_NULL){
        return JSON_ERROR_NULL;
    }else{
        return JSON_SUCCESS;
    }


    //struct JSON_OBJECT_INFO * oInfo = ((struct JSON_OBJECT_INFO *)object->thing.pointer);
    //unsigned int numberOfElements = oInfo->elements;
    //if(numberOfElements == 0) return JSON_ERROR_KEY_NOT_FOUND;
    //if(oInfo->start == JSON_NULL) return JSON_ERROR_KEY_NOT_FOUND;
//
    //if(strcmp(oInfo->start->key, key) == 0){
    //    struct JSON_OBJECT_ELEMENT * remove = oInfo->start;
    //    oInfo->start = oInfo->start->next;
    //    if(removed == JSON_NULL){
    //        JSON_THING_t queuedToRemove = remove->thing;
    //        free(remove);
    //        return JSONfreeThingRecursively(queuedToRemove);
    //    }
    //    *removed = remove->thing;
    //    free(remove);
    //    return JSON_SUCCESS;
    //}
//
    //struct JSON_OBJECT_ELEMENT * current = oInfo->start;
    //for(int i = 0; i < numberOfElements; i++){
    //    if(current->next == JSON_NULL) return JSON_ERROR_KEY_NOT_FOUND;
    //    if(strcmp(current->next->key, key) == 0){
    //        struct JSON_OBJECT_ELEMENT * remove = current->next;
    //        if(removed == JSON_NULL){
    //            JSON_THING_t queuedToRemove = remove->thing;
    //            free(remove);
    //            return JSONfreeThingRecursively(queuedToRemove);
    //        }
    //        *removed = remove->thing;
    //        return JSON_SUCCESS;
    //    }
    //    current = current->next;
    //}
    //return JSON_ERROR_KEY_NOT_FOUND;
}

JSON_RET JSONremoveElementFromArray  (JSON_THING_t object, unsigned int index, JSON_THING_t * removed){
    if(object == JSON_NULL) return JSON_ERROR_NULL;
    if(index < 0) return JSON_ERROR_KEY_NOT_FOUND;
    if(object->type != JSON_e_ARRAY) return JSON_ERROR_INCORRECT_TYPE;
    if(object->thing.pointer == JSON_NULL) return JSON_NULL;

    *removed = removeElementbyIndex(object->thing.pointer, index);
    if(*removed == JSON_NULL){
        return JSON_ERROR_NULL;
    }else{
        return JSON_SUCCESS;
    }
}

JSON_RET JSONfreeThingRecursively(JSON_THING_t object){
    if(object->type == JSON_e_DOUBLE || object->type == JSON_e_BOOLEAN || object->type == JSON_e_INTEGER || object->type == JSON_e_NULL){
        free(object);
        return JSON_SUCCESS;
    }else if(object->type == JSON_e_STRING){
        free(object->thing.pointer);
        free(object);
        return JSON_SUCCESS;
    }else if(object->type == JSON_e_ARRAY || object->type == JSON_e_OBJECT){
        deleteMap(object->thing.pointer);
        return JSON_SUCCESS;
    }else{
        return JSON_ERROR_INCORRECT_TYPE;
    }
}