#include <iostream>
#include <sstream>
#include "../lib/json.hpp"

#include "../include/sparceMatrix.h"

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
  if (rowIndex < 0 || colIndex < 0)
    throw invalid_argument("Error posicion negativa");

  HeaderNode* headerX = insertHeader(rowIndex, true);
  HeaderNode* headerY = insertHeader(colIndex, false);

  if (headerX->dato == nullptr || headerY->dato == nullptr)
    return 0;

  Nodo* currentRow = headerX->dato;
  Nodo* prevRow = nullptr;

  while (currentRow != nullptr && currentRow->columna < colIndex) {
    prevRow = currentRow;
    currentRow = currentRow->derecha;
  }

  if (currentRow == nullptr || currentRow->columna != colIndex)
    return 0;

  Nodo* currentCol = headerY->dato;
  Nodo* prevCol = nullptr;

  while (currentCol != nullptr && currentCol->fila < rowIndex) {
    prevCol = currentCol;
    currentCol = currentCol->abajo;
  }

  if (currentCol == nullptr || currentCol->fila != rowIndex)
    return 0;

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
  delete currentRow;  // currentRow y currentCol son el mismo nodo

  return 1;
}

// guardar el nodo, pero ajustar los apuntadores de su fila o columna segun sea
// necesario en la posicion dada
int sparseMatrix::insertColor(string color, int colIndex, int rowIndex) {
  if (rowIndex < 0 || colIndex < 0)
    return 0;

  HeaderNode* headerX = insertHeader(rowIndex, true);
  HeaderNode* headerY = insertHeader(colIndex, false);

  Nodo* nuevo = new Nodo(color, rowIndex, colIndex);

  if (headerX->dato == nullptr || headerX->dato->columna > colIndex) {
    // si el nodo a insertar es el primero en esta fila, o si esta en la primera
    // posicion
    nuevo->derecha = headerX->dato;
    headerX->dato = nuevo;
  } else {
    Nodo* temp = headerX->dato;
    headerX->dato = nuevo;
    while (temp->derecha != nullptr && temp->derecha->columna < colIndex) {
      temp = temp->derecha;
    }
    // si ya existe en esta posicion
    if (temp->derecha != nullptr && temp->derecha->columna == colIndex) {
      temp->derecha->color = color;
      delete nuevo;
      return 1;
    }
    nuevo->derecha = temp->derecha;
    temp->derecha = nuevo;
    if (nuevo->derecha != nullptr) {
      nuevo->derecha->izquierda = nuevo;
    }
    nuevo->izquierda = temp;
  }

  if (headerY->dato == nullptr || headerY->dato->fila > rowIndex) {
    nuevo->abajo = headerY->dato;
    headerY->dato = nuevo;
  } else {
    Nodo* temp = headerY->dato;
    headerY->dato = nuevo;
    while (temp->abajo != nullptr && temp->abajo->fila < rowIndex) {
      temp = temp->abajo;
    }
    if (temp->abajo != nullptr && temp->abajo->fila == rowIndex) {
      temp->abajo->color = color;
      delete nuevo;
      return 1;
    }
    nuevo->abajo = temp->abajo;
    temp->abajo = nuevo;
    if (nuevo->abajo != nullptr) {
      nuevo->abajo->arriba = nuevo;
    }
    nuevo->arriba = temp;
  }

  cout << "Color: " << color << " en la posicion: " << colIndex << ", "
       << rowIndex << endl;

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

  if (temp->pos == pos)
    return temp;
  if (temp->sig != nullptr && temp->sig->pos == pos)
    return temp->sig;

  HeaderNode* nuevo = new HeaderNode(pos);
  nuevo->sig = temp->sig;
  temp->sig = nuevo;
  return nuevo;
}

int sparseMatrix::findMax(HeaderNode* header) {
  if (header == nullptr)
    return 0;

  while (header->sig != nullptr) {
    header = header->sig;
  }
  return header->pos;
}

string sparseMatrix::generateGraph() {
  stringstream graph;
  graph << "digraph a {" << endl;
  graph << "node [fontname = \" Helvetica, Arial, sans - seruf \";];" << endl;
  graph << "a0 [shape= none;label = <" << endl;
  graph << "<table border = \"0\" cellspacing=\"0\">" << endl;

  int maxRow = findMax(headerNodeX);
  int maxCol = findMax(headerNodeY);

  // crear una cantidad de tr igual a maxRow
  for (int i = 0; i <= maxRow; i++) {
    // En este ciclo se recorren dos arrays lo que hace que su complejidad temporal sea O(x*y)
    graph << "<tr>" << endl;

    // buscar el header node de esta fila
    HeaderNode* currentRow = headerNodeX;
    while (currentRow != nullptr && currentRow->pos != i) {
      currentRow = currentRow->sig;
    }

    Nodo* currentNode = (currentRow != nullptr) ? currentRow->dato : nullptr;

    for (int j = 0; j <= maxCol; j++) {
      string color = "white";  // Color por defecto

      // Si hay un nodo en esta columna, usar su color
      if (currentNode != nullptr && currentNode->columna == j) {
        color = currentNode->color;
        currentNode = currentNode->derecha;
      }

      graph << "<td bgcolor=\"" << color << "\"></td>" << endl;
    }

    graph << "</tr>" << endl;
  }

  // Iterar por cada nodo de cada fila e irlos metiendo a la tabla

  graph << "</table> >;];" << endl;
  graph << "}" << endl;

  return graph.str();
}

json sparseMatrix::toJson() const {
  return jsonFile;
}

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