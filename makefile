TARGET = pizza

USECASE_DIR = usecase
REPO_DIR = repository

SRC = main.c $(USECASE_DIR)/pizzas.c $(USECASE_DIR)/ingredients.c \
      $(REPO_DIR)/pizzasRepository.c $(REPO_DIR)/ingredientsRepository.c \
      $(REPO_DIR)/indexRepository.c

INCLUDE = $(USECASE_DIR)/pizzas.h $(USECASE_DIR)/ingredients.h \
          $(REPO_DIR)/pizzasRepository.h $(REPO_DIR)/ingredientsRepository.h \
          $(REPO_DIR)/indexRepository.h

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
