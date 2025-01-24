#include <iostream>
#include <sstream>

#include "../include/sparceMatrix.h"
#include "../lib/json.hpp"

using namespace std;

sparseMatrix::sparseMatrix()
    : head(new Nodo("X", 0, 0)), headerNodeX(nullptr), headerNodeY(nullptr) {}

sparseMatrix::~sparseMatrix() {
  // Liberar los nodos de datos recorriendo por filas
  HeaderNode* currentRowHeader = headerNodeX;
  while (currentRowHeader != nullptr) {
    Nodo* currentNode = currentRowHeader->dato;
    while (currentNode != nullptr) {
      Nodo* temp = currentNode;
      currentNode = currentNode->derecha;
      delete temp;
    }
    HeaderNode* tempHeader = currentRowHeader;
    currentRowHeader = currentRowHeader->sig;
    delete tempHeader;
  }

  // Liberar los headers de columnas
  HeaderNode* currentColHeader = headerNodeY;
  while (currentColHeader != nullptr) {
    HeaderNode* temp = currentColHeader;
    currentColHeader = currentColHeader->sig;
    delete temp;
  }

  // Liberar el nodo cabecera principal
  delete head;
}

int sparseMatrix::deleteColor(int colIndex, int rowIndex) {
  if (rowIndex < 0 || colIndex < 0) return 0;

  HeaderNode* headerX = insertHeader(rowIndex, true);
  HeaderNode* headerY = insertHeader(colIndex, false);

  if (headerX->dato == nullptr || headerY->dato == nullptr) return 0;

  // Buscar el nodo en la fila
  Nodo* currentRow = headerX->dato;
  Nodo* prevRow = nullptr;
  while (currentRow != nullptr && currentRow->columna < colIndex) {
    prevRow = currentRow;
    currentRow = currentRow->derecha;
  }

  if (currentRow == nullptr || currentRow->columna != colIndex) return 0;

  // Buscar el nodo en la columna
  Nodo* currentCol = headerY->dato;
  Nodo* prevCol = nullptr;
  while (currentCol != nullptr && currentCol->fila < rowIndex) {
    prevCol = currentCol;
    currentCol = currentCol->abajo;
  }

  if (currentCol == nullptr || currentCol->fila != rowIndex) return 0;

  // Actualizar enlaces horizontales
  if (prevRow == nullptr) {
    headerX->dato = currentRow->derecha;
  } else {
    prevRow->derecha = currentRow->derecha;
  }
  if (currentRow->derecha != nullptr) {
    currentRow->derecha->izquierda = prevRow;
  }

  // Actualizar enlaces verticales
  if (prevCol == nullptr) {
    headerY->dato = currentCol->abajo;
  } else {
    prevCol->abajo = currentCol->abajo;
  }
  if (currentCol->abajo != nullptr) {
    currentCol->abajo->arriba = prevCol;
  }

  // Eliminar el nodo
  delete currentRow;

  // Eliminar del JSON
  auto& matrix = jsonFile["matrix"];
  for (auto it = matrix.begin(); it != matrix.end(); ++it) {
    if ((*it)["column"] == colIndex && (*it)["row"] == rowIndex) {
      matrix.erase(it);
      break;
    }
  }

  return 1;
}

// guardar el nodo, pero ajustar los apuntadores de su fila o columna segun sea
// necesario en la posicion dada
int sparseMatrix::insertColor(string color, int colIndex, int rowIndex) {
  if (rowIndex < 0 || colIndex < 0) return 0;

  HeaderNode* headerX = insertHeader(rowIndex, true);
  HeaderNode* headerY = insertHeader(colIndex, false);

  // Buscar si ya existe un nodo en esta posición
  Nodo* currentRow = headerX->dato;
  while (currentRow != nullptr && currentRow->columna < colIndex) {
    currentRow = currentRow->derecha;
  }

  if (currentRow != nullptr && currentRow->columna == colIndex) {
    // Si ya existe, actualizar el color
    currentRow->color = color;
    return 1;
  }

  // Crear un nuevo nodo
  Nodo* nuevo = new Nodo(color, rowIndex, colIndex);

  // Insertar en la fila
  if (headerX->dato == nullptr || headerX->dato->columna > colIndex) {
    nuevo->derecha = headerX->dato;
    headerX->dato = nuevo;
  } else {
    Nodo* temp = headerX->dato;
    while (temp->derecha != nullptr && temp->derecha->columna < colIndex) {
      temp = temp->derecha;
    }
    nuevo->derecha = temp->derecha;
    temp->derecha = nuevo;
    if (nuevo->derecha != nullptr) {
      nuevo->derecha->izquierda = nuevo;
    }
    nuevo->izquierda = temp;
  }

  // Insertar en la columna
  if (headerY->dato == nullptr || headerY->dato->fila > rowIndex) {
    nuevo->abajo = headerY->dato;
    headerY->dato = nuevo;
  } else {
    Nodo* temp = headerY->dato;
    while (temp->abajo != nullptr && temp->abajo->fila < rowIndex) {
      temp = temp->abajo;
    }
    nuevo->abajo = temp->abajo;
    temp->abajo = nuevo;
    if (nuevo->abajo != nullptr) {
      nuevo->abajo->arriba = nuevo;
    }
    nuevo->arriba = temp;
  }

  // Agregar al JSON
  jsonFile["matrix"].push_back(
      {{"color", color}, {"column", colIndex}, {"row", rowIndex}});

  return 1;

  // verificar si existe un header node en esas posiciones
  // si existe, entonces si la posicion a la que apunta es menor a la insertada
  // entonces se toma el nodo al que apunta el headerNode y a este se le apunta
  // hacia abajo o a la izquierda segun sea necesario al nuevo nodo, si la
  // posicion a la que apunta el header node es mayor, entonces el header node
  // ahora apunta al nuevo nodo y el nuevo nodo apunta al que apuntaba antes el
  // header node, ademas de tomar ciertas validaciones asi como si hay algo en
  // esa posicion entonces solo se reemplaza el color

  // tambien hacer las validaciones de las posiciones ya que digamos que solo
  // existe la posicion 2 y 5 pero luego se hace un insert en la posicion 4, se
  // tiene que insertar en la posicion despues del 2 antes del 5, entocnes hacer
  // un insertHeaderNode que busque donde se inserte
}

sparseMatrix::HeaderNode* sparseMatrix::insertHeader(int pos, bool isRow) {
  HeaderNode** header = isRow ? &headerNodeX : &headerNodeY;
  // Si la lista esta vacia
  if (*header == nullptr) {
    *header = new HeaderNode(pos);
    return *header;
  }

  if (pos < (*header)->pos) {
    HeaderNode* nuevo = new HeaderNode(pos);
    nuevo->sig = *header;
    *header = nuevo;
  }

  HeaderNode* temp = *header;
  while (temp->sig != nullptr && temp->sig->pos < pos) {
    temp = temp->sig;
  }

  if (temp->pos == pos) return temp;
  if (temp->sig != nullptr && temp->sig->pos == pos) return temp->sig;

  HeaderNode* nuevo = new HeaderNode(pos);
  nuevo->sig = temp->sig;
  temp->sig = nuevo;
  return nuevo;
}

int sparseMatrix::findMax(HeaderNode* header) {
  if (header == nullptr) return 0;

  while (header->sig != nullptr) {
    header = header->sig;
  }
  return header->pos;
}

string sparseMatrix::generateGraph() {
  stringstream graph;
  graph << "digraph G {" << endl;
  graph << "node [shape=plaintext];" << endl;
  graph << "rankdir=LR;" << endl;
  graph << "a0 [label=<<table border=\"0\" cellspacing=\"0\">" << endl;

  int maxRow = findMax(headerNodeX);
  int maxCol = findMax(headerNodeY);

  for (int i = 0; i <= maxRow; i++) {
    graph << "<tr>" << endl;

    HeaderNode* currentRow = headerNodeX;
    while (currentRow != nullptr && currentRow->pos != i) {
      currentRow = currentRow->sig;
    }

    Nodo* currentNode = (currentRow != nullptr) ? currentRow->dato : nullptr;

    for (int j = 0; j <= maxCol; j++) {
      string color = "white";  // Color por defecto

      if (currentNode != nullptr && currentNode->columna == j) {
        color = currentNode->color;
        currentNode = currentNode->derecha;
      }

      graph << "<td bgcolor=\"" << color
            << "\" width=\"20\" height=\"20\"></td>" << endl;
    }

    graph << "</tr>" << endl;
  }

  graph << "</table>>];" << endl;
  graph << "}" << endl;

  return graph.str();
}

json sparseMatrix::toJson() const { return jsonFile; }

void sparseMatrix::insertJson(json text) {
  if (text.is_array()) {
    for (const auto& element : text) {
      string color = element["color"];
      int column = element["column"];
      int row = element["row"];

      // Insertar cada elemento en la matriz
      insertColor(color, column, row);
    }
  } else {
    cout << "Error: Los datos enviados no son un array" << endl;
  }
}

void sparseMatrix::clearMatrix() {
  HeaderNode* currentRowHeader = headerNodeX;
  while (currentRowHeader != nullptr) {
    Nodo* currentNode = currentRowHeader->dato;

    while (currentNode != nullptr) {
      Nodo* temp = currentNode;
      currentNode = currentNode->derecha;
      delete temp;
    }

    currentRowHeader->dato = nullptr;
    HeaderNode* tempHeader = currentRowHeader;
    currentRowHeader = currentRowHeader->sig;
    delete tempHeader;
  }

  headerNodeX = nullptr;  // Limpiar el puntero de filas
  headerNodeY = nullptr;  // Limpiar el puntero de columnas

  jsonFile.clear();
}