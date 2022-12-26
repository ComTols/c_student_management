# Student Management
Diese Applikation beinhaltet ein Managementsystem zur Studentenverwaltung.
Es ermöglicht das Abspeichern und Einlesen persönlicher Daten, wie etwa Name, Geburtsdatum, Matrikelnummer usw., ebenso wie das Ausgeben fraglicher Daten in sortierter, strukturierter Form.

Es handelt sich um eine reine Konsolenanwendung. Daten zum Importieren müssen einer bestimmten From entsprechen, welche in der Dokumentation genauer beschrieben ist.
Die Datenbank wird lokal gespeichert. Es besteht die Möglichkeit, Backups und Version Controls beim Speichern zu erstellen.

-----
## Dokumentation
### `main(argc, argv): int`
Das Program wird hier gestartet.

| Parameter | Typ    | Beschreibung         |
|-----------|--------|----------------------|
| argc      | int    | Anzahl der Argumente |
| argv      | char[] | Übergebene Argumente |

Rückgabewert:
    `int`: Exitcode

---
## Dokumentation (Konsole)
### `mkStudent(vname, nname, id, gtag, beginn, ende): Student*`
Konstruktor für die Struct Student zum einfachen Erstellen eines Datensatzes.

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| vname     | char* | Vorname               |
| nname     | char* | Nachname              |
| id        | int   | Matrikelnummer        |
| gtag      | Datum | Geburtstag            |
| beginn    | Datum | Imatrukulationsdatum  |
| ende      | Datum | Exmatrikulationsdatum |

Rückgabewert:
    `Student*`: Erstellter Student
---
### `mkDatum(int tag, int monat, int jahr): Datum`
Konstruktor für die Struct Datum zum einfachen Erstellen eines Datums.

| Parameter | Typ  | Beschreibung      |
|-----------|------|-------------------|
| tag       | int  | Tag               |
| monat     | int  | Monat (numerisch) |
| jahr      | int  | Jahr              |

Rückgabewert:
    `Datum`: Erstelltes Datum
---
### `goToXY(x, y)`
Verschiebt den Cursor auf der Konsole an die angegebene Position.

| Parameter | Typ   | Beschreibung |
|-----------|-------|--------------|
| x         | int   | Horizontale  |
| y         | int   | Vertikale    |

Rückgabewert: 
    `void`
---
### `logo(line)`
Gibt das Logo auf der Konsole aus.

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| line      | int*  | Zeile unter dem Logo  |

Rückgabewert:
    `void`
---
### `con_frame(height, firstLine)`
Gibt den Rahmen auf der Konsole aus.

| Parameter | Typ   | Beschreibung                                |
|-----------|-------|---------------------------------------------|
| height    | int   | Die Höhe des Fensters                       |
| fistLine  | int*  | Erste Zeile, in die geschrieben werden kann |

Rückgabewert:
    `void`
---
### `con_redraw(MenuItem *items, int length, int *pos)`
Gibt das Menü auf der Konsole aus.

| Parameter | Typ       | Beschreibung                 |
|-----------|-----------|------------------------------|
| items     | MenuItem* | Die auszugebenden Menüpunkte |
| length    | int       | Die Länge des Array <items>  |
| pos       | int*      | Die Zeigerposition           |

Rückgabewert:
    `void`
---
### `con_mkMenu(size): MenuItem*`
Konstruktor für das Menü.

| Parameter | Typ   | Beschreibung         |
|-----------|-------|----------------------|
| size      | int*  | Die Größe des Arrays |

Rückgabewert:
    `MenuItem*`: Pointer auf das erste Element im Array
---
### `con_input(items, length, pos, students)`
Fängt die Tastendrücke des Nutzers ab und ruft die entsprechende Methode auf.

| Parameter | Typ         | Beschreibung                        |
|-----------|-------------|-------------------------------------|
| items     | MenuItem*   | Alle Menüpunkte                     |
| length    | int         | Länge des Arrays <items>            |
| pos       | int*        | Position des Zeigers                |
| students  | LinkedList* | Liste aller gespeicherten Studenten |

Rückgabewert:
    `void`
---
### `con_clamp(in, max)`
Lässt einen Wert zwischen 0 und <max> bewegen.

| Parameter | Typ   | Beschreibung                       |
|-----------|-------|------------------------------------|
| in        | int*  | Zu beschränkende Variable          |
| max       | int   | Maximal zulässiger Wert (exklusiv) |

Rückgabewert:
    `void`
