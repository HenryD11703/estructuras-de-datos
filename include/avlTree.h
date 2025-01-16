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
  string generateGraphviz() const;
  void generateGraphviz(stringstream& file, Nodo* node) const;
  string preorder();
  void preorder(stringstream& text, Nodo* node);
  string inorder();
  void inorder(stringstream& text, Nodo* node);
  string postorder();
  void postorder(stringstream& text, Nodo* node);
};

#endif