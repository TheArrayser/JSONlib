#define JSON_TRUE 1
#define JSON_FALSE 0
#define JSON_NULL ((void *) 0)

#define JSON_ERROR_INCORRECT_TYPE -1
#define JSON_ERROR_OUT_OF_MEMORY -2
#define JSON_ERROR_KEY_NOT_FOUND -3
#define JSON_ERROR_NULL -4
#define JSON_ERROR_INVALID_SOURCE -5
#define JSON_SUCCESS 0

typedef char JSON_BOOLEAN_t;
typedef struct JSON_ARRAY_INFO * JSON_ARRAY_t;
typedef enum JSON_TYPE JSON_TYPE_t;
typedef struct JSON_THING * JSON_THING_t;
typedef int JSON_RET;

enum JSON_TYPE{
    JSON_e_NULL,
    JSON_e_STRING,
    JSON_e_DOUBLE,
    JSON_e_INTEGER,
    JSON_e_OBJECT,
    JSON_e_BOOLEAN,
    JSON_e_ARRAY
};

struct JSON_THING{
    enum JSON_TYPE type;
    union thinga{
        void * pointer;
        //float floatval;
        double doubleval;
        long long intvalue;
        JSON_BOOLEAN_t boolean;
    } thing;
};

//struct JSON_ARRAY_INFO{
//    JSON_THING_t start;
//    unsigned int elements;
//};
//
//struct JSON_OBJECT_INFO{
//    struct JSON_OBJECT_ELEMENT * start;
//    unsigned int elements;
//};
//
//struct JSON_OBJECT_ELEMENT{
//    char * key;
//    JSON_THING_t thing;
//    struct JSON_OBJECT_ELEMENT * next;
//};

JSON_RET JSONparseSource     (char * source, JSON_THING_t * out);

JSON_RET JSONgetThingbyKey   (JSON_THING_t object, char * key, JSON_THING_t * out);
JSON_RET JSONgetThingbyIndex (JSON_THING_t object, unsigned int index, JSON_THING_t * out);

JSON_RET JSONThinggetType(JSON_THING_t object, JSON_TYPE_t * out);

JSON_RET JSONThingtoString (JSON_THING_t object, char *         * out);
JSON_RET JSONThingtoInt    (JSON_THING_t object, long long      * out);
JSON_RET JSONThingtoBoolean(JSON_THING_t object, JSON_BOOLEAN_t * out);
JSON_RET JSONThingtoDouble (JSON_THING_t object, double         * out);
JSON_RET JSONThingtoFloat  (JSON_THING_t object, float          * out);
//JSON_RET JSONThingtoNull   (JSON_THING_t object, void *         * out);
JSON_RET JSONThingtoObject (JSON_THING_t object, JSON_THING_t   * out);
JSON_RET JSONThingToArray  (JSON_THING_t object, JSON_ARRAY_t   * out);

JSON_RET JSONfreeThingRecursively(JSON_THING_t object);

JSON_RET JSONnewThingString (char * string, JSON_THING_t * out);
JSON_RET JSONnewThingInt    (long long integer, JSON_THING_t * out);
JSON_RET JSONnewThingBoolean(JSON_BOOLEAN_t boolean, JSON_THING_t * out);
JSON_RET JSONnewThingDouble (double doubleval, JSON_THING_t * out);
JSON_RET JSONnewThingFloat  (float floatval, JSON_THING_t * out);
JSON_RET JSONnewThingNull   (JSON_THING_t * out);
JSON_RET JSONnewEmptyObject (JSON_THING_t * out);
JSON_RET JSONnewEmptyArray  (JSON_THING_t * out);

//JSON_RET JSONnewThingByObject

JSON_RET JSONaddElementToObject     (JSON_THING_t object, char * key, JSON_THING_t value);
JSON_RET JSONaddElementToArray      (JSON_THING_t object, JSON_THING_t value);

JSON_RET JSONremoveElementFromObject (JSON_THING_t object, char * key, JSON_THING_t * removed);
JSON_RET JSONremoveElementFromArray  (JSON_THING_t object, unsigned int index, JSON_THING_t * removed);

JSON_RET JSONThingToStringRecursivly            (JSON_THING_t object, char * * out);

//{
//    "asd":123,
//    "uihsdf":4789,
//    "§":[
//        {"asd":123}
//    ]
//    "qwe":[
//        "asd",
//        123,
//        true,
//        null
//    ]
//}