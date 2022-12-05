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