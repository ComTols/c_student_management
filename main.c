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

void decode(Student *students, int size){
    //Öffne Datei und leere diese
    FILE *file;
    file = fopen("../daten.json", "w+");
    if(file == NULL) printf("Datei konnte nicht geöffnet werden.");

    fprintf(file, "{\"anzahl\":%d,\"studierende\":[", size);
    Student* index = students;
    for(int i = 0; i < size; i++) {
        fprintf(file,
                "{\"vname\":\"%s\",\"nname\":\"%s\",\"id\":%d,\"gtag\":{\"tag\":%d,\"monat\":%d,\"jahr\":%d},\"beginn\":{\"tag\":%d,\"monat\":%d,\"jahr\":%d},\"ende\":{\"tag\":%d,\"monat\":%d,\"jahr\":%d}}",
                index->vname,index->nname,index->id,index->gtag.tag,index->gtag.monat,index->gtag.jahr,index->beginn.tag,index->beginn.monat,index->beginn.jahr,index->ende.tag,index->ende.monat,index->ende.jahr);
        index++;
        if(i != size-1) {
            fprintf(file,",");
        }
    }
    fprintf(file, "]}");
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
    decode(students, 100);
    return 0;
}