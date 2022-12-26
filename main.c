#include "main.h"

int main() {
   LinkedList *students = load();

    int menuSize;
    int menuPosition = 0;
    MenuItem *menu = con_mkMenu(&menuSize);
    con_redraw(menu, menuSize, &menuPosition);
    while (1) {
        con_input(menu, menuSize, &menuPosition, students);
    }
}