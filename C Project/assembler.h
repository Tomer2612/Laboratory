#ifndef ASSEMBLER_H
#define ASSEMBLER_H

/* מריץ את שני מעברי האסמבלר:
 * 1. בניית טבלת סמלים.
 * 2. תרגום סופי וכתיבת קבצי פלט (.ob, .ent, .ext)
 * מחזיר 1 בהצלחה, 0 בכישלון.
 */
int runAssembler(const char *filename);

#endif

