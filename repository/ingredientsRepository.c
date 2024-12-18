#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredientsRepository.h"

Ingredient* getAllIngredientsByIdIn(int ids[], int count) {
    int allIngredientsCount, matchedCount=0;
    Ingredient *ingredients = getAllIngredients(&allIngredientsCount);
    if (ingredients == NULL) {
        perror("Error allocating array");
        exit(1);
    }

    Ingredient *filteredIngredients = (Ingredient *) malloc(sizeof(Ingredient)*count);
    if (filteredIngredients == NULL) {
        perror("Error allocating array");
        exit(1);
    }

    for(int i = 0; i<allIngredientsCount; i++){
        for (int j = 0; j < count; j++){
            if(ids[j] == ingredients[i].id){
                filteredIngredients[j] = ingredients[i];
                matchedCount++;
            }
        }
    }
    free(ingredients);
    return matchedCount > 0 ? filteredIngredients : NULL; 
}

void saveIngredient(Ingredient ingredient) {
    Index index = readIndex();
    index.ingredientId++;
    FILE *f = fopen(INGREDIENTS_FILE_NAME, "a");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(f, "%d;%s;%.2f\n", index.ingredientId, ingredient.name, ingredient.extraPrice);

    writeNewIndex(index);
    fclose(f);
}

void saveIngredients(Ingredient* ingredients, int count) {
    FILE *f = fopen(INGREDIENTS_FILE_NAME, "w");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d;%s;%f\n", ingredients[i].id, ingredients[i].name, ingredients[i].extraPrice);
    }

    fclose(f);
}

void deleteIngredientById(int id){
    int count;
    Ingredient *ingredients = getAllIngredients(&count);
    if(ingredients == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    int found = 0;
    int newCount = 0;
    
    for (int i = 0; i < count; i++) {
        if (ingredients[i].id == id) {
            found = 1;
        } else {
            ingredients[newCount] = ingredients[i];
            newCount++;
        }
    }

    if (found) {
        printf("Ingrediente com '%d' excluído com sucesso!\n", id);
        saveIngredients(ingredients, newCount);
    } else {
        printf("Ingrediente com '%d' não encontrado!\n", id);
    }

    free(ingredients);
}

Ingredient* getAllIngredients(int* count) {
    FILE *f;
    f = fopen(INGREDIENTS_FILE_NAME, "r");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int numberOfIngredients = getNumberOfIngredients();
    (*count) = numberOfIngredients;

    Ingredient *ingredients = (Ingredient*)malloc(sizeof(Ingredient)*numberOfIngredients);
    if (ingredients == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int i=0;
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ";");
        ingredients[i].id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(ingredients[i].name, token);

        token = strtok(NULL, ";");
        ingredients[i].extraPrice=atof(token);

        i++;
    }
    
    fclose(f);

    return ingredients;
}

int getNumberOfIngredients() {
    return countItemsOnAFile(INGREDIENTS_FILE_NAME);
}

Ingredient* searchIngredientByName(char name[NAME_SIZE], int* count) {
    int countAll = 0;
    Ingredient *ingredients = getAllIngredients(&countAll);
    if(ingredients == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    Ingredient *found = malloc(sizeof(Ingredient)*countAll);
     if(found == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    for (int i =0; i<countAll; i++) {
        if(strcmp(ingredients[i].name, name) == 0){
            found[*count] = ingredients[i];
            (*count)++;
        }
    }

    free(ingredients);    
    return found;
}

Ingredient* searchIngredientById(int id) {
    int count;
    Ingredient *ingredients = getAllIngredients(&count);
    if(ingredients == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i =0; i<count; i++) {
        if(ingredients[i].id==id){
            Ingredient *found = malloc(sizeof(Ingredient));
            if (found != NULL) {
                *found = ingredients[i];
            }
            free(ingredients);
            return found; 
        }
    }

    free(ingredients);    
    return NULL;
}

void updateIngredient(Ingredient ingredient) {
    int count;
    Ingredient *ingredients = getAllIngredients(&count);

    for (int i = 0; i < count; i++) {
        if(ingredients[i].id == ingredient.id){
            strcpy(ingredients[i].name,ingredient.name);
            ingredients[i].extraPrice = ingredient.extraPrice;
        }
    }

    saveIngredients(ingredients, count);
    free(ingredients);
    return;
};