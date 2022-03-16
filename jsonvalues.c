#include "jsonlib.h"
#include "jsonmap.h"
//#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define checkObject {if(object == JSON_NULL){return JSON_ERROR_NULL;}}
#define checkOut {if(out == JSON_NULL){return JSON_SUCCESS;}}

JSON_RET JSONThinggetType(JSON_THING_t object, JSON_TYPE_t * out){
    checkObject;
    checkOut;
    *out = object->type;
    return JSON_SUCCESS;
}

JSON_RET JSONThingtoString (JSON_THING_t object, char *         * out){
    if(object->type != JSON_e_STRING){
        return JSON_ERROR_INCORRECT_TYPE;
    }
    if(out != JSON_NULL){
        *out = object->thing.pointer;
        return JSON_SUCCESS;
    }else{
        return JSON_ERROR_NULL;
    }
    
}

JSON_RET JSONThingtoInt    (JSON_THING_t object, long long      * out){
    checkObject;
    checkOut;

    if(object->type == JSON_e_INTEGER){
        *out = object->thing.intvalue;
        return JSON_SUCCESS;
    }else if(object->type == JSON_e_DOUBLE){
        *out = (long long)(object->thing.doubleval);
        return JSON_SUCCESS;
    }
    return JSON_ERROR_INCORRECT_TYPE;
}

JSON_RET JSONThingtoBoolean(JSON_THING_t object, JSON_BOOLEAN_t * out){
    checkObject;
    checkOut;

    if(object->type == JSON_e_BOOLEAN){
        *out = object->thing.boolean;
        return JSON_SUCCESS;
    }
    return JSON_ERROR_INCORRECT_TYPE;
}

JSON_RET JSONThingtoDouble (JSON_THING_t object, double         * out){
    checkObject;
    checkOut;

    if(object->type == JSON_e_INTEGER){
        *out = (double)(object->thing.intvalue);
        return JSON_SUCCESS;
    }else if(object->type == JSON_e_DOUBLE){
        *out = object->thing.doubleval;
        return JSON_SUCCESS;
    }
    return JSON_ERROR_INCORRECT_TYPE;
}

JSON_RET JSONThingtoFloat  (JSON_THING_t object, float          * out){
    checkObject;
    checkOut;

    if(object->type == JSON_e_INTEGER){
        *out = (float)(object->thing.intvalue);
        return JSON_SUCCESS;
    }else if(object->type == JSON_e_DOUBLE){
        *out = (float)(object->thing.doubleval);
        return JSON_SUCCESS;
    }
    return JSON_ERROR_INCORRECT_TYPE;
}

JSON_RET JSONThingtoObject (JSON_THING_t object, JSON_THING_t   * out){
    checkObject;
    checkOut;

    if(object->type == JSON_e_OBJECT){
        *out = object->thing.pointer;
        return JSON_SUCCESS;
    }

    return JSON_ERROR_INCORRECT_TYPE;
}

JSON_RET JSONThingToArray  (JSON_THING_t object, JSON_ARRAY_t   * out){
    checkObject;
    checkOut;

    if(object->type == JSON_e_ARRAY){
        *out = object->thing.pointer;
        return JSON_SUCCESS;
    }

    return JSON_ERROR_INCORRECT_TYPE;
}

void * realocaddPage(void * buf, unsigned int * totalAllocatedminusOne){
    totalAllocatedminusOne += 512;
    return realloc(buf, totalAllocatedminusOne + 1);
}

JSON_BOOLEAN_t hasSize(unsigned int currentBuf, unsigned int totalAllocatedminusOne, unsigned int hasSize){
    if(totalAllocatedminusOne - currentBuf - hasSize > 0){
        return JSON_TRUE;
    }else{
        return JSON_FALSE;
    }
}

