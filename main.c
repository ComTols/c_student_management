#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>


COORD coord = { 0, 0 };

void gotoxy(int x, int y) {
    coord.X = x; coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}





int menuAnzeige(int MenuChoice,int WhereInMenu)
{
    printf("\33[?25l");   //Versteckt den Courser   (um ihn wieder zu aktivieren printf("\33[?25h");

    switch (MenuChoice)
    {
        case 1:
            system ("cls");


            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 19);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(26, 7);
            printf("\033[0;31m");       //Auswahl 1 gefärbt
            printf("1. Sch\x81ler eintragen\n\n");
            printf("\033[0m");

            gotoxy(26, 9);
            printf("2. Sch\x81ler hinzuf\x81gen\n\n");

            gotoxy(26, 11);
            printf("3. Anzahl der Sch\x81ler\n\n");

            gotoxy(26, 13);
            printf("4. Zeige Sch\x81ler \n\n");

            gotoxy(26, 15);
            printf("5. Zeige alle Sch\x81ler\n\n");

            gotoxy(26, 17);
            printf("6. L\x94sche Sch\x81ler\n\n");

            gotoxy(21, 21);
            printf(" Dr\x81 \bcke ESC zum speichern und verlassen");

            break;

        case 2:
            system ("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 19);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(26, 7);
            printf("1. Sch\x81ler eintragen\n\n");

            printf("\033[0;31m");       //Auswahl 2 gefärbt
            gotoxy(26, 9);
            printf("2. Sch\x81ler hinzuf\x81gen\n\n");
            printf("\033[0m");

            gotoxy(26, 11);
            printf("3. Anzahl der Sch\x81ler\n\n");

            gotoxy(26, 13);
            printf("4. Zeige Sch\x81ler \n\n");

            gotoxy(26, 15);
            printf("5. Zeige alle Sch\x81ler\n\n");

            gotoxy(26, 17);
            printf("6. L\x94sche Sch\x81ler\n\n");

            gotoxy(21, 21);
            printf(" Dr\x81 \bcke ESC zum speichern und verlassen");

            break;

        case 3:
            system ("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 19);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(26, 7);
            printf("1. Sch\x81ler eintragen\n\n");

            gotoxy(26, 9);
            printf("2. Sch\x81ler hinzuf\x81gen\n\n");

            printf("\033[0;31m");       //Auswahl 3 gefärbt
            gotoxy(26, 11);
            printf("3. Anzahl der Sch\x81ler\n\n");
            printf("\033[0m");

            gotoxy(26, 13);
            printf("4. Zeige Sch\x81ler \n\n");

            gotoxy(26, 15);
            printf("5. Zeige alle Sch\x81ler\n\n");

            gotoxy(26, 17);
            printf("6. L\x94sche Sch\x81ler\n\n");

            gotoxy(21, 21);
            printf(" Dr\x81 \bcke ESC zum speichern und verlassen");

            break;

        case 4:
            system ("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 19);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(26, 7);
            printf("1. Sch\x81ler eintragen\n\n");

            gotoxy(26, 9);
            printf("2. Sch\x81ler hinzuf\x81gen\n\n");

            gotoxy(26, 11);
            printf("3. Anzahl der Sch\x81ler\n\n");

            gotoxy(26, 13);
            printf("\033[0;31m");       //Auswahl 4 gefärbt
            printf("4. Zeige Sch\x81ler \n\n");
            printf("\033[0m");

            gotoxy(26, 15);
            printf("5. Zeige alle Sch\x81ler\n\n");

            gotoxy(26, 17);
            printf("6. L\x94sche Sch\x81ler\n\n");

            gotoxy(21, 21);
            printf(" Dr\x81 \bcke ESC zum speichern und verlassen");

            break;

        case 5:
            system ("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 19);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(26, 7);
            printf("1. Sch\x81ler eintragen\n\n");

            gotoxy(26, 9);
            printf("2. Sch\x81ler hinzuf\x81gen\n\n");

            gotoxy(26, 11);
            printf("3. Anzahl der Sch\x81ler\n\n");

            gotoxy(26, 13);
            printf("4. Zeige Sch\x81ler \n\n");

            printf("\033[0;31m");       //Auswahl 5 gefärbt
            gotoxy(26, 15);
            printf("5. Zeige alle Sch\x81ler\n\n");
            printf("\033[0m");

            gotoxy(26, 17);
            printf("6. L\x94sche Sch\x81ler\n\n");

            gotoxy(21, 21);
            printf(" Dr\x81 \bcke ESC zum speichern und verlassen.");

            break;

        case 6:
            system ("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENTEN-MANAGEMENT-PROGRAMM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 19);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(26, 7);
            printf("1. Sch\x81ler eintragen\n\n");

            gotoxy(26, 9);
            printf("2. Sch\x81ler hinzuf\x81gen\n\n");

            gotoxy(26, 11);
            printf("3. Anzahl der Sch\x81ler\n\n");

            gotoxy(26, 13);
            printf("4. Zeige Sch\x81ler \n\n");

            gotoxy(26, 15);
            printf("5. Zeige alle Sch\x81ler\n\n");

            printf("\033[0;31m");       //Auswahl 6 gefärbt
            gotoxy(26, 17);
            printf("6. L\x94sche Sch\x81ler\n\n");
            printf("\033[0m");

            gotoxy(21, 21);
            printf(" Dr\x81 \bcke ESC zum speichern und verlassen");

            break;

        default:
            system ("cls");
            printf("\nEaster Egg");
    }
    return 0;
}


void CheckKey() {
    int WhereInMenu;
    int key;
    char KeyTouched;


    while (kbhit()) {
        key=getch();
        if (key == 13){                 //Normale TastenKeys werden abgefragt bevor das zweite Mal getch() ausgeführt wird.

            printf("Enter wurde gedrueckt. Die Funktion %d wird ausgeführt", WhereInMenu);
            //Funktion Ausführen
        }
        if (key == 27) {
            system ("cls");
            //Funktion zum Speichern ausführen
            exit(0);
        }
        if (key == 224) {
            do {
                key=getch();
            } while(key==224);
            switch (key) {
                case 72:                       //72 ist KeyCodeValue für Up-Arrow
                    //printf("up");
                    WhereInMenu--;
                    if (WhereInMenu < 1)
                    {
                        WhereInMenu = 6;
                    }
                    menuAnzeige(WhereInMenu,WhereInMenu);
                    break;

                case 80:                 //80 ist KeyCodeValue für Down-Arrow

                    WhereInMenu++;
                    if (WhereInMenu > 6)
                    {
                        WhereInMenu = 1;
                    }
                    menuAnzeige(WhereInMenu,WhereInMenu);

                    break;
            }
        }
    }}


int main() {
    menuAnzeige(1,1);
    while (1) {     //viele ressourcen
                     CheckKey();
        Sleep(10);   //spart Ressouren

}}