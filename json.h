#include "linkedlist.h"
#include "map.h"
#include "stringstream.h"

//
// Created by Maximilian Schüller on 23.12.2022.
//

#ifndef C_STUDENT_MANAGEMENT_JSON_H
#define C_STUDENT_MANAGEMENT_JSON_H

typedef char bool;
#define false 0
#define true !0
#define JSON_TRUE "true"
#define JSON_FALSE "false"
#define JSON_NULL_S "null"

#define JSON_NULL (char)0
#define JSON_STR (char)1
#define JSON_FLOAT (char)2
#define JSON_INT (char)3
#define JSON_BOOL (char)4
#define JSON_LIST (char)5
#define JSON_OBJ (char)6

union json_types {
    void *n;
    char *s;
    float f;
    int i;
    bool b;
    LinkedList l;
    Map o;
};

typedef struct json {
    char type;
    union json_types val;
} Json;

Json json_mkJson(char type);
Json json_null();
Json json_string(char *val);
Json json_float(float val);
Json json_int(int val);
Json json_bool(bool val);
Json json_list(LinkedList val);
Json json_obj(Map val);

void json_list_add(Json *list, Json *val);
void json_list_push_null(Json *list);
void json_list_push_string(Json *list, char* val);
void json_list_push_int(Json *list, int val);
void json_list_push_float(Json *list, float val);

void json_obj_put(Json *obj, char *key, Json *val);
void json_obj_put_null(Json *obj, char *key);
void json_obj_put_string(Json *obj, char *key, char* val);
void json_obj_put_int(Json *obj, char *key, int val);
void json_obj_put_float(Json *obj, char *key, float val);

StringStream json_stringify(Json j, bool style, int tab, bool isInDic);
char* json_dump(Json j, int *n);

void json_free(Json *j);

#endif //C_STUDENT_MANAGEMENT_JSON_H
