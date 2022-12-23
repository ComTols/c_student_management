#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

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

Student mkStudent(char *vname, char *nname, int id, Datum gtag, Datum beginn, Datum ende) {
    Student s;
    s.vname = vname;
    s.nname = nname;
    s.id = id;
    s.gtag = gtag;
    s.beginn = beginn;
    s.ende = ende;

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

void con_input(MenuItem *items,int length, int *pos) {
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
            items[*pos].callback();
            break;
        case 27:
            //ESC
            //TODO: Speichern
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

void con_newData() {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Vorname: ");
    char vname[100];
    scanf("%s99", &vname);

    goToXY(22,(y += 2));
    printf("Nachname: ");
    char nname[100];
    scanf("%s99", &nname);

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
        Student newStudent = mkStudent(vname, nname, id, gTag, beginn, ende);
        //TODO: Insert
        goToXY(22,(y += 2));
        printf("Gespeichert! Weiteren hinzufuegen -> Enter; Menue -> Arrow");
    } else {
        goToXY(22,(y += 2));
        printf("Verworfen! Erneut versuchen -> Enter; Menue -> Arrow");
    }
}
void con_editData() {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Bitte geben Sie die ID des zu bearbeitenden Studenten ein:");
    goToXY(22,y+1);
    int id;
    scanf("%d", &id);

    //TODO: Suche studenten

    if(!0) {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Folgende Informationen wurden gefunden:");

        goToXY(22,(y += 2));
        printf("[1] Vorname: %s\t\t[2] Nachname: %s", "Max", "Mustermann");

        goToXY(22,(y += 2));
        printf("[3] ID: %d", 12345);

        goToXY(22,(y += 2));
        printf("[4] Geburtstag: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("[5] Beginn: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("[6] Ende: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("Was moechten Sie bearbeiten?");

        int key = getch();
        switch (key) {
            case 49:
                //1
                break;
            case 50:
                //2
                break;
            case 51:
                //3
                break;
            case 52:
                //4
                break;
            case 53:
                //5
                break;
            case 54:
                //6
                break;
        }
    } else {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Es wurde nichts gefunden!");

        goToXY(22,(y += 2));
        printf("Erneut versuchen -> Enter; Menue -> Arrow");
    }

}
void con_countData() {
    int y = 0;
    int height = 5;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Aktuell sind %d Datensaetze gespeichert.", 0);

    goToXY(22,(y += 2));
    printf("Erneut zaehlen -> Enter; Menue -> Arrow");
}
void con_showData() {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Bitte geben Sie die ID des Studenten ein:");
    goToXY(22,y+1);
    int id;
    scanf("%d", &id);

    //TODO: Suche studenten

    if(!0) {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Folgende Informationen wurden gefunden:");

        goToXY(22,(y += 2));
        printf("Vorname: %s\t\tNachname: %s", "Max", "Mustermann");

        goToXY(22,(y += 2));
        printf("ID: %d", 12345);

        goToXY(22,(y += 2));
        printf("Geburtstag: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("Beginn: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("Ende: %d.%d.%d", 1,9,2001);

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
void con_showDataFull() {
    printf("show2");

}
void con_deleteData() {
    int y = 0;
    int height = 19;
    con_frame(height, &y);

    goToXY(22,y);
    printf("Bitte geben Sie die ID des zu loeschenden Studenten ein:");
    goToXY(22,y+1);
    int id;
    scanf("%d", &id);

    //TODO: Suche studenten

    if(!0) {
        con_frame(height, &y);
        goToXY(22,y);
        printf("Folgende Informationen wurden gefunden:");

        goToXY(22,(y += 2));
        printf("Vorname: %s\t\tNachname: %s", "Max", "Mustermann");

        goToXY(22,(y += 2));
        printf("ID: %d", 12345);

        goToXY(22,(y += 2));
        printf("Geburtstag: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("Beginn: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("Ende: %d.%d.%d", 1,9,2001);

        goToXY(22,(y += 2));
        printf("Moechten Sie diese Daten loeschen? [j/n]");

        switch (getch()) {
            case 106:
            case 74:
                //TODO: Löschen
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