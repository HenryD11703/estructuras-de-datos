#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>

using namespace std;

class sparseMatrix {
 private:
  struct Nodo {
    int fila;
    int columna;
    string color;
    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(string clr, int fil, int col)
        : color(clr),
          fila(fil),
          columna(col),
          arriba(nullptr),
          abajo(nullptr),
          izquierda(nullptr),
          derecha(nullptr) {}
  };

  // Lista simplemente enlazadad
  struct HeaderNode {
    int pos;
    HeaderNode* sig;
    Nodo* dato;  // apunta al primer elemento que tenga ya sea fila o columna
    HeaderNode(int position) : pos(position), sig(nullptr), dato(nullptr) {}
  };

  Nodo* head;

 public:
  sparseMatrix();
  ~sparseMatrix();
  int insertColor(string color, int x, int y);
};

#endif