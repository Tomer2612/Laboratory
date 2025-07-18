/*
 * utils.c - פונקציות עזר כלליות
 */

#include <stdio.h>
#include "utils.h"

/* מדפיס הודעת שגיאה עם מספר שורה */
void printError(int lineNumber, const char *message) {
    printf("שגיאה בשורה %d: %s\n", lineNumber, message);
}

