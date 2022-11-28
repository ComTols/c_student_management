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
### `saveAsFile(students, path): void`
Speichert ein Array an Studenteninformationen in die lokale Datenbank.

| Parameter | Typ       | Beschreibung                               |
|-----------|-----------|--------------------------------------------|
| students  | Student[] | Das zu speichernde Array an Studenteninfos |
| path      | char[]    | Der Pfad zur Datenbank                     |

Rückgabewert: `void`

---
### `getFromFile(path): Student[]`
Liest alle Studenteninformationen aus der lokalen Datenbank und gibt diese als Array zurück.

| Parameter | Typ    | Beschreibung           |
|-----------|--------|------------------------|
| path      | char[] | Der Pfad zur Datenbank |

Rückgabewert: `Student[]`: Alle Informationen aus der Datenbank als Array