---
### `load(): LinkedList*`
Lädt alle Daten aus einer Datei.
> In dieser Funktion gibt es einen Bug!
> Nachdem die Werte aus der Datei gelesen wurden und in einen JSON-Tree konvertiert wurden,
> werden die Keys nicht korrekt behalten. Wahrscheinlich wird der Wert aus Versehen auf einen Pointer gesetzt.
> Alle Keys sind nach dem Beenden der Funktion json_read() gleich lang und unleserlich.
> Aus Zeitmangel konnten wir diesen Bug nicht fixen. Daher kann das Programm keine Daten beim
> öffnen automatisch laden.
> Um dies zu simulieren werden statische Daten am Anfang anstelle der Daten aus der Datei geladen.

Rückgabewert:
    `LinkedList*`: Pointer auf die Liste aller Studenten
---
### `save(data)`
Speichert die Liste der Studenten in einer Datei ab.

| Parameter | Typ         | Beschreibung          |
|-----------|-------------|-----------------------|
| data      | LinkedList* | Zu speichernde Daten  |

Rückgabewert:
    `void`
---
### `compareStudents(Item *first, Item *sec): int`
Vergleicht zwei Studenten anhand ihrer Nachnamen.
Gibt 0 bei Gleichheit, > 0 wenn das erste vor dem zweiten kommt und < 0 wenn das zweite vor dem ersten Kommt.

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| first     | Item* | Erster Student        |
| sec       | Item* | Zweiter Student       |

Rückgabewert:
    `int`: Vergleichswert
---

## Dokumentation (Json)
### `json_mkJson(type): Json`
Konstruktor der Struct Json zum schnellen Erstellen eines Json-Objekts des entsprechenden Typs.

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| type      | char  | Der Typ des Objekts   |

Rückgabewert:
    `Json`: Json-Objekt des entsprechenden Typs
---
### `json_null(): Json`
Erstellt ein Json-Objekt des Typs <null>.

Rückgabewert:
    `Json`: Json-Null-Objekt
---
### `json_string(val): Json`
Erstellt ein Json-Objekt des Typs <string>

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| val       | char* | Wert                  |

Rückgabewert:
    `Json`: Json-String-Objekt
---
### `json_float(val): Json`
Erstellt ein Json-Objekt des Typs <float>

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| val       | char* | Wert                  |

Rückgabewert:
`Json`: Json-Float-Objekt
---
### `json_int(val): Json`
Erstellt ein Json-Objekt des Typs <int>

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| val       | char* | Wert                  |

Rückgabewert:
`Json`: Json-Integer-Objekt
---
### `json_list(val): Json`
Erstellt ein Json-Objekt des Typs <list>

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| val       | char* | Wert                  |

Rückgabewert:
`Json`: Json-List-Objekt
---
### `json_list_add(list, val)`
Fügt ein Json-Objekt zu einer Json-Liste hinzu.

| Parameter | Typ   | Beschreibung         |
|-----------|-------|----------------------|
| list      | Json* | Liste zum hinzufügen |
| val | Json* | Hinzuzufügendes Json-Objekt |

Rückgabewert:
    `void`
---
### `json_obj_put(obj, key, val)`
Fügt ein Element einem Json-Objekt hinzu.

| Parameter | Typ   | Beschreibung                   |
|-----------|-------|--------------------------------|
| obj       | Json* | Objekt zu dem hinzugefügt wird |
| key       | char* | Schlüssel                      |
| val       | Json* | Hinzuzufügendes Json-Objekt    |

Rückgabewert:
    `void`
---
### `json_obj_put_string(obj, key, val)`
Fügt einen String zu einem Json-Objekt hinzu.

| Parameter | Typ   | Beschreibung                   |
|-----------|-------|--------------------------------|
| obj       | Json* | Objekt zu dem hinzugefügt wird |
| key       | char* | Schlüssel                      |
| val       | char* | Wert                           |

Rückgabewert:
    `void`
---
### `json_obj_put_int(obj, key, val)`
Fügt einen Integer zu einem Json-Objekt hinzu.

| Parameter | Typ   | Beschreibung                   |
|-----------|-------|--------------------------------|
| obj       | Json* | Objekt zu dem hinzugefügt wird |
| key       | char* | Schlüssel                      |
| val       | int   | Wert                           |

Rückgabewert:
    `void`
---
### `json_stringify(j): StringStream`
Gibt den Stringstream zu einem Json-Tree zurück.