JSON_RET JSONThingToStringRecursivlyinternal(JSON_THING_t object, char * * out, unsigned int * currentBuf, unsigned int * totalAllocatedminusOne){
    
    switch (object->type){
    case JSON_e_BOOLEAN:
        if(object->thing.boolean == JSON_TRUE){
            if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("true")) == JSON_FALSE){
                *out = realocaddPage(*out, totalAllocatedminusOne);
            }
            strcpy(&((*out)[*currentBuf]), "true");
            *currentBuf += sizeof("true") - 1;
        }else{
            if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("false")) == JSON_FALSE){
                *out = realocaddPage(*out, totalAllocatedminusOne);
            }
            strcpy(&((*out)[*currentBuf]), "false");
            *currentBuf += sizeof("false") - 1;
        }
        return JSON_SUCCESS;
    case JSON_e_NULL:
        if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("null")) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        strcpy(&((*out)[*currentBuf]), "null");
        *currentBuf += sizeof("null") - 1;
        return JSON_SUCCESS;
    case JSON_e_STRING:
        unsigned int stringlength = strlen(object->thing.pointer);
        if(hasSize(*currentBuf, *totalAllocatedminusOne, stringlength+2) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        (*out)[*currentBuf] = '\"';
        (*currentBuf)++;
        strcpy(&((*out)[*currentBuf]), object->thing.pointer);
        *currentBuf += stringlength;
        (*out)[*currentBuf] = '\"';
        (*currentBuf)++;
        return JSON_SUCCESS;
    case JSON_e_DOUBLE:
        char * doublebuffer = malloc(100);
        if(doublebuffer == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
        sprintf(doublebuffer, "%f", object->thing.doubleval);
        unsigned int stringlength = strlen(doublebuffer);
        if(hasSize(*currentBuf, *totalAllocatedminusOne, stringlength) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        strcpy(&((*out)[*currentBuf]), doublebuffer);
        *currentBuf += stringlength;
        free(doublebuffer);
        return JSON_SUCCESS;
    case JSON_e_INTEGER:
        char * intbuffer = malloc(100);
        if(intbuffer == JSON_NULL) return JSON_ERROR_OUT_OF_MEMORY;
        sprintf(intbuffer, "%lld", object->thing.intvalue);
        unsigned int stringlength = strlen(intbuffer);
        if(hasSize(*currentBuf, *totalAllocatedminusOne, stringlength) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        strcpy(&((*out)[*currentBuf]), intbuffer);
        *currentBuf += stringlength;
        free(intbuffer);
        return JSON_SUCCESS;
    case JSON_e_OBJECT:
        if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("{")) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        (*out)[*currentBuf] = '{';
        (*currentBuf)++;
        unsigned int maplength = getMapLength(object->thing.pointer);
        for(int i = 0; i < maplength; i++){
            (*out)[*currentBuf] = '\"';
            (*currentBuf)++;
            char * keystring = getKeyatIndex(object->thing.pointer, i);
            unsigned int keystringLength = strlen(keystring);
            while(hasSize(*currentBuf, *totalAllocatedminusOne, keystringLength) == JSON_FALSE){
                *out = realocaddPage(*out, totalAllocatedminusOne);
            }
            strcpy(&((*out)[*currentBuf]), keystring);
            if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof(":")) == JSON_FALSE){
                *out = realocaddPage(*out, totalAllocatedminusOne);
            }
            (*out)[*currentBuf] = ':';
            (*currentBuf)++;
            JSON_RET possibleRet = JSONThingToStringRecursivlyinternal(object, out, currentBuf, totalAllocatedminusOne);
            if(possibleRet){
                return possibleRet;
            }
            if(i != maplength - 1){
                if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof(",")) == JSON_FALSE){
                *out = realocaddPage(*out, totalAllocatedminusOne);
            }
            (*out)[*currentBuf] = ',';
            (*currentBuf)++;
            }
        }

        if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("}")) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        (*out)[*currentBuf] = '}';
        (*currentBuf)++;
        return JSON_SUCCESS;

    case JSON_e_ARRAY:
        
        if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("[")) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        (*out)[*currentBuf] = '[';
        (*currentBuf)++;
        unsigned int maplength = getMapLength(object->thing.pointer);
        for(int i = 0; i < maplength; i++){
            JSON_RET possibleRet = JSONThingToStringRecursivlyinternal(object, out, currentBuf, totalAllocatedminusOne);
            if(possibleRet){
                return possibleRet;
            }
            if(i != maplength - 1){
                if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof(",")) == JSON_FALSE){
                *out = realocaddPage(*out, totalAllocatedminusOne);
            }
            (*out)[*currentBuf] = ',';
            (*currentBuf)++;
            }
        }

        if(hasSize(*currentBuf, *totalAllocatedminusOne, sizeof("]")) == JSON_FALSE){
            *out = realocaddPage(*out, totalAllocatedminusOne);
        }
        (*out)[*currentBuf] = ']';
        (*currentBuf)++;

        return JSON_SUCCESS;
    default:
        JSON_ERROR_INCORRECT_TYPE;
    }
}

JSON_RET JSONThingToStringRecursivly            (JSON_THING_t object, char * * out){
    checkObject;
    checkOut;
    char * buffer = malloc(512);
    unsigned int currentBuf = 0;
    unsigned int totalAllocatedminusOne = 512;

    JSON_RET ret = JSONThingToStringRecursivlyinternal(object, &buffer, &currentBuf, &totalAllocatedminusOne);
    if(ret != 0){
        free(buffer);
        return ret;
    }
    return JSON_SUCCESS;
}