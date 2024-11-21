#include <stdio.h>
#include <stdlib.h>
#include "indexRepository.h"

int countItemsOnAFile(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int count = 0;
    char line[1024];

    while (fgets(line, sizeof(line), f) != NULL) {
        count++;
    }

    fclose(f);
    return count;
}
void writeNewIndex(Index index) {
    FILE *f = fopen(INDEX_FILE_NAME, "wb");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fwrite(&index, sizeof(Index), 1, f);

    fclose(f);
}
Index readIndex(){
    FILE *f = fopen(INDEX_FILE_NAME, "rb");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    Index index;
    fread(&index, sizeof(Index), 1, f);

    fclose(f);

    return index;
}