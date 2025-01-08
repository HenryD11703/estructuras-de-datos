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

void binarySearchTree::deleteNode(int val) { root = deleteNode(root, val); }

binarySearchTree::Nodo* binarySearchTree::deleteNode(Nodo* node, int val) {
  if (node == nullptr) {
    return nullptr;
  }
  if (val > node->value) {
    node->der = deleteNode(node->der, val);
  } else if (val < node->value) {
    node->izq = deleteNode(node->izq, val);
  }
  if (val == node->value) {
    // aca eliminar el nodo
    if (node->count > 1) {
      node->count--;
      return node;
    }
    if (node->izq == nullptr && node->der == nullptr) {
      // es hoja
      delete node;
      return nullptr;
    } else if (node->izq == nullptr || node->der == nullptr) {
      // tiene un solo hijo
      Nodo* temp;
      if (!node->izq)
        temp = node->der;
      else
        temp = node->izq;
      delete node;
      return temp;
    } else {
      // tiene dos hijos
      Nodo* sucesor = node->der;
      while (sucesor->izq != nullptr) {
        sucesor = sucesor->izq;
      }

      node->value = sucesor->value;
      node->count = sucesor->count;

      // En esta parte basicamente lo que esta pasando es que se busca el nodo
      // menor del lado izquierdo del arbol, es decir el nodo mas a la izquierda
      // de los hijos derechos del nodo y luego no se elimina fisicamente el
      // nodo, sino que se cambia el valor por este, y luego se procede a
      // eliminar el nodo mas pequeño del lado derecho del nodo que se esta
      // buscando eliminar

      node->der = deleteNode(node->der, sucesor->value);
      return node;
    }
  }
}