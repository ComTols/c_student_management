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
Json *json_alloc_typeSize(char type, unsigned int n)
{
    Json *ret = malloc(sizeof(Json));
    ret->type = type;

    switch (type)
    {
        case JSON_STR:
            ret->val.s = "";
            break;
        case JSON_FLOAT:
            ret->val.f = 0.0f;
            break;
        case JSON_INT:
            ret->val.i = 0;
            break;
        case JSON_BOOL:
            ret->val.b = false;
            break;
        case JSON_LIST:
            ret->val.l = list_mkList(n);
            break;
        case JSON_OBJ:
            ret->val.o = map_mkMap(strHash, strCompKeys);
            break;
        case JSON_NULL:
        default:
            ret->type = JSON_NULL;
            ret->val.n = NULL;
            break;
    };

    return ret;
}

Json *json_alloc_type(char type)
{
    return json_alloc_typeSize(type, 0);
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

Json *json_list_get(Json *list, unsigned int idx)
{
    if (list->type != JSON_LIST || idx >= list->val.l.size)
    {
        return NULL;
    }

    return list_get(&list->val.l, idx);
}

Json *json_obj_get(Json *obj, char *key)
{
    if (obj->type != JSON_OBJ)
    {
        return NULL;
    }

    return map_get(&obj->val.o, key);
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

bool charIsNumber(char c) {
    return (c >= '0' && c <= '9') || c == '.' || c == '-';
}

Json json_readFileObj(FILE *fp)
{
    StringStream str = stream_mkStringStream();
    stream_readFile(&str, fp, 0);

    LinkedList stack = list_mkList();
    LinkedList keyStack = list_mkList();

    bool keyOpen = false;
    char *curKey;

    Json *curElement = NULL;
    Json *list = NULL;
    Json *obj = NULL;

    bool foundDecimal;

    unsigned int nextI;
    unsigned int objLength;

    for (unsigned int i = 0; i < str.size; i += objLength)
    {
        objLength = 1;

        char c = str.str[i];

        if (c == ' ' || c == '\n'|| c == '\r' || c == '\t' || c == ':')
        {
            // skip whitespace
            continue;
        }

        printf("%c ", c);

        bool valid = true;

        switch (c)
        {
            case '{':
                // start dictionary
                list_push(&stack, json_alloc_type(JSON_OBJ));

                // start key
                keyOpen = true;
                break;
            case '[':
                // start list
                list_push(&stack, json_alloc_type(JSON_LIST));
                break;
            case '"':
                // start string
                // find closing quote
                nextI = i + 1;
                while (nextI < str.size)
                {
                    if (str.str[nextI] == '"' && str.str[nextI - 1] != '\\')
                    {
                        break;
                    }
                    nextI++;
                }

                // set as key or element
                i++;
                objLength = nextI - i;
                if (keyOpen)
                {
                    // store as key
                    list_push(&keyStack, stream_substr(&str, i, objLength));
                    keyOpen = false;
                }
                else
                {
                    // store as string value
                    curElement = json_alloc_type(JSON_STR);
                    curElement->val.s = stream_substr(&str, i, objLength);
                }
                objLength++;

                break;
            case ',':
                // end element
                // determine if add to obj or list
                if (curElement)
                {
                    if (stack.size)
                    {
                        // add to top list or object
                        if (((Json *) list_get(&stack, stack.size - 1))->type == JSON_LIST)
                        {
                            json_list_add(list_get(&stack, stack.size - 1), curElement);
                        }
                        else
                        {
                            json_obj_put(list_get(&stack, stack.size - 1),
                                         list_pop(&keyStack), curElement);
                            keyOpen = true;
                        }
                    }
                    curElement = NULL;
                }

                break;
            case ']':
                // end list (pop from stack)
                list = list_pop(&stack);

                // add current element to the list
                if (curElement && list->type == JSON_LIST)
                {
                    json_list_add(list, curElement);
                }

                // set current element as the popped list
                curElement = list;
                list = NULL;

                break;
            case '}':
                // end object (pop from stack)
                obj = list_pop(&stack);

                // add current key-value pair to the object
                if (curElement && obj->type == JSON_OBJ)
                {
                    json_obj_put(obj, list_pop(&keyStack), curElement);
                }

                // set current element as the popped object
                curElement = obj;
                obj = NULL;

                break;
            default:
                if (charIsNumber(c))
                {
                    // parse number
                    foundDecimal = c == '.';

                    nextI = i + 1;
                    while (nextI < str.size && charIsNumber(str.str[nextI]))
                    {
                        if (str.str[nextI] == '.')
                        {
                            if (foundDecimal)
                            {
                                // invalid number
                                valid = false;
                                break;
                            }
                            foundDecimal = true;
                        }
                        else if (str.str[nextI] == '-')
                        {
                            // invalid number
                            valid = false;
                            break;
                        }

                        nextI++;
                    }

                    objLength = nextI - i;

                    if (!valid)
                    {
                        break;
                    }

                    // finished number
                    if (foundDecimal)
                    {
                        // store float
                        curElement = json_alloc_type(JSON_FLOAT);
                        curElement->val.f = atof(stream_substr(&str, i, objLength));
                    }
                    else
                    {
                        // store integer
                        curElement = json_alloc_type(JSON_INT);
                        curElement->val.i = atoi(stream_substr(&str, i, objLength));
                    }
                }
                else
                {
                    // parse keywords: true, false, null
                    char *substr4 = stream_substr(&str, i, 4);
                    char *substr5 = stream_substr(&str, i, 5);

                    if (!strcmp(substr4, JSON_NULL_S))
                    {
                        // null value
                        curElement = json_alloc_type(JSON_NULL);
                        objLength = 4;
                    }
                    else if (!strcmp(substr4, JSON_TRUE))
                    {
                        // true boolean value
                        curElement = json_alloc_type(JSON_BOOL);
                        curElement->val.b = true;
                        objLength = 4;
                    }
                    else if (!strcmp(substr5, JSON_FALSE))
                    {
                        // false boolean value
                        curElement = json_alloc_type(JSON_BOOL);
                        curElement->val.b = false;
                        objLength = 5;
                    }
                    else
                    {
                        // invalid token
                        valid = false;
                    }
                }

                break;
        };

        if (!valid)
        {
            printf(" invalid %d\n", i);
            break;
        }

        printf(" valid\n");
    }

    //stream_clear(&str);

    if (curElement)
    {
        char *test = json_dump(*((Json*)((Item *)curElement)->value));
        return *((Json*)((Item *)curElement)->value);
    }
    else
    {
        return json_null();
    }
}

Json json_read(char *path) {
    FILE  *f = fopen(path, "r");
    Json j = json_readFileObj(f);

    fclose(f);
    char *test = json_dump(j);
    return j;
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