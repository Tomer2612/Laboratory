/*
 * symbol_table.c - מממש רשימה מקושרת של סמלים
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static Symbol *head = NULL;

/* מוסיף סמל חדש לטבלה */
void addSymbol(const char *name, int address, const char *attribute) {
    Symbol *newSymbol = (Symbol*)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    newSymbol->address = address;
    strcpy(newSymbol->attribute, attribute);
    newSymbol->next = head;
    head = newSymbol;
}

/* מחפש סמל בטבלה לפי שם */
Symbol* findSymbol(const char *name) {
    Symbol *current = head;
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

/* מדפיס את טבלת הסמלים (לבדיקות) */
void printSymbolTable() {
    Symbol *current = head;
    printf("=== טבלת סמלים ===\n");
    while (current) {
        printf("%s\t%d\t%s\n", current->name, current->address, current->attribute);
        current = current->next;
    }
}

/* משחרר את טבלת הסמלים מהזיכרון */
void freeSymbolTable() {
    Symbol *current = head;
    while (current) {
        Symbol *tmp = current;
        current = current->next;
        free(tmp);
    }
    head = NULL;
}

