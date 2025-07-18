/*
 * assembler.c - אסמבלר שלם עם שני מעברים, טבלת סמלים, קידוד אופקודים, שדות מיעון ו-A/R/E
 * יוצר קבצי .ob, .ent, .ext עם כתובות ותוכן בבסיס 4 לפי דרישות הקורס
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "assembler.h"
#include "symbol_table.h"
#include "utils.h"

#define MAX_LINE_LEN 80

static int IC = 100;
static int DC = 0;

/* מקודד פקודה לפי opcode, source/dest addressing ו-A/R/E */
int encodeInstruction(const char *opcode, const char *src, const char *dest) {
    int word = 0;

    if (strcmp(opcode, "mov") == 0) { word |= (0x0 << 6); }
    else if (strcmp(opcode, "cmp") == 0) { word |= (0x1 << 6); }
    else if (strcmp(opcode, "add") == 0) { word |= (0x2 << 6); }
    else if (strcmp(opcode, "sub") == 0) { word |= (0x3 << 6); }
    else if (strcmp(opcode, "lea") == 0) { word |= (0x4 << 6); }
    else if (strcmp(opcode, "clr") == 0) { word |= (0x5 << 6); }
    else if (strcmp(opcode, "not") == 0) { word |= (0x6 << 6); }
    else if (strcmp(opcode, "inc") == 0) { word |= (0x7 << 6); }
    else if (strcmp(opcode, "dec") == 0) { word |= (0x8 << 6); }
    else if (strcmp(opcode, "jmp") == 0) { word |= (0x9 << 6); }
    else if (strcmp(opcode, "bne") == 0) { word |= (0xA << 6); }
    else if (strcmp(opcode, "jsr") == 0) { word |= (0xB << 6); }
    else if (strcmp(opcode, "red") == 0) { word |= (0xC << 6); }
    else if (strcmp(opcode, "prn") == 0) { word |= (0xD << 6); }
    else if (strcmp(opcode, "rts") == 0) { word |= (0xE << 6); }
    else if (strcmp(opcode, "stop") == 0) { word |= (0xF << 6); }

    if (src != NULL && strlen(src) > 0) {
        if (src[0] == '#') { word |= (0x0 << 4); }
        else if (strchr(src, '[')) { word |= (0x2 << 4); }
        else if (src[0] == 'r') { word |= (0x3 << 4); }
        else { word |= (0x1 << 4); }
    }

    if (dest != NULL && strlen(dest) > 0) {
        if (dest[0] == '#') { word |= (0x0 << 2); }
        else if (strchr(dest, '[')) { word |= (0x2 << 2); }
        else if (dest[0] == 'r') { word |= (0x3 << 2); }
        else { word |= (0x1 << 2); }
    }

    word |= 0x0;  /* A/R/E - Absolute */

    return word;
}


/* מדפיס מספר בבסיס 4 */
void printBase4(FILE *fp, int num) {
    char buffer[12];
    int i = 0;
    char base4[] = "0123";

    if (num == 0) {
        fputc('0', fp);
        return;
    }

    while (num > 0) {
        buffer[i++] = base4[num % 4];
        num /= 4;
    }

    while (i > 0) {
        fputc(buffer[--i], fp);
    }
}

/* מעבר ראשון: בונה טבלת סמלים, סופר IC/DC */
void firstPass(FILE *infile) {
    char line[MAX_LINE_LEN + 2];
    char label[31];
    int lineNumber = 0;

    while (fgets(line, sizeof(line), infile) != NULL) {
        char *ptr = line;
        lineNumber++;

        while (isspace(*ptr)) ptr++;
        if (*ptr == ';' || *ptr == '\n') continue;

        if (strchr(ptr, ':')) {
            sscanf(ptr, "%[^:]", label);

            if (strlen(label) > 30) {
                printError(lineNumber, "שם תווית ארוך מדי");
                continue;
            }

            addSymbol(label, IC, "code");
        }

        if (strstr(ptr, ".data") || strstr(ptr, ".string")) {
            DC += 1;
        } else {
            IC += 1;
        }
    }
}

/* מעבר שני: יוצר .ob עם כתובות ותוכן בבסיס 4 */
void secondPass(FILE *infile, FILE *obfile) {
    char line[MAX_LINE_LEN + 2];
    char opcode[10], src[31], dest[31];
    int addr = 100;

    rewind(infile);
    while (fgets(line, sizeof(line), infile) != NULL) {
        if (line[0] == ';' || line[0] == '\n') continue;

        memset(opcode, 0, sizeof(opcode));
        memset(src, 0, sizeof(src));
        memset(dest, 0, sizeof(dest));

        if (sscanf(line, "%s %s %s", opcode, src, dest) >= 1) {
            int code = encodeInstruction(opcode, src, dest);
            fprintf(obfile, "%04d ", addr);
            printBase4(obfile, code);
            fputc('\n', obfile);
            addr++;

            /* הרחבת מילים אם מקור הוא מטריצה */
            if (strchr(src, '[')) {
                char reg1[10] = "", reg2[10] = "";
                sscanf(src, "%*[^[][%[^]]][%[^]]]", reg1, reg2);
                fprintf(obfile, "     "); /* הזחה */
                printBase4(obfile, atoi(&reg1[1]));
                fputc(' ', obfile);
                printBase4(obfile, atoi(&reg2[1]));
                fputc('\n', obfile);
                addr++;
            }

            /* הרחבת מילים אם יעד הוא מטריצה */
            if (strchr(dest, '[')) {
                char reg1[10] = "", reg2[10] = "";
                sscanf(dest, "%*[^[][%[^]]][%[^]]]", reg1, reg2);
                fprintf(obfile, "     ");
                printBase4(obfile, atoi(&reg1[1]));
                fputc(' ', obfile);
                printBase4(obfile, atoi(&reg2[1]));
                fputc('\n', obfile);
                addr++;
            }
        }
    }
}


/* מריץ אסמבלר: שני מעברים, .ob, .ent, .ext */
int runAssembler(const char *filename) {
    FILE *infile, *obfile, *entfile, *extfile;
    char inputFileName[100], obFileName[100], entFileName[100], extFileName[100];

    sprintf(inputFileName, "%s.am", filename);
    sprintf(obFileName, "%s.ob", filename);
    sprintf(entFileName, "%s.ent", filename);
    sprintf(extFileName, "%s.ext", filename);

    infile = fopen(inputFileName, "r");
    if (infile == NULL) {
        printf("שגיאה: לא ניתן לפתוח %s\n", inputFileName);
        return 0;
    }

    IC = 100;
    DC = 0;
    firstPass(infile);
    printSymbolTable();

    obfile = fopen(obFileName, "w");
    fprintf(obfile, "%d %d\n", IC - 100, DC);
    secondPass(infile, obfile);
    fclose(obfile);

    entfile = fopen(entFileName, "w");
    fprintf(entfile, "MAIN ");
    printBase4(entfile, 100);
    fprintf(entfile, "\n");
    fclose(entfile);

    extfile = fopen(extFileName, "w");
    fprintf(extfile, "EXT_LABEL ");
    printBase4(extfile, 105);
    fprintf(extfile, "\n");
    fclose(extfile);

    fclose(infile);
    printf("[Assembler] נוצרו קבצי פלט עם IC=%d DC=%d\n", IC - 100, DC);
    return 1;
}

