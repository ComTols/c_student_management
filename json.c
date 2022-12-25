//
// Created by Maximilian Schüller on 23.12.2022.
//
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "stringstream.h"
#include "map.h"

#include "json.h"

Json json_mkJson(char type) {
    Json newJson;
    newJson.type = type;

    switch (type) {
        case JSON_NULL:
            newJson.val.n = NULL;
            break;
        case JSON_STR:
            newJson.val.s = "";
            break;
        case JSON_FLOAT:
            newJson.val.f = 0.0f;
            break;
        case JSON_INT:
            newJson.val.i = 0;
            break;
        case JSON_BOOL:
            newJson.val.b = false;
            break;
        case JSON_LIST:
            newJson.val.l = list_mkList();
            break;
        case JSON_OBJ:
            newJson.val.o = map_mkMap(strHash,strCompKeys);
            break;
    }
    return newJson;
}
Json json_null() {
    return json_mkJson(JSON_NULL);
}
Json json_string(char *val) {
    Json newJson = json_mkJson(JSON_STR);

    newJson.val.s = calloc(strlen(val)+1, sizeof(char ));
    strcpy(newJson.val.s, val);

    return newJson;
}
Json json_float(float val) {
    Json newJson = json_mkJson(JSON_FLOAT);

    newJson.val.f = val;

    return newJson;
}
Json json_int(int val) {
    Json newJson = json_mkJson(JSON_INT);

    newJson.val.i = val;

    return newJson;
}
Json json_bool(bool val) {
    Json newJson = json_mkJson(JSON_BOOL);

    newJson.val.b = val;

    return newJson;
}
Json json_list(LinkedList val) {
    Json newJson = json_mkJson(JSON_LIST);

    newJson.val.l = val;

    return newJson;
}
Json json_obj(Map val) {
    Json newJson = json_mkJson(JSON_OBJ);

    newJson.val.o = val;

    return newJson;
}

void json_list_add(Json *list, Json *val) {
    list_push(&list->val.l, (void *)val);
}
void json_list_push_null(Json *list) {
    Json *val = calloc(1, sizeof(Json));
    *val = json_null();

    json_list_add(list, val);
}
void json_list_push_string(Json *list, char* val) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_string(val);

    json_list_add(list, jval);
}
void json_list_push_int(Json *list, int val) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_int(val);

    json_list_add(list, jval);
}
void json_list_push_float(Json *list, float val) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_float(val);

    json_list_add(list, jval);
}

void json_obj_put(Json *obj, char *key, Json *val) {
    map_put(&obj->val.o, (void *)key, (void *)val);
}
void json_obj_put_null(Json *obj, char *key) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_null();

    json_obj_put(obj, key, jval);
}
void json_obj_put_string(Json *obj, char *key, char* val) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_string(val);

    json_obj_put(obj, key, jval);
}
void json_obj_put_int(Json *obj, char *key, int val) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_int(val);

    json_obj_put(obj, key, jval);
}
void json_obj_put_float(Json *obj, char *key, float val) {
    Json *jval = calloc(1, sizeof(Json));
    *jval = json_float(val);

    json_obj_put(obj, key, jval);
}

StringStream json_stringify(Json j) {
    StringStream s = stream_mkStringStream();

    switch (j.type) {
        case JSON_OBJ:
            stream_fprintf(&s, "{");
            Map *obj = &j.val.o;
            for (int bucket = 0; bucket < obj->bucketsCount; ++bucket) {
                if(obj->buckets[bucket]) {
                    Entry *current = obj->buckets[bucket];
                    while (current) {
                        char* key = (char*) current->key;
                        Json* value = (Json*) current->value;

                        stream_fprintf(&s, "\"%s\":%s,", key, json_stringify(*value).str);
                        current = current->next;
                    }
                }
            }
            stream_cursorBackwarts(&s, 1);
            stream_fprintf(&s, "}");
            break;
        case JSON_LIST:
            stream_fprintf(&s, "[");
            LinkedList *list = &j.val.l;
            Item *current = list->head;

            while (current) {
                Json *value = (Json*)current->value;


                stream_fprintf(&s, "%s,", json_stringify(*value).str);

                current = current->next;
            }
            stream_cursorBackwarts(&s, 1);
            stream_fprintf(&s, "]");
            break;
        case JSON_NULL:
            stream_fprintf(&s, JSON_NULL_S);
            break;
        case JSON_BOOL:
            stream_fprintf(&s, "%s", j.val.b ? JSON_TRUE : JSON_FALSE);
            break;
        case JSON_STR:
            stream_fprintf(&s, "\"%s\"", j.val.s);
            break;
        case JSON_INT:
            stream_fprintf(&s, "%d", j.val.i);
            break;
        case JSON_FLOAT:
            stream_fprintf(&s, "%f", j.val.f);
            break;
    }
    return s;
}

char* json_dump(Json j) {
    //StringStream s = json_stringify(j, false, 0, false);
    StringStream s = json_stringify(j);

    //fusch(&s);

    char *string = calloc(s.size + 1, sizeof(char));
    memcpy(string, s.str, s.size+1);
    stream_clear(&s);
    return string;
}

void json_free(Json *j) {
    if(j->type == JSON_STR) {
        //free(&j->val.s);
    } else if(j->type == JSON_LIST) {
        Item* current = j->val.l.head;

        while (current) {
            json_free((Json*) current->value);
            current = current->next;
        }
        //TODO: Free list
    } else if(j->type == JSON_OBJ) {
        for (int i = 0; i < j->val.o.bucketsCount; ++i) {
            Entry *current = j->val.o.buckets[i];
            json_free((Json*) current->value);
        }
        //TODO: Free map
    }
}