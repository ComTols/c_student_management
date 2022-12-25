//
// Created by Justin Kreuzmann on 23.12.2022.
//

#include "console.h"

COORD coord = { 0, 0 };
void con_newData();
void con_editData();
void con_countData();
void con_showData();
void con_showDataFull();
void con_deleteData();

LinkedList STUDENTS;

Student *mkStudent(char *vname, char *nname, int id, Datum gtag, Datum beginn, Datum ende) {
    Student *s = calloc(1, sizeof(Student));
    s->vname = vname;
    s->nname = nname;
    s->id = id;
    s->gtag = gtag;
    s->beginn = beginn;
    s->ende = ende;

    return s;
}

Datum mkDatum(int tag, int monat, int jahr) {
    Datum d;
    if(tag > 31 || tag <= 0) {
        tag = 1;
        printf("NANANA!");
    }
    d.tag = tag;
    if(monat > 31 || monat <= 0) {
        monat = 1;
        printf("Das Problem sitzt meistens vor dem Rechner!");
    }
    d.monat = monat;
    if(jahr <= 0) {
        jahr = 2000;
        printf("Fluxkompensator aktiviert!");
    }
    d.jahr = jahr;

    return d;
}

void goToXY(int x, int y) {
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void logo(int *line){
    goToXY(22, *line);
    printf(" (            )                       \n");
    goToXY(22, ++*line);
    printf(" )\\ )      ( /(       (      (  (     \n");
    goToXY(22, ++*line);
    printf("(()/(      )\\())    ( )\\     )\\))(   '\n");
    goToXY(22, ++*line);
    printf(" /(_))    ((_)\\     )((_)   ((_)()\\ ) \n");
    goToXY(22, ++*line);
    printf("(_))_      _((_)   ((_)_    _(())\\_)()\n");
    goToXY(22, ++*line);
    printf(" |   \\    | || |    | _ )   \\ \\((_)/ /\n");
    goToXY(22, ++*line);
    printf(" | |) |   | __ |    | _ \\    \\ \\/\\/ / \n");
    goToXY(22, ++*line);
    printf(" |___/    |_||_|    |___/     \\_/\\_/  \n");
    ++*line;
}

void con_frame(int height, int* firstLine) {
    printf("\33[?25l");
    system("cls");

    //Y-Position
    int y = 1;

    logo(&y);
    y++;

    //Kopf
    goToXY(17, y);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    *firstLine = y + 2;
    y+= height;

    //Fuß
    goToXY(17, ++y);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    //Ende
    goToXY(0,++y);
}

void con_redraw(MenuItem *items, int length, int *pos) {
    //Aktiviere Farben
    printf("\33[?25l");
    system("cls");

    //Y-Position
    int y = 1;

    logo(&y);
    y++;

    //Kopf
    goToXY(17, y);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    y+=2;

    //Menü
    for (int i = 1; i <= length; ++i) {
        goToXY(26, y);
        if(i - 1 == *pos) {
            //Färben
            printf("\033[0;31m");
            goToXY(23, y);
            printf("-> ");
        }
        printf("%d. %s", i, items[i-1].name);
        printf("\033[0m");
        y += 2;
    }

    //Fuß
    goToXY(17, y);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    goToXY(17, ++y);
    printf("ESC zum speichern und beenden");

    //Ende
    goToXY(0,++y);
}

MenuItem *con_mkMenu(int *size) {
    *size = 6;
    int s = *size;

    MenuItem *m = calloc(s, sizeof(MenuItem));

    char *name = "Student eintragen";
    m[0].name = name;
    m[0].callback = con_newData;

    m[1].name = "Student bearbeiten";
    m[1].callback = con_editData;

    m[2].name = "Anzahl der Studenten";
    m[2].callback = con_countData;

    m[3].name = "Zeige Student";
    m[3].callback = con_showData;

    m[4].name = "Zeige alle Studenten";
    m[4].callback = con_showDataFull;

    m[5].name = "L\x94sche Student";
    m[5].callback = con_deleteData;

    return m;
}

void con_input(MenuItem *items,int length, int *pos, LinkedList *students) {

    Student* head = (Student *)students->head->value;
    Student* head2 = (Student *)STUDENTS.head->value;


    //Warte auf Input
    int key = getch();

    //Tasten W, w, S, s, ArrowUp, ArrowDown
    switch (key) {
        case 244:
            //244 wir ausgelöst, wenn Sondertasten verwendet werden
            key = getch();
        case 72:
        case 87:
        case 119:
            //ArrowUp
            *pos -=1;
            con_clamp(pos,length);
            con_redraw(items,length,pos);
            printf("%d", *pos);
            break;
        case 80:
        case 83:
        case 115:
            //ArrowDown
            *pos +=1;
            con_clamp(pos,length);
            con_redraw(items,length,pos);
            printf("%d", *pos);
            break;
        case 13:
            //Enter
            items[*pos].callback(students);
            break;
        case 27:
            //ESC
            //TODO: Speichern
            save(students);
            exit(0);
            break;
    }
}

void con_clamp(int *in, int max) {
    if (*in <= -1) {
        *in = max - 1;
    }
    if(*in >= max) {
        *in = 0;
    }
}

void con_newData(LinkedList *student) {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Vorname: ");
    char *vname = calloc(100, sizeof(char));
    scanf("%s99", vname);

    goToXY(22,(y += 2));
    printf("Nachname: ");
    char *nname = calloc(100, sizeof(char));;
    scanf("%s99", nname);

    goToXY(22,(y += 2));
    printf("ID: ");
    int id;
    scanf("%d", &id);

    con_frame(height, &y);
    goToXY(22,y);
    printf("Geburtstag:");

    goToXY(22,(y += 2));
    printf("Tag: ");
    int gtagTag;
    scanf("%d", &gtagTag);

    goToXY(22,(y += 2));
    printf("Monat: ");
    int gtagMonat;
    scanf("%d", &gtagMonat);

    goToXY(22,(y += 2));
    printf("Jahr: ");
    int gtagJahr;
    scanf("%d", &gtagJahr);

    Datum gTag = mkDatum(gtagTag, gtagMonat, gtagJahr);

    con_frame(height, &y);
    goToXY(22,y);
    printf("Beginn:");

    goToXY(22,(y += 2));
    printf("Tag: ");
    int beginnTag;
    scanf("%d", &beginnTag);

    goToXY(22,(y += 2));
    printf("Monat: ");
    int beginnMonat;
    scanf("%d", &beginnMonat);

    goToXY(22,(y += 2));
    printf("Jahr: ");
    int beginnJahr;
    scanf("%d", &beginnJahr);

    Datum beginn = mkDatum(beginnTag, beginnMonat, beginnJahr);

    con_frame(height, &y);
    goToXY(22,y);
    printf("Ende:");

    goToXY(22,(y += 2));
    printf("Tag: ");
    int endeTag;
    scanf("%d", &endeTag);

    goToXY(22,(y += 2));
    printf("Monat: ");
    int endeMonat;
    scanf("%d", &endeMonat);

    goToXY(22,(y += 2));
    printf("Jahr: ");
    int endeJahr;
    scanf("%d", &beginnJahr);

    Datum ende = mkDatum(endeTag, endeMonat, endeJahr);

    con_frame(height, &y);
    goToXY(22,y);
    printf("Moechten Sie folgenden Studenten speichern?");

    goToXY(22,(y += 2));
    printf("Vorname: %s", vname);

    goToXY(22,(y += 2));
    printf("Nachname: %s", nname);

    goToXY(22,(y += 2));
    printf("ID: %d", id);

    goToXY(22,(y += 2));
    printf("Geburtsdatum: %d.%d.%d", gtagTag, gtagMonat, gtagJahr);

    goToXY(22,(y += 2));
    printf("Beginn: %d.%d.%d", beginnTag, beginnMonat, beginnJahr);

    goToXY(22,(y += 2));
    printf("Ende: %d.%d.%d", endeTag, endeMonat, endeJahr);

    goToXY(22,(y += 2));
    printf("Druecken Sie j um zu bestaetigen...");

    if(getch() == 106) {
        Student *newStudent = mkStudent(vname, nname, id, gTag, beginn, ende);
        list_push(student, newStudent);
        list_sort(student, compareStudents);
        goToXY(22,(y += 2));
        printf("Gespeichert! Weiteren hinzufuegen -> Enter; Menue -> Arrow");
    } else {
        goToXY(22,(y += 2));
        printf("Verworfen! Erneut versuchen -> Enter; Menue -> Arrow");
    }
}
void con_editData(LinkedList *student) {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Bitte geben Sie die ID des zu bearbeitenden Studenten ein:");
    goToXY(22,y+1);
    int id;
    scanf("%d", &id);

    Item *current = student->head;

    while (current) {
        if (((Student*)current->value)->id == id) {
            break;
        }
        current = current->next;
    }

    if(current) {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Folgende Informationen wurden gefunden:");

        goToXY(22,(y += 2));
        printf("[1] Vorname: %s\t\t[2] Nachname: %s", ((Student*)current->value)->vname, ((Student*)current->value)->nname);

        goToXY(22,(y += 2));
        printf("[3] ID: %d", ((Student*)current->value)->id);

        goToXY(22,(y += 2));
        printf("[4] Geburtstag: %d.%d.%d", ((Student*)current->value)->gtag.tag, ((Student*)current->value)->gtag.monat, ((Student*)current->value)->gtag.jahr);

        goToXY(22,(y += 2));
        printf("[5] Beginn: %d.%d.%d", ((Student*)current->value)->beginn.tag, ((Student*)current->value)->beginn.monat, ((Student*)current->value)->beginn.jahr);

        goToXY(22,(y += 2));
        printf("[6] Ende: %d.%d.%d", ((Student*)current->value)->ende.tag, ((Student*)current->value)->ende.monat, ((Student*)current->value)->ende.jahr);

        goToXY(22,(y += 2));
        printf("Was moechten Sie bearbeiten?");

        int key = getch();
        con_frame(height, &y);
        goToXY(22,y);
        switch (key) {
            case 49:
                printf("Geben Sie den neuen Vornamen ein:");
                char *vname = calloc(100, sizeof(char ));
                scanf("%s", vname);
                ((Student*)current->value)->vname = vname;
                break;
            case 50:
                printf("Geben Sie den neuen Nachnamen ein:");
                char *nname = calloc(100, sizeof(char ));
                scanf("%s", nname);
                ((Student*)current->value)->nname = nname;
                break;
            case 51:
                printf("Geben Sie die neue ID ein:");
                int id = 0;
                scanf("%d", &id);
                ((Student*)current->value)->id = id;
                break;
            case 52:
                printf("Geben Sie das neue Geburtsdatum ein:");

                goToXY(22,(y += 2));
                printf("Tag: ");
                int gday = 0;
                scanf("%d", &gday);

                goToXY(22,(y += 2));
                printf("Monat: ");
                int gmonth = 0;
                scanf("%d", &gmonth);

                goToXY(22,(y += 2));
                printf("Jahr: ");
                int gyear = 0;
                scanf("%d", &gyear);


                ((Student*)current->value)->gtag.tag = gday;
                ((Student*)current->value)->gtag.monat = gmonth;
                ((Student*)current->value)->gtag.jahr = gyear;
                break;
            case 53:
                printf("Geben Sie das neue Startdatum ein:");

                goToXY(22,(y += 2));
                printf("Tag: ");
                int sday = 0;
                scanf("%d", &sday);

                goToXY(22,(y += 2));
                printf("Monat: ");
                int smonth = 0;
                scanf("%d", &smonth);

                goToXY(22,(y += 2));
                printf("Jahr: ");
                int syear = 0;
                scanf("%d", &syear);


                ((Student*)current->value)->beginn.tag = sday;
                ((Student*)current->value)->beginn.monat = smonth;
                ((Student*)current->value)->beginn.jahr = syear;
                break;
            case 54:
                printf("Geben Sie das neue Enddatum ein:");

                goToXY(22,(y += 2));
                printf("Tag: ");
                int day = 0;
                scanf("%d", &day);

                goToXY(22,(y += 2));
                printf("Monat: ");
                int month = 0;
                scanf("%d", &month);

                goToXY(22,(y += 2));
                printf("Jahr: ");
                int year = 0;
                scanf("%d", &year);


                ((Student*)current->value)->ende.tag = day;
                ((Student*)current->value)->ende.monat = month;
                ((Student*)current->value)->ende.jahr = year;
                break;
        }

        goToXY(22,(y += 2));
        printf("Uebernommen! Weiteren aendern -> Enter; Menue -> Arrow");
    } else {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Es wurde nichts gefunden!");

        goToXY(22,(y += 2));
        printf("Erneut versuchen -> Enter; Menue -> Arrow");
    }

}
void con_countData(LinkedList *student) {
    int y = 0;
    int height = 5;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Aktuell sind %d Datensaetze gespeichert.", student->size);

    goToXY(22,(y += 2));
    printf("Erneut zaehlen -> Enter; Menue -> Arrow");
}
void con_showData(LinkedList *student) {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Bitte geben Sie die ID des Studenten ein:");
    goToXY(22,y+1);
    int id;
    scanf("%d", &id);

    Item *current = student->head;

    while (current) {
        if (((Student*)current->value)->id == id) {
            break;
        }
        current = current->next;
    }

    if(current) {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Folgende Informationen wurden gefunden:");

        goToXY(22,(y += 2));
        printf("Vorname: %s\t\tNachname: %s", ((Student*)current->value)->vname, ((Student*)current->value)->nname);

        goToXY(22,(y += 2));
        printf("ID: %d", ((Student*)current->value)->id);

        goToXY(22,(y += 2));
        printf("Geburtstag: %d.%d.%d", ((Student*)current->value)->gtag.tag, ((Student*)current->value)->gtag.monat, ((Student*)current->value)->gtag.jahr);

        goToXY(22,(y += 2));
        printf("Beginn: %d.%d.%d", ((Student*)current->value)->beginn.tag, ((Student*)current->value)->beginn.monat, ((Student*)current->value)->beginn.jahr);

        goToXY(22,(y += 2));
        printf("Ende: %d.%d.%d", ((Student*)current->value)->ende.tag, ((Student*)current->value)->ende.monat, ((Student*)current->value)->ende.jahr);

        goToXY(22,(y += 2));
        printf("Neue Abfrage -> Enter; Menue -> Arrow");
    } else {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Es wurde nichts gefunden!");

        goToXY(22,(y += 2));
        printf("Erneut versuchen -> Enter; Menue -> Arrow");
    }
}
void con_showDataFull(LinkedList *students) {
    list_sort(students,compareStudents);
    int y = 0;
    int height = students->size * 2 + 5;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Es wurden %d Datensaetze gefunden:", students->size);

    Item *current = students->head;
    while (current) {
        Student* value = (Student*)current->value;
        goToXY(22,(y += 2));
        printf("%s\t%s\t%d", value->vname, value->nname, value->id);
        current = current->next;
    }

    goToXY(22,(y += 2));
    printf("Erneut ausgeben -> Enter; Menue -> Arrow");

}
void con_deleteData(LinkedList *student) {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Bitte geben Sie die ID des zu loeschenden Studenten ein:");
    goToXY(22,y+1);
    int id;
    scanf("%d", &id);

    Item *parent = student->head;
    Item *current = parent->next;

    if (((Student*)parent->value)->id == id) {
        current = parent;
    }

    while (current) {
        if (((Student*)current->value)->id == id) {
            break;
        }
        current = current->next;
    }

    if(current) {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Folgende Informationen wurden gefunden:");

        goToXY(22,(y += 2));
        printf("Vorname: %s\t\tNachname: %s", ((Student*)current->value)->vname, ((Student*)current->value)->nname);

        goToXY(22,(y += 2));
        printf("ID: %d", ((Student*)current->value)->id);

        goToXY(22,(y += 2));
        printf("Geburtstag: %d.%d.%d", ((Student*)current->value)->gtag.tag, ((Student*)current->value)->gtag.monat, ((Student*)current->value)->gtag.jahr);

        goToXY(22,(y += 2));
        printf("Beginn: %d.%d.%d", ((Student*)current->value)->beginn.tag, ((Student*)current->value)->beginn.monat, ((Student*)current->value)->beginn.jahr);

        goToXY(22,(y += 2));
        printf("Ende: %d.%d.%d", ((Student*)current->value)->ende.tag, ((Student*)current->value)->ende.monat, ((Student*)current->value)->ende.jahr);

        goToXY(22,(y += 2));
        printf("Moechten Sie diese Daten loeschen? [j/n]");

        switch (getch()) {
            case 106:
            case 74:
                if(parent != current) {
                    parent->next = current->next;
                    free(current);
                } else {
                    student->head = current;
                }
                student->size--;
                goToXY(22,(y += 2));
                printf("Geloescht! Naechsten loeschen -> Enter; Menue -> Arrow");
                break;
            default:
                goToXY(22,(y += 2));
                printf("Behalten! Erneut versuchen -> Enter; Menue -> Arrow");
        }
    } else {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Es wurde nichts gefunden!");

        goToXY(22,(y += 2));
        printf("Erneut versuchen -> Enter; Menue -> Arrow");
    }
}

void save(LinkedList *data) {
    list_print(data);
    FILE *file = fopen(SAVE_PATH, "w+");
    if(!file) {
        exit(555);

    }

    Json j = json_mkJson(JSON_OBJ);
    json_obj_put_int(&j, "size", data->size);

    LinkedList jsonList = list_mkList();
    Item *current = data->head;
    while (current) {
        Student *value = (Student*)current->value;
        Json *j = calloc(1, sizeof (Json));
        *j = json_mkJson(JSON_OBJ);

        json_obj_put_string(j, "vname", value->vname);
        json_obj_put_string(j, "nname", value->nname);
        json_obj_put_int(j, "id", value->id);

        Json *gday = calloc(1, sizeof (Json));
        *gday = json_mkJson(JSON_OBJ);
        json_obj_put_int(gday, "day", value->gtag.tag);
        json_obj_put_int(gday, "month", value->gtag.monat);
        json_obj_put_int(gday, "year", value->gtag.jahr);

        json_obj_put(j, "geburtstag", gday);

        Json *bday = calloc(1, sizeof (Json));
        *bday = json_mkJson(JSON_OBJ);
        json_obj_put_int(bday, "day", value->beginn.tag);
        json_obj_put_int(bday, "month", value->beginn.monat);
        json_obj_put_int(bday, "year", value->beginn.jahr);

        json_obj_put(j, "beginn", bday);

        Json *eday = calloc(1, sizeof (Json));
        *eday = json_mkJson(JSON_OBJ);
        json_obj_put_int(eday, "day", value->ende.tag);
        json_obj_put_int(eday, "month", value->ende.monat);
        json_obj_put_int(eday, "year", value->ende.jahr);

        json_obj_put(j, "ende", eday);

        list_push(&jsonList, j);

        current = current->next;
    }

    Json list = json_list(jsonList);
    json_obj_put(&j, "data", &list);

    char* jsonSring = json_dump(j);

    printf("%s", jsonSring);
    fputs(jsonSring,file);

    fclose(file);
}

LinkedList* load() {
    //TODO: Load from File
    Student *s1 = (Student *)calloc(1, sizeof (Student));
    s1->id = 456;
    s1->nname = "Max";
    s1->vname = "Maxi";

    Student *s2 = (Student *)calloc(1, sizeof (Student));
    s2->id = 123;
    s2->nname = "Hans";
    s2->vname = "Hansi";

    STUDENTS = list_mkList();
    STUDENTS.size = 0;
    STUDENTS.head = NULL;

    list_push(&STUDENTS, s1);
    list_push(&STUDENTS, s2);

    list_print(&STUDENTS);
    printf("%s", ((Student *)STUDENTS.head->value)->nname);
    printf("%s", ((Student *)STUDENTS.head->value)->vname);
    printf("%s", ((Student *)STUDENTS.head->next->value)->nname);
    printf("%s", ((Student *)STUDENTS.head->next->value)->vname);

    Student *head = (Student*)STUDENTS.head->value;
    return &STUDENTS;
}

int compareStudents(Item *first, Item *sec) {
    char *name1 = ((Student*)first->value)->nname;
    char *name2 = ((Student*)sec->value)->nname;

    int i = 0;
    while (name1[i] == name2) {
        i++;
    }

    return name2[i] - name1[i];
}