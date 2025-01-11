#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

using namespace std;
class avlTree {
 private:
  struct Nodo {
    Nodo* left;
    Nodo* right;
    int value;
    int height;
    Nodo(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
  };
  Nodo* root;

 public:
  avlTree();
  ~avlTree();
  void destroyTree(Nodo* node);
  void insert(int val);
  Nodo* insert(Nodo* nodo, int val);
  void deleteNode(int val);
  Nodo* deleteNode(Nodo* nodo, int val);
  int getHeight();
  int getHeight(Nodo* nodo);
  Nodo* llRotation(Nodo* nodo);
  Nodo* rrRotation(Nodo* nodo);
  Nodo* lrRotation(Nodo* nodo);
  Nodo* rlRotation(Nodo* nodo);
  void generateGraphviz() const;
  void generateGraphviz(ofstream& file, Nodo* node) const;
  void preorder();
  void preorder(Nodo* node);
  void inorder();
  void inorder(Nodo* node);
  void postorder();
  void postorder(Nodo* node);
};

#endif