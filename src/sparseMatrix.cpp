#include <iostream>
#include <sstream>

#include "../include/sparceMatrix.h"

using namespace std;

sparseMatrix::sparseMatrix() : head(new Nodo("X", 0, 0)) {}

sparseMatrix::~sparseMatrix() {}

// guardar el nodo, pero ajustar los apuntadores de su fila o columna segun sea
// necesario en la posicion dada
int sparseMatrix::insertColor(string color, int x, int y) {
  if (x < 0 || y < 0) return 0;
  Nodo* nuevo = new Nodo(color, x, y);

  // verificar si existe un header node en esas posiciones
  // si existe, entonces si la posicion a la que apunta es menor a la insertada
  // entonces se toma el nodo al que apunta el headerNode y a este se le apunta
  // hacia abajo o a la izquierda segun sea necesario al nuevo nodo, si la
  // posicion a la que apunta el header node es mayor, entonces el header node
  // ahora apunta al nuevo nodo y el nuevo nodo apunta al que apuntaba antes el
  // header node, ademas de tomar ciertas validaciones asi como si hay algo en
  // esa posicion entonces solo se reemplaza el color
}