#ifndef INDEXREPOSITORY_H
#define INDEXREPOSITORY_H

#define INDEX_FILE_NAME "./db/index.bin"
#define MAX_LINE_LENGTH 255
#define NAME_SIZE 50

typedef struct Index {
    int pizzaId;
    int ingredientId;
} Index;

void writeNewIndex(Index index);
Index readIndex();
int countItemsOnAFile(char *filename);
#endif