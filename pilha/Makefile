CC = gcc
CFLAGS = -Wall -Wextra -g

# Fontes
SRCS = teste.c fila_dinamica.c fila_hierarquica.c
HEADERS = fila_dinamica.h fila_hierarquica.h
OBJS = $(SRCS:.c=.o)

# Nome do executável
TARGET = teste

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)