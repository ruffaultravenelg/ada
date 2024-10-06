# Répertoires
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -L$(LIB_DIR) -lSDL2

# Fichiers sources et objets
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nom de l'exécutable
EXECUTABLE = $(BIN_DIR)/ada.exe

# Chemin vers la DLL
SDL2_DLL = $(LIB_DIR)\SDL2.dll

# Règle par défaut
all: $(EXECUTABLE) copy-dll

# Création de l'exécutable
$(EXECUTABLE): $(OBJECTS)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Copier la DLL dans le répertoire de l'exécutable
copy-dll:
	@if exist "$(SDL2_DLL)" (copy "$(SDL2_DLL)" "$(BIN_DIR)" > nul)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)

.PHONY: all clean copy-dll
