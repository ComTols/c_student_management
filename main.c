#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int tag;
    int monat;
    int jahr;
} Datum;

typedef struct {
    char *vname;
    char *nname;
    int id;
    Datum gtag;
    Datum beginn;
    Datum ende;
} Student;

void saveAsFile(Student* students, char* path) {

}

Student* getFromFile(char* path) {

}

bool decode(Student *students){
    char json = malloc(374);
    for (int i = 0; i < ((sizeof *students)/(sizeof students[0])); ++i) {

    }
}

Student* encode(char* jsonString) {
    char* index = jsonString;
    printf("%c", jsonString[0]);
}

void jObject() {

}

int main(int argc, char *argv[]) {
    Student* students = {
            {"Max", "Mustermann", 334562, {10,11,2012},{10,11,2012},{10,11,2012}},
            {"Adam", "Musterfrau", 234566, {2,8,2010},{10,11,2012},{10,11,2012}}
    };


    //saveAsFile(students, "database.json");
    encode("Test");
    return 0;
}