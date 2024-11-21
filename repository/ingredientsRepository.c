#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "ingredientsRepository.h"

Ingredient* getAllIngredientsByIdIn(int ids[], int count) {
    int allIngredientsCount;
    Ingredient *ingredients = getAllIngredients(&allIngredientsCount);
    Ingredient *filteredIngredients = (Ingredient *) malloc(sizeof(Ingredient)*count);

    for(int i = 0; i<allIngredientsCount; i++){
        for (int j = 0; j < count; j++){
            if(ids[j] == ingredients[i].id){
                filteredIngredients[j].id = ingredients[i].id;
                strcpy(filteredIngredients[j].name, ingredients[i].name);
                filteredIngredients[j].extraPrice = ingredients[i].extraPrice;
            }
        }
        
    }
    free(ingredients);
    return filteredIngredients;
}

void saveIngredient(Ingredient ingredient) {
    Index index = readIndex();
    index.ingredientId++;
    writeNewIndex(index);
    FILE *f = fopen(INGREDIENTS_FILE_NAME, "a");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(f, "%d;%s;%.2f\n", index.ingredientId, ingredient.name, ingredient.extraPrice);

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

void deleteIngredientByName(char name[]){
    int count;
    Ingredient *ingredients = getAllIngredients(&count);

    int found = 0;
    int newCount = 0;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(ingredients[i].name, name) == 0) {
            found = 1;
        } else {
            ingredients[newCount] = ingredients[i];
            newCount++;
        }
    }

    if (found) {
        printf("Ingrediente '%s' excluído com sucesso!\n", name);
        saveIngredients(ingredients, newCount);
    } else {
        printf("Ingrediente '%s' não encontrado!\n", name);
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
        strncpy(ingredients[i].name, token, NAME_SIZE);

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

Ingredient* searchIngredientByName(char name[NAME_SIZE]) {
    int count;
    Ingredient *ingredients = getAllIngredients(&count);
    for (int i =0; i<count; i++) {
        if(strcmp(ingredients[i].name, name) == 0){
            return &ingredients[i];
        }
    }

    free(ingredients);    
    return NULL;
};

void updateIngredient(Ingredient ingredient) {
    int count;
    Ingredient *ingredients = getAllIngredients(&count);

    for (int i = 0; i < count; i++) {
        if(ingredients[i].id == ingredient.id){
            stpcpy(ingredients[i].name,ingredient.name);
            for (int j = 0; j < 50; j++) {
            ingredients[i].extraPrice = ingredient.extraPrice;
        }
    }

    free(ingredients);
    return;
};