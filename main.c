#include <stdio.h>
#include <stdlib.h>


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
    //TOD: Abfangen, ob Ende der Liste
    Student *s = list.head;
    for(int i = 0; i < list.listIndex; i++) {
        //TOD: Null abfangen
        s = s->next;
        if(s == NULL) {
            s=list.tail;
            list.listIndex= list.length;
            break;
        }
    }
    return s;
}       //returns address of current list item



Student *next(Liste list) {
    //TOD: Abfangen, ob Ende der Liste
    Student *s = getCurrent(list);
    s = s->next;
    list.listIndex++;
    return s;
} //moves the pointer to the next item

Student *inputStudent(){
    Student st1;
    printf("Wie lautet der Nachname?\n");
    char *buffer = malloc(5 * sizeof(char));
    st1.nname = gets(buffer);
    printf("Nachname: %s", st1.nname);
    //TOD: andere Inputs implementieren
} //lets the user input student data and returns the address of the new item

int addStudent(){
    Student *new = inputStudent();
    Student *s = getCurrent(studentlist);
    Student *following = s->next;
    //Evtl. null abfangen?
    s->next = new;
    new-> next = following;
    return 0;
    //Neuen Eintrag an alphabetisch richtige position Einfügen
} //adds another student to the list

int getNumberOfStudents(Liste list) {
    Student *s;
    int i = 0;
    while (s != NULL) {
        s = next(list);
        i++;
    }
    return i;
} // returns the number of total students

void printStudent(int id){

} //prints a student

void printAllStudents(){

} //prints all students in alphabetical order

void deleteStudent(int id){

} //deletes a student from the list


int main(){
    //TOD: Errors nummerieren für besseres Debugging
    studentlist.listIndex = 0;
    Student st1;
    studentlist.head = &st1;
    

}