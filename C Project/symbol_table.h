#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_LABEL_LEN 31
#define MAX_ATTR_LEN 10

typedef struct Symbol {
    char name[MAX_LABEL_LEN];
    int address;
    char attribute[MAX_ATTR_LEN];
    struct Symbol *next;
} Symbol;

/* מוסיף סמל חדש לטבלה */
void addSymbol(const char *name, int address, const char *attribute);

/* מחפש סמל בטבלה לפי שם */
Symbol* findSymbol(const char *name);

/* מדפיס את כל הסמלים בטבלה (debug) */
void printSymbolTable();

/* משחרר את כל הזיכרון של הטבלה */
void freeSymbolTable();

#endif

