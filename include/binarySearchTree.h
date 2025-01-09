#ifndef BINARY_SERACH_TREE_H
#define BINARY_SERACH_TREE_H

#include <iostream>

using namespace std;

class binarySearchTree {
 private:
  struct Nodo {
    Nodo* left;
    Nodo* right;
    int value;
    int count;
    Nodo(int val) : left(nullptr), right(nullptr), value(val), count(1) {}
  };
  Nodo* root;
  int counter;

 public:
  binarySearchTree();
  ~binarySearchTree();
  void insert(int val);
  Nodo* insert(Nodo* node, int val);
  void deleteNode(int val);
  Nodo* deleteNode(Nodo* node, int val);
};

#endif