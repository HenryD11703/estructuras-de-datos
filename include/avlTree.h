#ifndef AVL_TREE_H
#define AVL_TREE_H

class AVLTree {
 private:
  struct Nodo {
    Nodo* left;
    Nodo* right;
    int value;
    int counter;
  };

 public:
  AVLTree();
  ~AVLTree();
};

#endif