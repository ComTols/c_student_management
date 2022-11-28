#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void saveAsFile(Student *students, char *path) {
    FILE *f = fopen(path, "w+");

}

Student *getFromFile(char *path) {

}

void decode(Student *students){
    FILE *file;
    file = fopen("../daten.json", "w+");
    if(file == NULL) printf("errroer");
    fputs("\"anzahl\": ",file);
    printf("%lu",sizeof (*students));
    //fputs(length, file);
    fputs(",\"studierende\":[",file);
    /*for (int i = 0; i < (sizeof *students); ++i) {
        /*fputs("\"vname\" : \"\","
              "      \"nname\" : \"\","
              "      \"id\" : \"\","
              "      \"gtag\": {"
              "        \"tag\": \"\","
              "        \"monat\" : \"\","
              "        \"Jahr\" : \"\""
              "      },"
              "      \"beginn\": {"
              "        \"tag\": \"\","
              "        \"monat\" : \"\","
              "        \"Jahr\" : \"\""
              "      },"
              "      \"ende\": {"
              "        \"tag\": \"\","
              "        \"monat\" : \"\","
              "        \"Jahr\" : \"\""
              "      }",file);
    }*/
    fclose(file);
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
    //printf("%s\n", students[90].nname);
    //saveAsFile(students, "database.json");
    decode(students);
    return 0;
}