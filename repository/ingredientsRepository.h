#ifndef INGREDIENTSREPOSITORY_H
#define INGREDIENTSREPOSITORY_H

#include "indexRepository.h"

#define INGREDIENTS_FILE_NAME "./db/ingredients.csv"

typedef struct Ingredient{
    int id;
    char name[NAME_SIZE];
    float extraPrice;
} Ingredient;

Ingredient* getAllIngredientsByIdIn(int ids[], int count);
Ingredient* getAllIngredients(int* count);
Ingredient* searchIngredientByName(char name[NAME_SIZE]);
void updateIngredient(Ingredient ingredient);
void saveIngredient(Ingredient ingredient);
void deleteIngredientByName(char name[]);
int getNumberOfIngredients();

#endif