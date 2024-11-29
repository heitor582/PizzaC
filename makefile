CC = gcc
CFLAGS = -Wall -g
TARGET = pizza
USECASE_DIR = usecase
REPO_DIR = repository

SRC = main.c $(USECASE_DIR)/pizzas.c $(USECASE_DIR)/ingredients.c \
      $(REPO_DIR)/pizzasRepository.c $(REPO_DIR)/ingredientsRepository.c \
      $(REPO_DIR)/indexRepository.c

HEADERS = $(USECASE_DIR)/pizzas.h $(USECASE_DIR)/ingredients.h \
          $(REPO_DIR)/pizzasRepository.h $(REPO_DIR)/ingredientsRepository.h \
          $(REPO_DIR)/indexRepository.h

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)


DB_DIR = db
INDEX_FILE = $(DB_DIR)/index.bin
PIZZA_FILE = $(DB_DIR)/pizza.csv
INGREDIENT_FILE = $(DB_DIR)/ingredients.csv
INPUT_FILE = test/pub.in
EXPECTED_OUTPUT_FILE = test/pub.out
ACTUAL_OUTPUT_FILE = test/pub.actual.out

.PHONY: test
test:
	@echo "Limpando arquivos antigos..."
	@rm -rf $(DB_DIR) $(ACTUAL_OUTPUT_FILE)
	@echo "Criando pasta '$(DB_DIR)'..."
	@mkdir -p $(DB_DIR)
	@touch $(INDEX_FILE) $(PIZZA_FILE) $(INGREDIENT_FILE)
	@printf '\x00\x00\x00\x00\x00\x00\x00\x00' > $(INDEX_FILE)
	@echo "Compilando o programa..."
	@make
	@echo "Executando o teste..."
	@./pizza < $(INPUT_FILE) > $(ACTUAL_OUTPUT_FILE)
	@diff -u $(EXPECTED_OUTPUT_FILE) $(ACTUAL_OUTPUT_FILE) && \
		echo "Teste passou! As saídas são iguais." || \
		(echo "Teste falhou. Veja a diferença acima." && exit 1)
	@make clean
	@printf '\x00\x00\x00\x00\x00\x00\x00\x00' > $(INDEX_FILE)