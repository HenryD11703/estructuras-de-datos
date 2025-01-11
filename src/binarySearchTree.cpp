#include "../include/binarySearchTree.h"

#include <fstream>
#include <iostream>

using namespace std;

binarySearchTree::binarySearchTree() : root(nullptr), counter(0) {}

binarySearchTree::~binarySearchTree() { destroyTree(root); }

void binarySearchTree::destroyTree(Nodo* node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

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

binarySearchTree::Nodo* binarySearchTree::search(int val) {
  return search(root, val);
}
binarySearchTree::Nodo* binarySearchTree::search(Nodo* node, int val) {
  if (node == nullptr || node->value == val) {
    return node;
  }
  if (val > node->value) {
    return search(node->right, val);
  } else if (val < node->value) {
    return search(node->left, val);
  }
}

void binarySearchTree::preorder() { preorder(root); }
void binarySearchTree::preorder(Nodo* node) {
  if (node == nullptr) return;
  cout << node->value << " ";
  preorder(node->left);
  preorder(node->right);
}

void binarySearchTree::inorder() { inorder(root); }
void binarySearchTree::inorder(Nodo* node) {
  if (node == nullptr) return;
  inorder(node->left);
  cout << node->value << " ";
  inorder(node->right);
}

void binarySearchTree::postorder() { postorder(root); }
void binarySearchTree::postorder(Nodo* node) {
  if (node == nullptr) return;
  postorder(node->left);
  postorder(node->right);
  cout << node->value << " ";
}

int binarySearchTree::findMax() {
  if (root == nullptr) {
    throw std::runtime_error("El árbol está vacío");
  }
  return findMax(root);
}
int binarySearchTree::findMax(Nodo* node) {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node->value;
}

void binarySearchTree::generateGraphviz() const {
  ofstream file;
  file.open("./utils/graphviz/binarySearchTree.dot");
  if (file.is_open()) {
    file << "digraph g {" << endl;
    file << "node [shape=circle, style=filled, fontname=\"Helvetica\"];"
         << endl;
    generateGraphviz(file, root);
    file << "rankdir=TB;" << endl;
    file << "nodesep = 0.1" << endl;
    file << "}" << endl;
  }
  file.close();
}
void binarySearchTree::generateGraphviz(ofstream& file, Nodo* node) const {
  if (node == nullptr) {
    return;
  }
  file << "\"" << node << "\"" << "[label=\"" << node->value << "("
       << node->count << ")" << "\"];" << endl;

  // si el nodo, tiene hijo izquierdo
  if (node->left) {
    file << "\"" << node << "\"" << "->" << "\"" << node->left << "\""
         << "[label=\"L\", color=black]" << endl;
    generateGraphviz(file, node->left);
  }
  if (node->right) {
    file << "\"" << node << "\"" << "->" << "\"" << node->right << "\""
         << "[label=\"R\", color=black]" << endl;
    generateGraphviz(file, node->right);
  }
}
