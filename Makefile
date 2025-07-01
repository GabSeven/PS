# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Project files
SRC = IEEE_representacao.c
OBJ = $(SRC:.c=.o)
EXEC = my_program

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compiling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean
