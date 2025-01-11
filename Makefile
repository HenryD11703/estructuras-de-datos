CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -I/usr/include/qt -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtCore -g
LDFLAGS = -L/usr/lib/qt5 -lQt5Widgets -lQt5Core

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
