//
// Created by Maximilian Schüller on 21.12.2022.
//

#include "map.h"

Map map_mkMap(int (*hashf)(void* key), int (*keycompare)(void *key1, void *key2)) {
    return map_mkMapOfSize(BUCKETS_COUNT, hashf, keycompare);
}

Map map_mkMapOfSize(int bucketsCount, int (*hashf)(void* key), int (*keycompare)(void *key1, void *key2)) {
    Map newMap;

    newMap.bucketsCount = bucketsCount;
    newMap.entrysCount = 0;
    newMap.buckets = calloc(bucketsCount,sizeof(Entry*));
    newMap.hashf = hashf;
    newMap.compKeys = keycompare;

    //Setzte initial alle Einträge auf Null
    for (int i = 0; i < bucketsCount; ++i) {
        newMap.buckets[i] = NULL;
    }

    return newMap;
}

void map_resize(Map *map) {
    //Neue Größe setzten, um workload zu verringern
    float bucketsCount = (float) map->bucketsCount;
    float entrysCount = (float) map->entrysCount;
    while (entrysCount/bucketsCount > MAX_WORKLOAD) {
        bucketsCount *= 2.0f;
    }

    Map newMap = map_mkMapOfSize(bucketsCount, map->hashf, map->compKeys);

    // Gehe durch alle Buckets
    for (int i = 0; i < map->bucketsCount; ++i) {
        Entry *element = map->buckets[i];
        //Gehe durch die verkettete Liste
        while (element) {
            map_put(&newMap, element->key, element->value);
            element = element->next;
        }
    }

    //Schreibe vorbereitete Buckte-Liste in übergebene Map
    Entry **tmpList = map->buckets;
    map->buckets = newMap.buckets;
    newMap.buckets = tmpList;
    newMap.bucketsCount = map->bucketsCount;

    //Gebe Speicher frei
    map_free(&newMap);

    //Update bucketCount
    map->bucketsCount = bucketsCount;
}

Entry *map_mkEntry(int hash, void *key, void* value) {
    Entry *newEntry = calloc(1,sizeof(Entry));

    newEntry->key = key;
    newEntry->hash = hash;
    newEntry->value = value;
    newEntry->next = NULL;

    return newEntry;
}

void map_put(Map* map, void *key, void *value) {
    //Index finden
    int hash = map->hashf(key);
    int index = abs(hash) % map->bucketsCount;

    Entry* newEntry = map_mkEntry(hash, key, value);

    if(map->buckets[index] != NULL) {
        //Liste existiert bereits
        Entry *element = map->buckets[index];

        //Finde Position oder füge am Ende ein
        while (element->next && hash > element->hash) {
            element = element->next;
        }

        if(hash == element->hash && !map->compKeys(key, element->key)) {
            //Keys sind gleich, überschreibe Value
            element->value = value;
        } else {
            //Keys unterschiedlich, einfügen
            Entry *tmp = element->next;
            element->next = newEntry;
            newEntry->next = tmp;
        }
    } else {
        //Liste existiert nicht, erstelle
        map->buckets[index] = newEntry;
        map->entrysCount++;
    }

    //Prüfe, ob überlastet
    float workload = map->entrysCount;
    workload /= (float) map->bucketsCount;
    if(workload > MAX_WORKLOAD) {
        map_resize(map);
    }
}

void *map_get(Map *map, void *key) {
    Entry *entry = map_getEntry(map, key);

    return entry ? entry->value : NULL;
}

Entry *map_getEntry(Map *map, void *key) {
    int hash = map->hashf(key);
    int index = abs(hash) % map->bucketsCount;

    if(map->buckets[index]) {
        Entry *element = map->buckets[index];

        while (element) {
            if (hash < element->hash) {
                //Optimierung durch sortierten Hash
                element = NULL;
                break;
            }

            if(hash == element->hash && !map->compKeys(key, element->key)) {
                //Keys sind gleich, gefunden
                break;
            }

            element = element->next;
        }

        return element;
    } else {
        //Nicht gefunden
        return NULL;
    }
}

void *map_remove(Map *map, void* key) {
    int hash = map->hashf(key);
    int index = abs(hash) % map->bucketsCount;

    if(map->buckets[index]) {
        Entry *element = map->buckets[index];
        Entry *previous = NULL;

        while (element) {
            if(hash < element->hash) {
                //Abbruch durch optimierung (sortierter hash)
                element = NULL;
                break;
            }

            if(hash == element->hash && !map->compKeys(key, element->key)) {
                //Keys sind gleich, gefunden
                break;
            }

            previous = element;
            element = element->next;
        }

        if(element) {
            //Lösche Eintrag
            void *value = element->value;

            if(previous) {
                //Lösche aus der Mitte/vom Ende
                previous->next = element->next;
            } else {
                //Lösche am Anfang
                map->buckets[index] = element->next;
            }

            //Lösche
            free(element);
            map->entrysCount--;
            return value;
        }
    }

    //Nicht gefunden
    return NULL;
}

void map_free(Map *map) {
    for (int i = 0; i < map->bucketsCount; ++i) {
        if(map->buckets[i]) {
            map_freeEntry(map->buckets[i]);
            free(map->buckets[i]);
        }
    }

    map->bucketsCount = 0;
    map->entrysCount = 0;
    free(map->buckets);
    //free(map);
}

void map_freeEntry(Entry *entry) {
    if(entry) {
        if(entry->next) {
            map_freeEntry(entry->next);
            free(entry->next);
        }

        //free(entry->key);
        //free(entry->value);
    }

}

void map_print(Map *map) {
    printf("#START MAP\n");
    for (int i = 0; i < map->bucketsCount; ++i) {
        printf("\t%i:\t", i);
        if(map->buckets[i]) {
            Entry *element = map->buckets[i];
            while (element) {
                printf("{Key: \"%s\", Value: \"%s\"} ", (char*)element->key, (char*)element->value);
                element = element->next;
            }
            printf("\n");
        } else {
            printf("EMPTY\n");
        }
    }
    printf("#END MAP");
}

int strHash(void* key) {
    int hash = 0;

    if(!key) {
        return hash;
    }

    char *strKey = (char*)key;
    int lenght = strlen(strKey);

    for (int i = 0; i < lenght; ++i) {
        hash = strKey[i] + 31 * hash;
    }

    return hash;
}

int strCompKeys(void *key1, void *key2) {
    if(!key1) {
        if(!key2) {
            return 0;
        }
        return -1;
    } else if(!key2) {
        return 1;
    }

    char *strKey1 = (char*)key1;
    char *strKey2 = (char*)key2;

    return strcmp(strKey1, strKey2);
}