| Parameter | Typ   | Beschreibung                     |
|-----------|-------|----------------------------------|
| j         | Json  | Zu interpretierdenes Json-Objekt |

Rückgabewert:
    `StringStream`: Zeichenkette im JSON-Format
---
### `json_dump(j): char*`
Gibt eine Zeichenkette im Json-Format eines Json-Trees zurück.

| Parameter | Typ   | Beschreibung                     |
|-----------|-------|----------------------------------|
| j         | Json  | Zu interpretierdendesJson-Objekt |

Rückgabewert:
    `char*`: Pointer auf den ersten Buchstaben der Zeichenkette
---
### `json_read(path): Json`
Liest eine Json-Datei ein.

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| path      | char* | Pfad zur Datei        |

Rückgabewert:
    `Json`: Das interpretierte Json-Objekt
---
### `json_obj_get(obj, key): Json*`
Gibt das Json-Objekt hinter dem übergebenene Key zurück.

| Parameter | Typ   | Beschreibung                    |
|-----------|-------|---------------------------------|
| obj       | Json* | Json-Objekt in dem gesucht wird |
| key       | char* | Schlüssel                       |

Rückgabewert:
    `Json*`: Pointer auf die interpretierte Json-Struktur
---
### `json_free(j)`
Gibt den Speicher frei.

| Parameter | Typ   | Beschreibung              |
|-----------|-------|---------------------------|
| j         | Json* | Zu löschendes Json-Objekt |

Rückgabewert:
    `void`
---
## Dokumentation (LinkedList)
LinkedList list_mkList();
Item *list_mkItem(void *value);

//Fügt ein Element am Anfang hinzu und gibt die neue Länge zurück
int list_unshift(LinkedList* list, void* value);
//Fügt ein Element am Ende hinzu und gibt die neue Länge zurück
int list_push(LinkedList* list, void* value);
//Fügt ein Element an einer bestimmten Position hinzu und gibt die neue Länge zurück
int list_addAtIndex(LinkedList* list, void* value, int index);

//Entfernt das letzte Element und gibt es zurück
void *list_pop(LinkedList* list);
//Entfernt das erste Element und gibt es zurück
void *list_shift(LinkedList* list);
//Entfernt ein Element an einer bestimmten Stelle und gibt es zurück
void *list_remove(LinkedList* list, int index);

//Apply a function simultaneously against two values of the array (from left-to-right) as to reduce it to a single value.
void list_reduce();
//Reverses the order of the elements of an array -- the first becomes the last, and the last becomes the first.
void list_reverse();
//Sorts the elements of an array.
void list_sort(LinkedList *list, int(*compare)(Item* first, Item* secound));

//Gibt ein Element an einer bestimmten Stelle zurück
void *list_get(LinkedList *list, int index);
void *list_getLast(LinkedList *list);
void *list_getFirst(LinkedList *list);

void list_print(LinkedList *list);

## Dokumentation (Map)
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

## Dokumentation (StringStream)
StringStream stream_mkStringStream();
StringStream stream_mkStringStreamSize(int size);
StringStream stream_mkStringStreamFromString(char *str);

char stream_increase(StringStream *stream, int inc);
int stream_available(StringStream *stream);
void stream_fprintf(StringStream *stream, const char *format, ...);
void stream_read(StringStream *stream, void *data, int length);
void stream_cursorBackwarts(StringStream *stream, int length);

void stream_readFile(StringStream *stream, FILE *file, int length);
void stream_writeFile(StringStream *stream, FILE *file, int first, int last);

void stream_clear(StringStream *stream);
void stream_print(StringStream *stream);
void stream_printFull(StringStream *stream);

char *stream_substr(StringStream *s, unsigned int i, int n);

---
# Quellen
Diese Projekt basiert auf verschiedenen Quellen im Internet. Alle enthaltenden Dateien wurden von uns
selber geschrieben, basieren jedoch auf algorithmen und Strukturen, die sich bewährt haben.
Ebenso wurden verschiedene Codefragmente aus Recherchen zu bestimmten Themen verwendet.
Insbesondere die Umsetzung des Json-Interpreters, der Hash-Map und der Stringstreams basieren auf
Codes von StackOverflow und YouTube. Genaue Quellen können wir leider nicht nennen, da wir
den Code selber geschrieben und für unsere Bedürfnisse angepasst haben. Daher ist nicht 
mehr klar zu differenzieren, welcher Teil des Codes aus welcher Quelle kommt.
Es ist ein Gesamtwerk, das auf unseren eigenen Recherchen basiert.