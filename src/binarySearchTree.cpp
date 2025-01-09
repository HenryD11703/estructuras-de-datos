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
    node->left = insert(node->left, val);
  else
    node->right = insert(node->right, val);

  return node;
}

void binarySearchTree::deleteNode(int val) { root = deleteNode(root, val); }

binarySearchTree::Nodo* binarySearchTree::deleteNode(Nodo* node, int val) {
  if (node == nullptr) {
    return nullptr;
  }
  if (val > node->value) {
    node->right = deleteNode(node->right, val);
  } else if (val < node->value) {
    node->left = deleteNode(node->left, val);
  }
  if (val == node->value) {
    // aca eliminar el nodo
    if (node->count > 1) {
      node->count--;
      return node;
    }
    if (node->left == nullptr && node->right == nullptr) {
      // es hoja
      delete node;
      return nullptr;
    } else if (node->left == nullptr || node->right == nullptr) {
      // tiene un solo hijo
      Nodo* temp = node->left ? node->left : node->right;
      delete node;
      return temp;
    } else {
      // tiene dos hijos
      Nodo* sucesor = node->right;
      while (sucesor->left != nullptr) {
        sucesor = sucesor->left;
      }

      node->value = sucesor->value;
      node->count = sucesor->count;

      // En esta parte basicamente lo que esta pasando es que se busca el nodo
      // menor del lado izquierdo del arbol, es decir el nodo mas a la izquierda
      // de los hijos derechos del nodo y luego no se elimina fisicamente el
      // nodo, sino que se cambia el valor por este, y luego se procede a
      // eliminar el nodo mas pequeño del lado derecho del nodo que se esta
      // buscando eliminar

      node->right = deleteNode(node->right, sucesor->value);
    }
  }
  return node;
}