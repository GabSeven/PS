# Makefile para compilar código C no Windows

# Compilador
CC = gcc

# Flags (adicione -m32 se quiser gerar código de 32 bits)
CFLAGS = -Wall -O2

# Arquivos
SRC = trabalho.c
OBJ = trabalho.o
TARGET = trabalho.exe

# Regra principal
all: $(TARGET)

# Compilação
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

# Linkagem
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Limpeza
clean:
	del /Q $(TARGET) $(OBJ)