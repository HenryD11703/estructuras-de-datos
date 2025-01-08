#include "../include/binarySearchTree.h"

#include <fstream>
#include <iostream>

using namespace std;

binarySearchTree::binarySearchTree() : root(nullptr), counter(0) {}

binarySearchTree::~binarySearchTree() {}

void binarySearchTree::insert(int val) { root = insert(root, val); }

binarySearchTree::Nodo* binarySearchTree::insert(Nodo* node, int val) {
  if (node == nullptr) {
    return new Nodo(val);
  }
  if (val == node->value) {
    node->count++;
    return node;
  }
  if (val < node->value)
    node->izq = insert(node->izq, val);
  else
    node->der = insert(node->der, val);

  return node;
}

void binarySearchTree::insert(int val) { root = deleteNode(root, val); }

binarySearchTree::Nodo* binarySearchTree::deleteNode(Nodo* node, int val) {}