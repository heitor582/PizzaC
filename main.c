#include<stdio.h>
#include <stdlib.h>
#include "./usecase/pizzas.h"
#include "./usecase/ingredients.h"

void menu();
void cleanTerminal();

int main() {
    menu();
}

void cleanTerminal() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void menu() {
    int value;
    do {
        printf("Menu de Opções:\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar uma pizza\n");
        printf("2 - Ver todas as pizzas\n");
        printf("3 - Atualizar uma pizza\n");
        printf("4 - Deletar uma pizza\n");
        printf("5 - Cadastrar um ingrediente\n");
        printf("6 - Ver todos os ingredientes\n");
        printf("7 - Atualizar um ingrediente\n");
        printf("8 - Deletar um ingrediente\n");
        printf("Escolha uma opção: ");

        scanf("%d", &value);
        switch(value) {
            case 0:
                cleanTerminal();
                printf("Saindo do programa...\n");
                break;
            case 1:
                cleanTerminal();
                printf("Cadastrar uma pizza selecionado.\n");
                createPizzaUseCase();
                printf("\n");
                break;
            case 2:
                cleanTerminal();
                printf("Ver todas as pizzas selecionado.\n");
                printPizzasUseCase();
                printf("\n");
                break;
            case 3:
                cleanTerminal();
                printf("Atualizar uma pizza selecionado.\n");
                updatePizzaUseCase();
                printf("\n");
                break;
            case 4:
                cleanTerminal();
                printf("Deletar uma pizza selecionado.\n");
                deletePizzaUseCase();
                printf("\n");
                break;
            case 5:
                cleanTerminal();
                printf("Cadastrar um ingrediente selecionado.\n");
                createIngredientUseCase();
                printf("\n");
                break;
            case 6:
                cleanTerminal();
                printf("Ver todos os ingredientes selecionado.\n");
                printIngredientsUseCase();
                printf("\n");
                break;
            case 7:
                cleanTerminal();
                printf("Atualizar um ingrediente selecionado.\n");
                // updateIngredientUseCase();
                printf("\n");
                break;
            case 8:
                cleanTerminal();
                printf("Deletar um ingrediente selecionado.\n");
                deleteIngredientUseCase();
                printf("\n");
                break;
            default:
                cleanTerminal();
                printf("Opção inválida. Tente novamente.\n");
                printf("\n");
        }
    } while(value != 0);
    return;
}