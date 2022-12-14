#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int tag;
    int monat;
    int jahr;
} Datum;        //struct for date

typedef struct {
    char *nname;
    int id;
    Datum gtag;
    Datum beginn;
    Datum ende;
    struct Student *next;
} Student;      //struct for student data

typedef struct {
    Student *head;
    Student *tail;
    int length;
    int listIndex;
} Liste;        //struct for List

Liste studentlist;

Student *getCurrent(Liste list) {
    Student *s = list.head;
    for(int i = 0; i < list.listIndex; i++) {
        s = s->next;
        if(s == NULL) {
            s=list.tail;
            list.listIndex= list.length;
            break;
        }
    }
    return s;
} //returns address of current list item

Student *next(Liste list) {
    Student *s = getCurrent(list);
    s = s->next;
    if (s!=NULL){
        list.listIndex++;
    }
    return s;
} //moves the pointer to the next item
  //returns NULL if it tried to step over your last item

Student *inputStudent(){
    Student st1;
    printf("Last name:\n");
    char *buffer = malloc(5 * sizeof(char));
    st1->nname = gets(buffer); //printf("Nachname: %s", st1.nname); to check if it works
    //TOD: andere Inputs implementieren
    printf("Id:\n");
    st1.id = gets();
    printf("Birthday [DD.MM.YYYY]:\n");
    scanf_s("%d.%d.%d", &st1.gtag.tag, &st1.gtag.monat, &st1.gtag.jahr);
    if (st1.gtag.tag < 1 || st1.gtag.tag > 31 || st1.gtag.monat < 1 || st1.gtag.monat > 12){
        printf("Error: Wrong input! Please repeat!\n");
        bool again = true;
        while (again){
            scanf_s("%d.%d.%d", &st1.gtag.tag, &st1.gtag.monat, &st1.gtag.jahr);
            if (st1.gtag.tag > 0 || st1.gtag.tag < 31 || st1.gtag.monat > 0 || st1.gtag.monat < 12){
                again = false;
            }else{
                printf("Error: Wrong input! Please repeat!\n");
            }
        }
    }

    printf("Day of immatriculation [DD.MM.YYYY]:\n");
    scanf_s("%d.%d.%d", &st1.beginn.tag, &st1.beginn.monat, &st1.beginn.jahr);
    if (st1.beginn.tag < 1 || st1.beginn.tag > 31 || st1.beginn.monat < 1 || st1.beginn.monat > 12){
        printf("Error: Wrong input! Please repeat!\n");
        bool again = true;
        while (again){
            scanf_s("%d.%d.%d", &st1.beginn.tag, &st1.beginn.monat, &st1.beginn.jahr);
            if (st1.beginn.tag > 0 || st1.beginn.tag < 31 || st1.beginn.monat > 0 || st1.beginn.monat < 12){
                again = false;
            }else{
                printf("Error: Wrong input! Please repeat!\n");
            }
        }
    }

    printf("Expected day of graduation [DD.MM.YYYY]:\n");
    scanf_s("%d.%d.%d", &st1.ende.tag, &st1.ende.monat, &st1.ende.jahr);
    if (st1.ende.tag < 1 || st1.ende.tag > 31 || st1.ende.monat < 1 || st1.ende.monat > 12){
        printf("Error: Wrong input! Please repeat!\n");
        bool again = true;
        while (again){
            scanf_s("%d.%d.%d", &st1.ende.tag, &st1.ende.monat, &st1.ende.jahr);
            if (st1.ende.tag > 0 || st1.ende.tag < 31 || st1.ende.monat > 0 || st1.ende.monat < 12){
                again = false;
            }else{
                printf("Error: Wrong input! Please repeat!\n");
            }
        }
    }
    return &st1;

} //lets the user input student data and returns the address of the new item

int addStudent(){
    Student *new = inputStudent();
    Student *s = getCurrent(studentlist);
    Student *following = s->next;
    //Evtl. null abfangen?
    s->next = new;
    new->next = following;
    return 0;
    //Neuen Eintrag an alphabetisch richtige position Einfügen
} //adds another student to the list

int getNumberOfStudents(Liste list) {
    Student *s;
    int i = 0;
    list.listIndex = 0;
    while (s != NULL) {
        s = next(list);
        i++;
    }
    return i;
} // returns the number of total students

Student *findStudent(int id, Liste list){
    Student *s = list.head;
    Student *target;
    for(int i = 0; i < list.length; i++) {
        s = s->next;
        if (s!=NULL){
            list.listIndex++;
        }
        if(s->id == id) {
            target = s;
        }
    }
    return target;
}

void printStudent(int id, Liste list){
    Student *s = findStudent(id, list);
    printf("Name: %c\n", s->nname);
    printf("Id: %d\n", s->id);
    printf("Birthday: %d.%d.%d\n", s->gtag.tag, s->gtag.monat, s->gtag.jahr);
    printf("Day of immatriculation: %d.%d.%d\n", s->beginn.tag, s->beginn.monat, s->beginn.jahr);
    printf("Expected day of graduation: %d.%d.%d\n", s->ende.tag, s->ende.monat, s->ende.jahr);
} //prints a student

void printAllStudents(Liste list){
    Student *s = list.head;
    for(int i = 0; i < list.length; i++) {
        printf("Name: %c\n", s->nname);
        printf("Id: %d\n", s->id);
        printf("Birthday: %d.%d.%d\n", s->gtag.tag, s->gtag.monat, s->gtag.jahr);
        printf("Day of immatriculation: %d.%d.%d\n", s->beginn.tag, s->beginn.monat, s->beginn.jahr);
        printf("Expected day of graduation: %d.%d.%d\n", s->ende.tag, s->ende.monat, s->ende.jahr);
        s = s->next;
        if(s == NULL) {
            s=list.tail;
            break;
        }
    }
} //prints all students in alphabetical order

void deleteStudent(int id, Liste list){
    Student *s = findStudent(id, list);
    Student *latest;
    Student *following;
    s->nname = NULL;
    s->id = 0;
    s->gtag.monat = 0;
    s->gtag.monat = 0;
    s->gtag.jahr = 0;
    s->beginn.monat = 0;
    s->beginn.monat = 0;
    s->beginn.jahr = 0;
    s->ende.monat = 0;
    s->ende.monat = 0;
    s->ende.jahr = 0;
    s->next = NULL;
    following = next(list);
    list.listIndex -= 2;
    latest = getCurrent(list);
    latest->next = following;
} //deletes a student from the list


int main(){
    //TOD: Errors nummerieren für besseres Debugging
    studentlist.listIndex = 0;
    Student st1;
    studentlist.head = &st1;
    

}

//printf("Error: List end overreach\n");