#include "../include/redBlackTree.h"
#include <iostream>
#include <sstream>

using namespace std;

RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::~RedBlackTree() {}

void RedBlackTree::insert(int val) {
  if (root == nullptr)
    root = new Nodo(val, "black");
  else
    root = insert(root, val);
}

RedBlackTree::Nodo* RedBlackTree::insert(Nodo* node, int val) {
  if (node == nullptr) {
    return new Nodo(val, "red");
  }

  if (val < node->valor)
    node->izquierdo = insert(node->izquierdo, val);
  else
    node->derecho = insert(node->derecho, val);

    return node;
}
