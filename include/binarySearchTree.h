#ifndef BINARY_SERACH_TREE_H
#define BINARY_SERACH_TREE_H

#include <iostream>
#include <sstream>

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
  Nodo* search(int val);
  Nodo* search(Nodo* node, int val);
  string generateGraphviz() const;
  void generateGraphviz(stringstream& file, Nodo* node) const;
  string preorder();
  void preorder(stringstream& text, Nodo* node);
  string inorder();
  void inorder(stringstream& text, Nodo* node);
  string postorder();
  void postorder(stringstream& text, Nodo* node);
  int findMax();
  int findMax(Nodo* node);
  void destroyTree(Nodo* node);
};

#endif