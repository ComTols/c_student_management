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

Student* encode(char* jsonString) {
    int size = strlen(jsonString);
    printf("%c%c\n", jsonString[0], jsonString[size-1]);
    if(jsonString[0] == '{' && jsonString[size-1] == '}') {
        printf("%c\n", jsonString[1]);
        if(jsonString[1] == '"') {
            int i = 2;
            while (jsonString[i] != '"') {
                printf("%c", jsonString[i]);
                i++;
            }
            char variableName[i-2];
            for (int j = 2; j < i-2; j++) {
                variableName[j] = jsonString[j];
            }
            printf("\n%s lol", variableName);
        } else {
            printf("Json ist nicht in der geforderten Form!");
            exit(json_error_file_struct_head_not_formatet);
        }
    } else {
        printf("Json ist nicht in der geforderten Form!");
        exit(json_error_file_struct_beginn_or_end);
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
    printf("%s\n", students[90].nname);
    return;
    //saveAsFile(students, "database.json");
    encode("{\"anzahl\":4}");
    return 0;
}