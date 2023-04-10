CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

APP_NAME = app

GEOMETRY_OBJ = $(OBJ_DIR)/geometry/main.o
GEOMETRY_CALC_OBJ = $(OBJ_DIR)/libgeometry/lab1.o

APP_DEPS = $(GEOMETRY_OBJ) $(GEOMETRY_CALC_OBJ)
APP_OBJ = $(BIN_DIR)/$(APP_NAME)

.PHONY: all clean

all: $(APP_OBJ)

$(APP_OBJ): $(APP_DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(GEOMETRY_OBJ): $(SRC_DIR)/geometry/main.c | $(OBJ_DIR)/geometry
	$(CC) $(CFLAGS) -c -o $@ $<

$(GEOMETRY_CALC_OBJ): $(SRC_DIR)/libgeometry/lab1.c | $(OBJ_DIR)/libgeometry
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Используем include для автоматической генерации зависимостей из исходных файлов
-include $(OBJ_DIR)/geometry/main.d $(OBJ_DIR)/libgeometry/lab1.d

$(OBJ_DIR)/geometry:
	mkdir -p $@

$(OBJ_DIR)/libgeometry:
	mkdir -p $@