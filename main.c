#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

Student* getFromFile(char *path);
void saveAsFile(Student *students, char *path);
Student* encode(char* jsonString);
Student jStudent(char* jsonString, int* indexPointer);
Student* encode(char* jsonString);
char* jString(char* jsonString, int* indexPointer);
Datum jDatum(char* jsonString, int* indexPointer);
bool isNumber(char c);
int potenz(int basis, int exponent);

void saveAsFile(Student *students, char *path) {
    FILE *f = fopen(path, "w+");

}

Student* getFromFile(char *path) {

}

Student* encode(char* jsonString) {
    int i = 10;
    //Hole Anzahl
    int anzahl = jInt(jsonString, &i);

    //Prüfen, ob Schlüsselwort studierende nach Anzahl
    i += 2;
    if(jsonString[i] == 's' && jsonString[i+10]=='e') {
        i+=13;
        //Prüfen, ob studierende ein Array ist.
        if(jsonString[i] == '[') {
            Student* students = calloc(anzahl, sizeof (Student));
            Student* s = students;
            i++;
            if(jsonString[i] == ']') {
                //Leeres Array
                return NULL;
            }
            while (jsonString[i] == '{') {
                i++;
                *s = jStudent(jsonString, &i);
                s++;
            }
            //TODO: Abfangen Syntax error
            return students;
        } else {
            exit(3);
        }
    } else {
        exit(2);
    }
}

Student jStudent(char* jsonString, int* indexPointer) {
    int index = *indexPointer;
    index++;
    Student* student = malloc(sizeof (Student));
    //Es folgen fünf Felder
    for (int k = 0; k < 5; ++k) {
        //Prüfen, ob beginn folgt
        if(jsonString[index] == 'b' && jsonString[index+5] == 'n') {
            index += 8;
            student->beginn = jDatum(jsonString, &index);
            //printf("Beginn Datum: %d.%d.%d\n", student->beginn.tag, student->beginn.monat,student->beginn.jahr);
        //Prüfen, ob ende folgt
        } else if(jsonString[index] == 'e' && jsonString[index+3]== 'e') {
            index += 6;
            student->ende = jDatum(jsonString, &index);
            //printf("Ende Datum: %d.%d.%d\n", student->ende.tag, student->ende.monat,student->ende.jahr);
        //Prüfen, ob gtag folgt
        } else if(jsonString[index] == 'g' && jsonString[index+3]== 'g') {
            index += 6;
            student->gtag = jDatum(jsonString, &index);
            //printf("Geburtstag Datum: %d.%d.%d\n", student->gtag.tag, student->gtag.monat,student->gtag.jahr);
        //Prüfen, ob nname folgt
        } else if(jsonString[index] == 'n' && jsonString[index+4]== 'e') {
            index += 7;
            student->nname = jString(jsonString, &index);
            //printf("Nachname string: %s\n", student->nname);
        //Prüfen, ob vname folgt
        } else if(jsonString[index] == 'v' && jsonString[index+4]== 'e') {
            index += 7;
            student->vname = jString(jsonString, &index);
            //printf("Vorname string: %s\n", student->vname);
        //Prüfen, ob id folgt
        } else if(jsonString[index] == 'i' && jsonString[index+1]== 'd') {
            index += 4;
            student->id = jInt(jsonString, &index);
            //printf("Id int: %d\n", student->id);
        } else {
            exit(6);
        }
        index += 3;
    }
    *indexPointer = index;
    return *student;
}

int jInt(char* jsonString, int* indexPointer) {
    int index = *indexPointer;
    //Prüfen, ob Nummer ist
    if(isNumber(jsonString[index])) {
        int numberSize = 0;
        while (isNumber(jsonString[index+numberSize])) {
            numberSize++;
        }
        int number = 0;
        for (int j = 0; j < numberSize; j++) {
            number += potenz(10, numberSize - j) * (int)(jsonString[index+j] - '0');
        }
        number /= 10;
        index += numberSize;
        *indexPointer = index;
        return number;
    } else {
        exit(8);
    }
}


