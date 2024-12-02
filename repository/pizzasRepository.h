#ifndef PIZZAREPOSITORY_H
#define PIZZAREPOSITORY_H

#include "indexRepository.h"
#include "ingredientsRepository.h"

#define PIZZA_FILE_NAME "./db/pizza.csv"
#define MAX_INGREDIENTS_LINE_LENGTH 140
#define INGREDIENTS_SIZE 50

enum PIZZA_SIZE {
  G = 'G',
  M = 'M',
  P = 'P'
};

typedef struct Pizza{
    int id;
    float price;
    char flavor[NAME_SIZE];
    enum PIZZA_SIZE size;
    int ingredients[INGREDIENTS_SIZE];
    int ingredientsSize;
} Pizza;

Pizza* getAllPizzas(int* count);
void savePizza(Pizza pizza);
void deletePizzaById(int id);
void updatePizza(Pizza pizza);
Pizza* searchPizzaByFlavor(char flavor[NAME_SIZE], int* count);
Pizza* searchPizzaById(int id);
int getNumberOfPizzas();

#endif