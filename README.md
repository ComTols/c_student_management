# Student Management
Diese Applikation beinhaltet ein Managementsystem zur Studentenverwaltung.
Es ermöglicht das Abspeichern und Einlesen persönlicher Daten, wie etwa Name, Geburtsdatum, Matrikelnummer usw., ebenso wie das Ausgeben fraglicher Daten in sortierter, strukturierter Form.

Es handelt sich um eine reine Konsolenanwendung. Daten zum Importieren müssen einer bestimmten From entsprechen, welche in der Dokumentation genauer beschrieben ist.
Die Datenbank wird lokal gespeichert. Es besteht die Möglichkeit, Backups und Version Controls beim Speichern zu erstellen.

-----
## Dokumentation
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