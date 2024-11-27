#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "ingredients.h"
#include "pizzas.h"

void printPizzasUseCase() {
    int count;
    Pizza *pizzas = getAllPizzas(&count);
    for (int i =0; i<count; i++) {
        Pizza pizza = pizzas[i];
        printf("Pizza ID: %d\n", pizza.id);
        printf("Sabor: %s\n", pizza.flavor);
        printf("Sabor: %c\n", pizza.size);
        printf("Preço: R$%.2f\n\n", pizza.price);
        if(pizza.ingredientsSize > 0){
            printf("Com ingredientes: \n");
            Ingredient *ingredients = getAllIngredientsByIdIn(pizza.ingredients, pizza.ingredientsSize);
            if(ingredients != NULL){
                for (int i =0; i<pizza.ingredientsSize; i++) {
                    printf("\t%s\n", ingredients[i].name);
                }
                free(ingredients);
                printf("\n");
            }
        }
    }
    
    printf("\n");
    free(pizzas);
}

void createPizzaUseCase() {
    while (getchar() != '\n'); 
    Pizza pizza;

    printf("Digite o sabor da pizza: ");
    fgets(pizza.flavor, NAME_SIZE, stdin);
    pizza.flavor[strcspn(pizza.flavor, "\n")] = '\0';

    printf("Digite o preço da pizza: ");
    scanf("%f", &pizza.price);

    char pizza_size;
    printf("Digite o tamanho da pizza: ");
    scanf(" %c", &pizza_size);
    pizza_size = toupper(pizza_size);
    
    if(pizza_size != P && pizza_size != M && pizza_size != G){
        printf("Não existe esse tamanho");
        return;
    }
    pizza.size=pizza_size;

    int ingredientsCount = getNumberOfIngredients();
    if(ingredientsCount == 0 ){
        printf("Voce nao tem ingredientes cadastrados deseja salvar mesmo assim? (s/n)\n");
        char resp;
        scanf(" %c", &resp);

        if (tolower(resp) != 's') {
            return;
        }
    } else {
        printf("Escreva o id do ingrediente que você quer adicionar na pizza ou digite 0 para sair: \n\n");
        printIngredientsUseCase();

        int value;
        printf("Ingrediente ID: ");
        scanf("%d", &value);
        while (value != 0 && pizza.ingredientsSize < INGREDIENTS_SIZE) {
            int values[1] = {value};
            Ingredient *ingredient = getAllIngredientsByIdIn(values, 1);
            if(ingredient != NULL){
                pizza.ingredients[pizza.ingredientsSize]=value;
                pizza.ingredientsSize++;
                free(ingredient);
            } else {
                printf("\nIngrediente não existe\n");
            }
            
            printf("Ingrediente ID: ");
            scanf("%d", &value);
        }
    }
    
    savePizza(pizza);
}

void deletePizzaUseCase() {
    while (getchar() != '\n');
    char flavorForDelete[NAME_SIZE];
    printf("Digite o sabor da pizza que quer deletar: ");
    fgets(flavorForDelete, NAME_SIZE, stdin);
    flavorForDelete[strcspn(flavorForDelete, "\n")] = '\0';
    deletePizzaByFlavor(flavorForDelete);
}

