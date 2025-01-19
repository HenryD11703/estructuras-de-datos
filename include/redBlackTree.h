#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <sstream>

using namespace std;

class RedBlackTree {
 private:
  struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    string color;
    Nodo(int val, string color)
        : valor(val), izquierdo(nullptr), derecho(nullptr) {}
  };
  Nodo* root;

 public:
  RedBlackTree();
  ~RedBlackTree();
  void insert(int val);
  Nodo* insert(Nodo* node, int val);
};

#endif