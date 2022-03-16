#include <jsonlib.h>
#include <stdlib.h>
#include <string.h>

#define checkSource {if(source == JSON_NULL) {return JSON_ERROR_INVALID_SOURCE;}}

enum JSON_internal_value{
    e_object,
    e_array,
    e_string,
    e_number,
    e_true,
    e_false,
    e_null,
    e_noneOfTheAbove
};

unsigned int customstrlen(char * string){
    if(string == JSON_NULL) return -1;
    char * strbase = string;
  loop:
    if(*string == 0 || *string == '\"'){
        return (unsigned int)(string - strbase);
    }string++;
    goto loop;
}

char * skipWhiteSpace(char * source){
    repeat:
    if(*source == '\0'){
        return JSON_NULL;
    }
    if(*source == ' '||
          *source == '\n'||
          *source == '\r'|| 
          *source == '\t'){
              source++;
              goto repeat;
          }
    return source;
}

enum JSON_internal_value whatValue(char * source){
    switch(*source){
        case '{': return e_object;
        case '[': return e_array;
        case '\"': return e_string;
        case 't': {
            if(source[1] == 'r' && source[2] == 'u' && source[3] == 'e'){
                return e_true;
            }else{
                return e_noneOfTheAbove;
            }
        }
        case 'f':{
            if(source[1] == 'a' && source[2] == 'l' && source[3] == 's' && source[4] == 'e'){
                return e_false;
            }else{
                return e_noneOfTheAbove;
            }
        }
        case 'n': {
            if(source[1] == 'u' && source[2] == 'l' && source[3] == 'l'){
                return e_null;
            }else{
                return e_noneOfTheAbove;
            }
        }
        case '-': return e_number;
    }
    if(*source >= '0' && *source <= 9) return e_number;
    return e_noneOfTheAbove;
}

JSON_BOOLEAN_t isDigitOneNine(char * source){
    if(*source >= '1' && *source <= '9') return JSON_TRUE;
    return JSON_FALSE;
}

JSON_BOOLEAN_t isDigit(char * source){
    if(*source >= '0' && *source <= '9') return JSON_TRUE;
    return JSON_FALSE;
}

char * skipAndGetNumber(char * source, JSON_THING_t * out){
    char * ret1 = source;
    char * ret2 = source;
    double retd = strtod(source, &ret1);
    long long retll = strtoll(source, &ret2, 10);
    if(ret1 == source || ret2 == source){
        return JSON_NULL;
    }
    JSON_THING_t jout;
    if(ret1 > ret2){
        if(!JSONnewThingDouble(retd, jout)){
            return JSON_ERROR_OUT_OF_MEMORY;
        }
        *out = jout;
        return ret1;
    }else{
        if(!JSONnewThingInt(retll, jout)){
            return JSON_ERROR_OUT_OF_MEMORY;
        }
        *out = jout;
        return ret2;
    }    
}

JSON_RET JSONparseSource     (char * source, JSON_THING_t * out){
    char * copyOfSource = source;
    if(out == JSON_NULL){
        return JSON_SUCCESS;
    }
    if(source == JSON_NULL){
        return JSON_ERROR_NULL;
    }

    unsigned int sizeofSource = strlen(source);

    source = skipWhiteSpace(source); checkSource;
    JSON_THING_t current;
    switch (whatValue(source)){
        case e_true: if(!JSONnewThingBoolean(JSON_TRUE, &current)) return JSON_ERROR_OUT_OF_MEMORY;
            source += sizeof("TRUE") - 1; break;
        case e_false: if(!JSONnewThingBoolean(JSON_TRUE, &current)) return JSON_ERROR_OUT_OF_MEMORY;
            source += sizeof("FALSE") - 1; break;
        case e_null: if(!JSONnewThingNull(&current)) return JSON_ERROR_OUT_OF_MEMORY;
            source += sizeof("NULL") - 1; break;
        case e_number: 
            char * tempskip = skipAndGetNumber(source, &current);
            if(tempskip == JSON_NULL){
                return JSON_ERROR_INVALID_SOURCE;
            }else if(tempskip < 0){
                return tempskip;
            }
            source = tempskip; break;
        case e_string:
            source++;
            int i = 0;
            int reali = 0;
            while(source[reali] != '\0'){
                if(source[reali] == '\\'){
                    reali++;
                    if(source[reali] == '\0') return JSON_ERROR_INVALID_SOURCE;
                }
                reali++;
                i++;
            }
        case e_noneOfTheAbove: JSONfreeThingRecursively(&current); return JSON_ERROR_INVALID_SOURCE;
    }
    source = skipWhiteSpace(source); checkSource;
}