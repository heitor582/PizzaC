# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target
TARGET = pizza

# Directories
USECASE_DIR = usecase
REPO_DIR = repository

# Source and header files
SRC = main.c $(USECASE_DIR)/pizzas.c $(USECASE_DIR)/ingredients.c \
      $(REPO_DIR)/pizzasRepository.c $(REPO_DIR)/ingredientsRepository.c \
      $(REPO_DIR)/indexRepository.c

HEADERS = $(USECASE_DIR)/pizzas.h $(USECASE_DIR)/ingredients.h \
          $(REPO_DIR)/pizzasRepository.h $(REPO_DIR)/ingredientsRepository.h \
          $(REPO_DIR)/indexRepository.h

# Object files
OBJ = $(SRC:.c=.o)

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile source files into object files, considering header dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove build artifacts
clean:
	rm -f $(OBJ) $(TARGET)
