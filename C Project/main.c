

/*
 * main.c - קובץ ההפעלה הראשי
 * מקבל שמות קבצי מקור, מפעיל קדם-אסמבלר ואז אסמבלר.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preprocessor.h"
#include "assembler.h"

int main(int argc, char *argv[]) {
    int i = 0;
    char *filename;

    if (argc < 2) {
        printf("שגיאה: לא סופקו קבצי מקור.\n");
        return 1;
    }


    for (i = 1; i < argc; i++) {
        filename = argv[i];
        printf("מעבד קובץ: %s.as\n", filename);

        if (!runPreprocessor(filename)) {
            printf("שגיאה בשלב קדם האסמבלר.\n");
            continue;
        }

        if (!runAssembler(filename)) {
            printf("שגיאה בשלב האסמבלר.\n");
            continue;
        }

        printf("✅ קובץ %s טופל בהצלחה!\n", filename);
    }

    return 0;
}

