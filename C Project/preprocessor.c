/*
 * preprocessor.c - קדם אסמבלר עם פרישת מאקרואים בסיסית
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "preprocessor.h"
#include "utils.h"

#define MAX_LINE_LEN 80
#define MAX_MACROS 50
#define MAX_MACRO_NAME 31
#define MAX_MACRO_BODY 1000

/* מבנה של מאקרו */
typedef struct {
    char name[MAX_MACRO_NAME];
    char body[MAX_MACRO_BODY];
} Macro;

static Macro macroTable[MAX_MACROS];
static int macroCount = 0;

/* בודק אם שם מאקרו כבר קיים בטבלה */
int macroExists(const char *name) {
    int i;
    for (i = 0; i < macroCount; i++) {
        if (strcmp(macroTable[i].name, name) == 0)
            return 1;
    }
    return 0;
}

/* מוסיף מאקרו לטבלה */
void addMacro(const char *name, const char *body) {
    if (macroCount >= MAX_MACROS) {
        printf("שגיאה: מספר המאקרואים חרג מהמותר\n");
        exit(1);
    }
    strcpy(macroTable[macroCount].name, name);
    strcpy(macroTable[macroCount].body, body);
    macroCount++;
}

/* מחפש מאקרו בטבלה ומחזיר מצביע לגוף שלו */
const char* getMacroBody(const char *name) {
    int i;
    for (i = 0; i < macroCount; i++) {
        if (strcmp(macroTable[i].name, name) == 0)
            return macroTable[i].body;
    }
    return NULL;
}

/* מריץ קדם-אסמבלר עם פרישת מאקרואים */
int runPreprocessor(const char *filename) {
    FILE *infile, *outfile;
    char inputFileName[100];
    char outputFileName[100];
    char line[MAX_LINE_LEN + 2];
    char macroBody[MAX_MACRO_BODY];
    char macroName[MAX_MACRO_NAME];
    int inMacro = 0;
    int lineNumber = 0;

    sprintf(inputFileName, "%s.as", filename);
    sprintf(outputFileName, "%s.am", filename);

    infile = fopen(inputFileName, "r");
    if (infile == NULL) {
        printf("שגיאה: לא ניתן לפתוח את %s\n", inputFileName);
        return 0;
    }

    outfile = fopen(outputFileName, "w");
    if (outfile == NULL) {
        printf("שגיאה: לא ניתן ליצור את %s\n", outputFileName);
        fclose(infile);
        return 0;
    }

    while (fgets(line, sizeof(line), infile) != NULL) {
        char word[MAX_MACRO_NAME];
        const char* body;
        lineNumber++;

        if (strlen(line) > MAX_LINE_LEN) {
            printError(lineNumber, "שורה ארוכה מדי (>80 תווים)");
        }

        if (inMacro) {
            if (strncmp(line, "mcroend", 7) == 0) {
                addMacro(macroName, macroBody);
                inMacro = 0;
                macroBody[0] = '\0';
            } else {
                strcat(macroBody, line);
            }
        } else {
            if (strncmp(line, "mcro", 4) == 0) {
                if (sscanf(line, "mcro %s", macroName) != 1) {
                    printError(lineNumber, "שם מאקרו חסר");
                    fclose(infile);
                    fclose(outfile);
                    return 0;
                }
                if (macroExists(macroName)) {
                    printError(lineNumber, "מאקרו מוגדר פעמיים");
                    fclose(infile);
                    fclose(outfile);
                    return 0;
                }
                inMacro = 1;
                macroBody[0] = '\0';
            } else {
                sscanf(line, "%s", word);
                body = getMacroBody(word);
                if (body != NULL) {
                    fprintf(outfile, "%s", body);
                } else {
                    fprintf(outfile, "%s", line);
                }
            }
        }
    }

    fclose(infile);
    fclose(outfile);

    printf("[Preprocessor] נוצר %s בהצלחה! נמצאו %d מאקרואים.\n", outputFileName, macroCount);
    return 1;
}



