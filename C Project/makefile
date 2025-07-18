# הגדרות כלליות
CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJFILES = main.o preprocessor.o assembler.o symbol_table.o utils.o

# קובץ ההרצה הסופי
TARGET = assembler

# יעד ברירת מחדל
all: $(TARGET)

# קישור כל קבצי ה-object
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

# קומפילציה של כל מקור
main.o: main.c preprocessor.h assembler.h
	$(CC) $(CFLAGS) -c main.c

preprocessor.o: preprocessor.c preprocessor.h utils.h
	$(CC) $(CFLAGS) -c preprocessor.c

assembler.o: assembler.c assembler.h symbol_table.h utils.h
	$(CC) $(CFLAGS) -c assembler.c

symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# ניקוי כל הקבצים שנבנו
clean:
	rm -f $(TARGET) *.o *.ob *.am *.ent *.ext

