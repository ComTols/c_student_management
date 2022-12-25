#include "main.h"
/*
int main(int argc, char *argv[]) {
    Json out = json_mkJson(JSON_OBJ);

    Json list = json_mkJson(JSON_LIST);
    json_list_push_string(&list, "string");
    json_list_push_float(&list, 1.23f);
    json_list_push_null(&list);

    Json list2 = json_mkJson(JSON_LIST);
    json_list_push_string(&list2, "halloeschen");
    json_list_push_float(&list2, 4.56f);
    json_list_push_null(&list2);

    json_obj_put(&out, "lst1", &list);
    json_obj_put(&out, "lst2", &list2);

    json_obj_put_string(&out, "str5", "meineguete");
    json_obj_put_float(&out, "data", 6.78f);

    int n;
    char *str = json_dump(out, &n);
    printf("%s\n", str);

    free(str);
    getchar();

    //json_free(&out);

    return 0;
}
#include "console.h"
*/
int main() {

    LinkedList *students = load();

    Student* head = (Student *)students->head->value;

    int menuSize;
    int menuPosition = 0;
    MenuItem *menu = con_mkMenu(&menuSize);
    con_redraw(menu, menuSize, &menuPosition);
    while (1) {
        con_input(menu, menuSize, &menuPosition, students);
    }

    /*while (1) {
        printf("%d\n", getch());
    }*/
}