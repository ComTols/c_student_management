# Student Management
Diese Applikation beinhaltet ein Managementsystem zur Studentenverwaltung.
Es ermöglicht das Abspeichern und Einlesen persönlicher Daten, wie etwa Name, Geburtsdatum, Matrikelnummer usw., ebenso wie das Ausgeben fraglicher Daten in sortierter, strukturierter Form.

Es handelt sich um eine reine Konsolenanwendung. Daten zum Importieren müssen einer bestimmten From entsprechen, welche in der Dokumentation genauer beschrieben ist.
Die Datenbank wird lokal gespeichert. Es besteht die Möglichkeit, Backups und Version Controls beim Speichern zu erstellen.

Link zur GitHub-Repo: https://github.com/ComTols/c_student_management

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
### `list_mkList(): LinkedList`
Konstruktor zum erstellen einer verketteten Liste

Rückgabewert:
    `LinkedList`: Die verkettete Liste
---
### `list_mkItem(void *value): Item*`
Erstellt ein Element einer verketteten Liste mit bestimmten Wert.

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| value     | void* | Der Wert des Elements |

Rückgabewert:
    `Item*`: Pointer auf das Listenelement
---
### `list_unshift(LinkedList* list, void* value): int`
Fügt ein Element am Anfang hinzu und gibt die neue Länge zurück

| Parameter | Typ         | Beschreibung             |
|-----------|-------------|--------------------------|
| list      | LinkedList* | Die zu verändernde Liste |
| value     | void*       | Hinzuzufügendes Element  |

Rückgabewert:
    `int`: Neue Länge der Liste
---
### `list_push(LinkedList* list, void* value): int`
Fügt ein Element am Ende hinzu und gibt die neue Länge zurück

| Parameter | Typ         | Beschreibung             |
|-----------|-------------|--------------------------|
| list      | LinkedList* | Die zu verändernde Liste |
| value     | void*       | Hinzuzufügendes Element  |

Rückgabewert:
    `int`: Neue Länge der Liste
---
### `list_addAtIndex(LinkedList* list, void* value, int index): int`
Fügt ein Element an einer bestimmten Position hinzu und gibt die neue Länge zurück

| Parameter | Typ         | Beschreibung                             |
|-----------|-------------|------------------------------------------|
| list      | LinkedList* | Die zu verändernde Liste                 |
| value     | void*       | Hinzuzufügedes Element                   |
| index     | int         | Position, an der hinzugefügt werden soll |

Rückgabewert:
    `int`: Neue Länge der Liste
---
### `list_pop(LinkedList* list): void*`
Entfernt das letzte Element und gibt es zurück

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| list      | LinkedList* | Die zu verändernde Liste                 |

Rückgabewert:
    `void*`: Pointer auf das letzte Element der Liste
---
### `list_shift(LinkedList* list): void*`
Entfernt das erste Element und gibt es zurück

| Parameter | Typ   | Beschreibung          |
|-----------|-------|-----------------------|
| list      | LinkedList* | Die zu verändernde Liste                 |

Rückgabewert:
    `void*`: Pointer auf das erste Element der Liste
---
### `list_sort(LinkedList *list, int(*compare)(Item* first, Item* secound))`
Sortiert die Liste

| Parameter | Typ               | Beschreibung                          |
|-----------|-------------------|---------------------------------------|
| list      | LinkedList*       | Die zu verändernde Liste              |
| compare   | int(Item*, Item*) | Funktion zum vergleichen der Elemente |

Rückgabewert:
    `void`
---
### `list_get(LinkedList *list, int index): void*`
Gibt ein Element an einer bestimmten Stelle zurück

| Parameter | Typ         | Beschreibung                 |
|-----------|-------------|------------------------------|
| list      | LinkedList* | Die zu verändernde Liste     |
| index     | int         | Index des gesuchten Elements |

Rückgabewert:
    `void*`: Pointer auf das gesuchte Element
---
### `list_print(LinkedList *list)`
Gibt eine Liste auf der Konsole aus.

| Parameter | Typ   | Beschreibung           |
|-----------|-------|------------------------|
| list      | LinkedList* | Die auszugebende Liste |

Rückgabewert:
    `void`

---
# Quellen
Dieses Projekt basiert auf verschiedenen Quellen im Internet. Alle enthaltenden Dateien wurden von uns
selber geschrieben, basieren jedoch auf algorithmen und Strukturen, die sich bewährt haben.
Ebenso wurden verschiedene Codefragmente aus Recherchen zu bestimmten Themen verwendet.
Insbesondere die Umsetzung des Json-Interpreters, der Hash-Map und der Stringstreams basieren auf
Codes von StackOverflow und YouTube. Genaue Quellen können wir leider nicht nennen, da wir
den Code selber geschrieben und für unsere Bedürfnisse angepasst haben. Daher ist nicht 
mehr klar zu differenzieren, welcher Teil des Codes aus welcher Quelle kommt.
Es ist ein Gesamtwerk, das auf unseren eigenen Recherchen basiert.