#!/bin/bash

make clean

DB_DIR="db"
INDEX_FILE="$DB_DIR/index.bin"
PIZZA_FILE="$DB_DIR/pizza.csv"
INGREDIENT_FILE="$DB_DIR/ingredients.csv"

if [ -d "$DB_DIR" ]; then
    echo "Removendo pasta existente '$DB_DIR'..."
    rm -rf "$DB_DIR"
fi

mkdir "$DB_DIR"

touch "$INDEX_FILE" "$PIZZA_FILE" "$INGREDIENT_FILE"

printf '\x00\x00\x00\x00' > "$INDEX_FILE"

make

INPUT_FILE="test/pub.in"
EXPECTED_OUTPUT_FILE="test/pub.out"
ACTUAL_OUTPUT_FILE="test/pub.actual.out"

./pizza < "$INPUT_FILE" > "$ACTUAL_OUTPUT_FILE"

diff -u "$EXPECTED_OUTPUT_FILE" "$ACTUAL_OUTPUT_FILE"
if [ $? -eq 0 ]; then
    echo "Teste passou! As saídas são iguais."
else
    echo "Teste falhou. Veja a diferença acima."
fi
