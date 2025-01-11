# Definir compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -g
LDFLAGS =

# Directorios
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
LIB_DIR = lib
DOC_DIR = docs

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/program

# Reglas
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

# Crear los directorios necesarios si no existen
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regla para generar los directorios y luego compilar
.PHONY: all clean