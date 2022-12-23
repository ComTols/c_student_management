//
// Created by Justin Kreuzmann on 23.12.2022.
//

#ifndef C_STUDENT_MANAGEMENT_CONSOLE_H
#define C_STUDENT_MANAGEMENT_CONSOLE_H

typedef struct menu {
    char* name;
    void (*callback)();
} MenuItem;

typedef struct datum {
    int tag;
    int monat;
    int jahr;
} Datum;

typedef struct student {
    char* vname;
    char* nname;
    int id;
    Datum gtag;
    Datum beginn;
    Datum ende;
} Student;

MenuItem con_mkMenuItem(char *name, void (*callback)());
Student mkStudent(char *vname, char *nname, int id, Datum gtag, Datum beginn, Datum ende);
Datum mkDatum(int tag, int monat, int jahr);

void goToXY(int x, int y);
void logo(int *line);
void con_frame(int height, int* firstLine);
void con_redraw(MenuItem *items, int length, int *pos);
MenuItem *con_mkMenu(int *size);
void con_input(MenuItem *items,int length, int *pos);
void con_clamp(int *in, int max);

#endif //C_STUDENT_MANAGEMENT_CONSOLE_H
