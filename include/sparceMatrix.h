#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>

#include "../lib/json.hpp"

using namespace std;
using json = nlohmann::json;

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

  // Lista simplemente enlazada
  struct HeaderNode {
    int pos;
    HeaderNode* sig;
    Nodo* dato;  // apunta al primer elemento que tenga ya sea fila o columna
    HeaderNode(int position) : pos(position), sig(nullptr), dato(nullptr) {}
  };

  Nodo* head;
  HeaderNode* headerNodeX;
  HeaderNode* headerNodeY;
  json jsonFile;

 public:
  sparseMatrix();
  ~sparseMatrix();
  int insertColor(string color, int x, int y);
  HeaderNode* insertHeader(int pos, bool isRow);
  int findMax(HeaderNode* header);
  string generateGraph();
  json toJson() const;
  int deleteColor(int x, int y);
  void insertJson(json text);
  void clearMatrix();
};

#endif