void updatePizzaUseCase() {
    while (getchar() != '\n');
    char flavorForUpdate[NAME_SIZE];
    printf("Digite o sabor da pizza que quer alterar: ");
    fgets(flavorForUpdate, NAME_SIZE, stdin);
    flavorForUpdate[strcspn(flavorForUpdate, "\n")] = '\0';

    Pizza *pizza = searchPizzaByFlavor(flavorForUpdate);

    if(pizza == NULL){
        printf("Pizza de sabor %s não encontrada", flavorForUpdate);
        return;
    }

    int value;
    do{
        printf("Menu de Opções Atualização da pizza:\n");
        printf("0 - Sair\n");
        printf("1 - Atualizar sabor da pizza\n");
        printf("2 - Atualizar valor da pizza\n");
        printf("3 - Adicionar ingredientes à pizza\n");
        printf("4 - Remover ingredientes da pizza\n");
        printf("Escolha uma opção: ");
        scanf("%d", &value);
        switch(value) {
            case 0:
                printf("Saindo da atualização da pizza...\n");
                break;
            case 1:
                printf("Opção selecionada: Atualizar sabor da pizza.\n");
                printf("Digite o sabor da pizza: ");
                while (getchar() != '\n');
                char newFlavor[NAME_SIZE];
                fgets(newFlavor, NAME_SIZE, stdin);
                newFlavor[strcspn(newFlavor, "\n")] = '\0';
                strcpy(pizza->flavor, newFlavor);
                printf("\n");
                break;
            case 2:
                printf("Opção selecionada: Atualizar valor da pizza.\n");
                printf("Digite o preço da pizza: ");
                scanf("%f", &pizza->price);
                printf("\n");
                break;
            case 3:
                printf("Opção selecionada: Adicionar ingredientes à pizza.\n");
                printIngredientsUseCase();
                int idIngrediente;
                scanf("%d", &idIngrediente);
                if(pizza->ingredientsSize == INGREDIENTS_SIZE){
                    printf("A quantidade de ingredientes da pizza já está no maximo");
                    return;
                }
                pizza->ingredients[pizza->ingredientsSize] = idIngrediente;
                pizza->ingredientsSize++;
                printf("\n");
                break;
            case 4:
                printf("Opção selecionada: Remover ingredientes da pizza.\n");
                printIngredientsUseCase();
                int idIngredienteRemove;
                scanf("%d", &idIngredienteRemove);
                if(pizza->ingredientsSize == 0){
                    printf("A quantidade de ingredientes da pizza já está no minimo");
                    return;
                }
                for(int i = 0; i<pizza->ingredientsSize; i++){
                    if(pizza->ingredients[i] == idIngredienteRemove){
                        pizza->ingredients[i] = pizza->ingredients[pizza->ingredientsSize];
                    }
                }
                pizza->ingredients[pizza->ingredientsSize] = 0;
                pizza->ingredientsSize--;
                printf("\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(value != 0);

    updatePizza(*pizza);
    free(pizza);
}

void sellPizzaUseCase() {  
    printPizzasUseCase();

    int procura_id, count;
    printf("Selecione o ID da pizza que quer vender: ");
    scanf("%d", &procura_id);

    Pizza *pizzas = getAllPizzas(&count);
    if(pizzas == NULL || count ==0){
        printf("Nao tem pizzas cadastradas\n");
        return;
    }

    Pizza *foundPizza = NULL;

    for (int i = 0; i < count && foundPizza == NULL; i++) {
        if (procura_id == pizzas[i].id) {
            foundPizza = &pizzas[i];
        }
    }

    if (foundPizza == NULL) {
        printf("Pizza não encontrada.\n");
        return;
    }

    char addIngredients;
    float precoExtra = 0;

    printf("Deseja adicionar ingredientes extras? (s/n): ");
    scanf(" %c", &addIngredients);

    if (tolower(addIngredients) == 's') {
        int idIngredients = -1, quantidade, ingredientCount;
        Ingredient *ingredients = getAllIngredients(&ingredientCount);

        printIngredientsUseCase();
        printf("Digite o ID do ingrediente que deseja adicionar (0 para finalizar): ");
        scanf("%d", &idIngredients);

        while (idIngredients != 0) {
            Ingredient *foundIngredient = NULL;

            for (int i = 0; i < ingredientCount && foundIngredient == NULL; i++) {
                if (idIngredients == ingredients[i].id) {
                    foundIngredient = &ingredients[i];
                }
            }

            if (foundIngredient == NULL) {
                printf("Ingrediente não encontrado.\n");
            } else {
                printf("Digite a quantidade do ingrediente adicional: ");
                scanf("%d", &quantidade);

                if (quantidade < 0) {
                    printf("Quantidade inválida. Tente novamente.\n");
                }

                precoExtra += foundIngredient->extraPrice * quantidade;
            }

            printIngredientsUseCase();
            printf("Digite o ID do ingrediente que deseja adicionar (0 para finalizar): ");
            scanf("%d", &idIngredients);
        }
        free(ingredients);
    }

    float precoFinal = foundPizza->price + precoExtra;
    printf("\nResumo do pedido:\n");
    printf("Pizza: %s (R$ %.2f)\n", foundPizza->flavor, foundPizza->price);
    printf("Adicionais: R$ %.2f\n", precoExtra);
    printf("Total a pagar: R$ %.2f\n\n", precoFinal);

    free(pizzas);
    return;
}
