#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>

using namespace std;

class BTree {
 private:
  int M;
  class Nodo {
   public:
    int M_nodo;
    int num_claves;
    std::vector<int> claves;
    std::vector<Nodo*> hijos;
    bool es_hoja;

    Nodo(int m, bool hoja);
    void insertarNoLleno(int clave);
    void dividirHijo(int indice, Nodo* hijo);
    void recorrer();
    string generateGraphviz();
  };

  Nodo* raiz;

 public:
  BTree(int max_claves);
  void insertar(int clave);
  void recorrer();
  string generateGraphviz();
};
#endif