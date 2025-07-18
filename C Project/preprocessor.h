#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

/* מריץ את קדם האסמבלר על קובץ מקור.
 * יוצר קובץ .am אחרי פרישת המאקרואים.
 * מחזיר 1 בהצלחה, 0 בכישלון.
 */
int runPreprocessor(const char *filename);

#endif

