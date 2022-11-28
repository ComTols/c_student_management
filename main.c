#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum EXIT_CODES {
    json_error_file_struct_beginn_or_end = 1,
    json_error_file_struct_head_not_formatet = 2,
};

typedef struct {
    int tag;
    int monat;
    int jahr;
} Datum;

typedef struct {
    char* vname;
    char* nname;
    int id;
    Datum gtag;
    Datum beginn;
    Datum ende;
} Student;

void saveAsFile(Student *students, char *path) {
    FILE *f = fopen(path, "w+");

}

Student *getFromFile(char *path) {

}

bool isNumber(char c) {
    if(
        c == '0' ||
        c == '1' ||
        c == '2' ||
        c == '3' ||
        c == '4' ||
        c == '5' ||
        c == '6' ||
        c == '7' ||
        c == '8' ||
        c == '9'
    ) {
        return true;
    }
    return false;
}

int potenz(int basis, int exponent) {
    if(exponent == 0) return 1;
    int ret = basis;
    for (int i = 1; i < exponent; ++i) {
        ret *= basis;
    }
    return ret;
}

Student* encode(char* jsonString) {
    //int size = strlen(jsonString);

    //Prüfen, ob an der Stelle 10 eine Nummer ist (erste Stelle von anzahl)
    if(!isNumber(jsonString[10])) {
        exit(1);
    }
    //Ende der Nummer finden
    int i = 10;
    while (isNumber(jsonString[i])) {
        i++;
    }
    //String in int konvertieren
    int anzahl = 0;
    for (int j = 10; j < i; j++) {
        anzahl += potenz(10, i-j) * (int)(jsonString[j]-'0');
    }
    anzahl /= 10;
    printf("Anzahl: %d", anzahl);

    //Prüfen, ob Schlüsselwort studierende nach Anzahl
    i += 2;
    if(jsonString[i] == 's' && jsonString[i+10]=='e') {
        printf("%c%c", jsonString[i], jsonString[i+10]);
        i+=13;
        //Prüfen, ob studierende ein Array ist.
        if(jsonString[i] == ']') {
            i++;
            if(jsonString[i] == ']') {
                //Leeres Array
                return 0;
            }
            //TODO: Studenten auslesen
        } else {
            exit(3);
        }
    } else {
        exit(2);
    }
}


int main(int argc, char *argv[]) {
    Student* students = malloc(sizeof (Student)*100);
    Student* index = students;

    for (int i = 0; i < 100; i++) {
        index->nname = "Max";
        index->vname = "Mustermann";
        index->id = i + 100;
        index++;
    }
    //saveAsFile(students, "database.json");
    encode("{\"anzahl\":44567894,\"studierende\":[]}");
    return 0;
}