# Makefile PRUEBAS - Proyecto de Simulador Interactivo de Microrred en C
# IE-0117 - I-2026

CC     = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11
VALGRIND = -Iinclude -g -O0 
TARGET = prueba_interfaz
SRC_DIR = src
COMPLETO = $(SRC_DIR)/main_prueba.c $(SRC_DIR)/componentes.c $(SRC_DIR)/interfaz.c
.PHONY: all clean run

all: $(TARGET)

$(TARGET):  
	$(CC) $(CFLAGS) $(LDFLAGS)  $(COMPLETO) -o $(TARGET)

run: all
	./$(TARGET)
debug: clean
	$(CC) $(VALGRIND) $(LDFLAGS)  $(COMPLETO) -o $(TARGET)

valgrind: debug
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET)