char* jString(char* jsonString, int* indexPointer) {
    int index = *indexPointer;
    //Prüfen, ob String ist
    if(jsonString[index] == '"') {
        index++;
        //Länge des Strings
        int strSize = 0;
        while (jsonString[index+strSize] != '"') {
            strSize++;
        }
        char *string = calloc(strSize, sizeof (char ));
        for (int i = 0; i < strSize; ++i) {
            string[i] = jsonString[index+i];
        }
        index += strSize;
        *indexPointer = index;
        return string;
    } else {
        exit(7);
    }
}


Datum jDatum(char* jsonString, int* indexPointer) {
    int index = *indexPointer;
    //Prüfen, ob Objekt ist
    if(jsonString[index] == '{') {
        //Es folgen drei Felder
        int tag = 0;
        int monat = 0;
        int jahr = 0;
        for (int i = 0; i < 3; i++) {
            index += 2;
            //Prüfen, ob Tag folgt
            if(jsonString[index] == 't' && jsonString[index+2]=='g') {
                index += 5;
                //String in int konvertieren
                int sizeTag = 0;
                while (isNumber(jsonString[index+sizeTag])) {
                    sizeTag++;
                }
                for (int j = 0; j < sizeTag; j++) {
                    tag += potenz(10, sizeTag-j) * (int)(jsonString[index+j]-'0');
                }
                tag /= 10;
                index += sizeTag;
                //Prüfen, ob monat folgt
            } else if (jsonString[index] == 'm' && jsonString[index+4]=='t') {
                index += 7;
                //String in int konvertieren
                int sizeMonat = 0;
                while (isNumber(jsonString[index+sizeMonat])) {
                    sizeMonat++;
                }
                for (int j = 0; j < sizeMonat; j++) {
                    monat += potenz(10, sizeMonat - j) * (int)(jsonString[index + j] - '0');
                }
                monat /= 10;
                index += sizeMonat;
                //Prüfen, ob jahr folgt
            } else if (jsonString[index] == 'j' && jsonString[index+3]=='r') {
                index += 6;
                //String in int konvertieren
                int sizeJahr = 0;
                while (isNumber(jsonString[index + sizeJahr])) {
                    sizeJahr++;
                }
                for (int j = 0; j < sizeJahr; j++) {
                    jahr += potenz(10, sizeJahr - j) * (int)(jsonString[index + j] - '0');
                }
                jahr /= 10;
                index += sizeJahr;
            } else {
                exit(5);
            }
        }
        Datum* datum = malloc(sizeof (Datum));
        datum->tag = tag;
        datum->monat = monat;
        datum->jahr = jahr;
        *indexPointer = index;
        printf("\n\n---\n%c\n", jsonString[index]);

        return *datum;
    } else {
        exit(4);
    }

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


int main(int argc, char *argv[]) {
    Student* students = calloc(100,sizeof (Student));
    Student* index = students;

    for (int i = 0; i < 100; i++) {
        index->nname = "Max";
        index->vname = "Mustermann";
        index->id = i + 100;
        index++;
    }
    //saveAsFile(students, "database.json");
    students = encode("{\"anzahl\":2,\"studierende\":[{\"beginn\":{\"tag\":15,\"monat\":5,\"jahr\":2001},\"ende\":{\"tag\":10,\"monat\":3,\"jahr\":2011},\"gtag\":{\"tag\":1,\"monat\":10,\"jahr\":2021},\"nname\":\"Mustermann\",\"vanme\":\"Max\"},{\"beginn\":{\"tag\":15,\"monat\":5,\"jahr\":2001},\"ende\":{\"tag\":10,\"monat\":3,\"jahr\":2011},\"gtag\":{\"tag\":1,\"monat\":10,\"jahr\":2021},\"nname\":\"Mustermann\",\"vanme\":\"Hans\"}]}");
    if(students == NULL) {
        printf("Leere Datei");
    }
    index = students;
    for (int i = 0; i < 2; ++i) {
        printf("Name: %s, Vorname: %s, Geburtstag: %d.%d.%d\n", index->nname, index->vname, index->gtag.tag, index->gtag.monat, index->gtag.jahr);
        index++;
    }
    return 0;
}