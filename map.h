#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
/**
 * Diese Bibliothek basiert auf der Vorlesung im Fach <<Theoretische Informatik>> zum Thema Hashing und Hashing-maps.
 * Der Code wurde vollständig von uns geschrieben, basiert jedoch auf verschiedenen Quellen im Internet, die im
 * beiliegenden Referenzdokument aufgelistet sind.
 *
 * Wir haben uns für Hash-maps entschieden, da wir die Laufzeit unseres Programms verbessern , jedoch auch die
 * Vorgaben aus der Aufgabenstellung beachten wollten. Wir wurden dazu angehalten, verkettete Listen zu nutzen.
 * Diese haben eine Lesezugriffszeit von O(n), wohingegen ein Array die Lesezugriffszeit von O(1) hat.
 * Jedoch biete die verkettete Liste einen enormen Laufzeitvorteil beim einfügen und löschen von Elementen und ist
 * obendrein noch sparsam beim Speicher.
 * Beide Vorteile haben wir kombiniert und uns für eine Hash-map entschieden. Diese greift anhand eines Hashwertes mit
 * O(1) auf eine Verkettete Liste zu und durchsucht diese mit O(n) nach dem Element. Da die Listen deutlich kleiner sind,
 * ist die Laufzeit in Summe geringer.
 *
 * Somit haben wir verkettete Listen verwendet, wie es in der Aufgabenstellung gefordert ist, und haben diese
 * für unseren Use case optimiert.
 */

#ifndef C_STUDENT_MANAGEMENT_MAP_H
#define C_STUDENT_MANAGEMENT_MAP_H

#define BUCKETS_COUNT 16    //Standartgröße der Map
#define MAX_WORKLOAD 0.75   //Maximale Auslastung, um Zugriffszeit konstant zu halten

/**
 * Key Value Paar als verkettete Liste
 * Void-Pointer weil wir den Datentyp nicht kennen
 */
typedef struct entry {
    int hash;
    void *key;
    void *value;
    struct entry *next;
} Entry;

typedef struct map {
    int bucketsCount;
    int entrysCount;

    Entry **buckets;
    int (*hashf)(void* key);
    int (*compKeys)(void *key1, void *key2);
} Map;

// Initialisieren der Structs
Map map_mkMap(int (*hashf)(void* key), int (*compKeys)(void *key1, void *key2));
Map map_mkMapOfSize(int bucketsCount, int (*hashf)(void* key), int (*compKeys)(void *key1, void *key2));
Entry *map_mkEntry(int hash, void *key, void* value);

//Operationen auf Maps
void map_resize(Map *map);
void map_put(Map* map, void *key, void *value);
void *map_get(Map *map, void *key);
Entry *map_getEntry(Map *map, void *key);
void *map_remove(Map *map, void* key);

void map_free(Map *map);
void map_freeEntry(Entry *entry);

void map_print(Map *map);

/**
 * In diesem Projekt wird die Hashmap zum interpretieren von JSON-Dateien genutzt.
 * Im JSON-Format sind die Keys Strings, daher definiere ich hier eine Hashfunktion für Strings.
 * Die Structs sind jedoch so geschrieben, dass auch andere Datentypen verwendet werden könnten.
 */
int strHash(void* key);
int strCompKeys(void *key1, void *key2);

#endif //C_STUDENT_MANAGEMENT_MAP_H
