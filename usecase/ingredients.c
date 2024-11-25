#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "ingredients.h"

void printIngredientsUseCase(){
    int count;
    Ingredient *ingredients = getAllIngredients(&count);
    for (int i =0; i<count; i++) {
        Ingredient ingredient = ingredients[i];
        printf("Ingrediente ID: %d\n", ingredient.id);
        printf("Nome: %s\n", ingredient.name);
        printf("Preço: R$%.2f\n\n", ingredient.extraPrice);
        printf("\n");
    }

    printf("\n");
    free(ingredients);
}

void createIngredientUseCase(){
    while (getchar() != '\n'); 

    Ingredient ingredient;

    printf("Digite o nome do ingredient: ");
    fgets(ingredient.name, NAME_SIZE, stdin);
    ingredient.name[strcspn(ingredient.name, "\n")] = '\0';

    printf("Digite o preço extra do ingredient: \n");
    scanf("%f", &ingredient.extraPrice);
    
    saveIngredient(ingredient);
}

void deleteIngredientUseCase(){
    while (getchar() != '\n');
    char ingredientName[NAME_SIZE];
    printf("Digite o nome do ingredient para deletar: ");
    fgets(ingredientName, NAME_SIZE, stdin);
    ingredientName[strcspn(ingredientName, "\n")] = '\0';
    deleteIngredientByName(ingredientName);
}

void updateIngredientUseCase(){
    char nameForUpdate[NAME_SIZE];
    printf("Digite o ingrediente que quer alterar: ");
    fgets(nameForUpdate, NAME_SIZE, stdin);
    nameForUpdate[strcspn(nameForUpdate, "\n")] = '\0';
    Ingredient *ingredient = searchIngredientByName(nameForUpdate);

    if(ingredient == NULL){
        printf("Ingrediente %s não encontrada", nameForUpdate);
        free(ingredient);
        return;
    }

    int value;
    do{
        printf("Menu de Opções Atualização do ingrediente:\n");
        printf("0 - Sair\n");
        printf("1 - Atualizar nome do ingrediente\n");
        printf("2 - Atualizar valor do ingrediente\n");
        scanf("%d", &value);
        switch(value) {
            case 0:
                printf("Saindo da atualização do ingrediente...\n");
                break;
            case 1:
                printf("Opção selecionada: Atualizar sabor da pizza.\n");
                printf("Digite o sabor da pizza: ");
                fgets(ingredient->name, NAME_SIZE, stdin);
                printf("\n");
                break;
            case 2:
                printf("Opção selecionada: Atualizar valor da pizza.\n");
                printf("Digite o preço da pizza: ");
                scanf("%f", &ingredient->extraPrice);
                printf("\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(value != 0);


    updateIngredient(*ingredient);
    free(ingredient);
};