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
### `saveAsFile(students, path)`
Speichert ein Array an Studenteninformationen in die lokale Datenbank.

| Parameter | Typ      | Beschreibung                               |
|-----------|----------|--------------------------------------------|
| students  | Student* | Das zu speichernde Array an Studenteninfos |
| path      | char*    | Der Pfad zur Datenbank                     |

Rückgabewert: `void`

---
### `getFromFile(path): Student[]`
Liest alle Studenteninformationen aus der lokalen Datenbank und gibt diese als Array zurück.

| Parameter | Typ   | Beschreibung           |
|-----------|-------|------------------------|
| path      | char* | Der Pfad zur Datenbank |

Rückgabewert: `Student*`: Alle Informationen aus der Datenbank. Pointer auf erstes Element im Array.

---
### `encode(jsonString): Student[]`
Gibt ein Array an Studenteninformationen aus einem speziellen JSON-String zurück.
Die Formatierung des Strings ist stickt zu befolgen:
 - Keine Leerzeichen zwischen den Variablen
 - Keine Zeilenumbrüche (hier nur zur übersicht enthalten!)
 - Escape-Zeichen werden nicht berücksichtigt
 - Alle Keys werden kleingeschrieben
 - Der Typ `number` wird nur ganzzahlig angenommen
```json
{
  "anzahl":number,
  "studierende":[
    {
      "vname":string,
      "nname":string,
      "id":number,
      "gtag":{
        "tag": number,
        "monat":number,
        "jahr":number
      },
      "beginn":{
        "tag":number,
        "monat":number,
        "jahr":number
      },
      "ende":{
        "tag":number,
        "monat":number,
        "jahr":number
      }
    }
  ]
}
```
| Parameter  | Typ   | Beschreibung                       |
|------------|-------|------------------------------------|
| jsonString | char* | Zeichenfolge, aus der gelesen wird |

Rückgabewert: `Student*`: Die Studenteninformationen aus dem JSON-String.
Pointer auf das erste Element im Array.
---
### `jStudent(jsonString, indexPointer): Student`
Liest vom gesamten JSON-String ab dem übergebenen Index das folgende Objekt als Student-Struct ein
und gibt eine entsprechende Struct zurück.
Der Index muss dabei auf das Zeichen hinter der öffnenden geschweiften Klammer stehen.
Erwartet wird als erstes Symbol `"`.

Nach der Funktion zeigt der Index auf `{` des folgenden Studenten, oder auf `}` des JSON-Objekts.

| Parameter    | Typ   | Beschreibung                       |
|--------------|-------|------------------------------------|
| jsonString   | char* | Zeichenfolge, aus der gelesen wird |
| indexPointer | int*  | Pointer auf den aktuellen Index    |

Rückgabewert: `Student`: Die Studenteninformationen aus dem aktuellen Objekt als Struct.

---
### `jString(jsonString, indexPointer): char[]`
Liest vom gesamten JSON-String ab dem übergebenen Index den folgenden String ein
und gibt diesen als Char-Array zurück.
Der Index muss dabei auf das anführende `"` zeigen. Der String wird bis zum nächsten `"` gelesen.

Nach der Funktion zeigt der Index auf das abschließende `"` des Strings.

**ACHTUNG!** Es werden keine Escape-Zeichen berücksichtigt.

| Parameter    | Typ   | Beschreibung                       |
|--------------|-------|------------------------------------|
| jsonString   | char* | Zeichenfolge, aus der gelesen wird |
| indexPointer | int*  | Pointer auf den aktuellen Index    |

Rückgabewert: `char*`: Die gelesene Zeichenfolge als Char-Array.
Pointer auf das erste Element.

---
### `jDatum(jsonString, indexPointer): Datum`
Liest vom gesamten JSON-String ab dem übergebenen Index das folgende Objekt als Datum-Struct ein
und gibt eine entsprechende Struct zurück.
Der Index muss dabei auf die öffnenden geschweiften Klammer zeigen.
Erwartet wird als erstes Symbol `{`.

Nach der Funktion zeigt der Index auf die schließende geschweifte Klammer des jeweiligen JSON-Objekts.

| Parameter    | Typ   | Beschreibung                       |
|--------------|-------|------------------------------------|
| jsonString   | char* | Zeichenfolge, aus der gelesen wird |
| indexPointer | int*  | Pointer auf den aktuellen Index    |

Rückgabewert: `Datum`: Die Datumsinformationen aus dem aktuellen Objekt als Struct.

---
### `isNumber(c): boolean`
Gibt true zurück, wenn der übergebene Char eine Zahl ist.

| Parameter | Typ   | Beschreibung         |
|-----------|-------|----------------------|
| c         | char  | Der zu prüfende Char |

Rückgabewert: `bool`: `True` -> Char ist Ziffer; `False` -> Char ist keine Ziffer

---
### `potenz(int basis, int exponent): int`
Gibt die den Wert einer Potenz mal dem Faktor 10 zurück.

| Parameter | Typ | Beschreibung            |
|-----------|-----|-------------------------|
| basis     | int | Die Basis der Potenz    |
| exponent  | int | Der Exponent der Potenz |

Rückgabewert: `int`: Den Wert der Potenz mal 10
### `goToXY(x,y)`
Setzt den Cursor zum Schreiben in den Output-Stream auf die übergebene Position.

| Parameter | Typ | Beschreibung                        |
|-----------|-----|-------------------------------------|
| x         | int | Position auf der horizontalen Achse |
| y         | int | Position auf der vertikalen Achse   |

Rückgabewert:
`void`

---
### `menuAnzeige(MenuChoice): int`
Zeigt das Menü an und färbt den ausgewählten Menüpunkt rot.

| Parameter  | Typ | Beschreibung                      |
|------------|-----|-----------------------------------|
| MenuChoice | int | Aktuell ausgewählter Menüpunkt    |

Rückgabewert:
`int`: 0 bei Erfolg
---
### `Logo()`
Zeigt das DHBW-Logo in der Konsole an.
Rückgabewert:
`void`
---
### `CheckKey()`
Überprüft, ob eine Taste gedrückt wurde.

Rückgabewert:
`void`
