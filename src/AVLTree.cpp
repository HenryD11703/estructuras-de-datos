#include "../include/avlTree.h"

#include <fstream>
#include <iostream>

using namespace std;

avlTree::avlTree() : root(nullptr) {}

avlTree::~avlTree() { destroyTree(root); }
void avlTree::destroyTree(Nodo* node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

void avlTree::insert(int val) { root = insert(root, val); }
avlTree::Nodo* avlTree::insert(Nodo* nodo, int val) {
  int leftHeight, rightHeight, balanceFactor;
  if (nodo == nullptr) {
    // si esta vacio solo se inserta en el root
    return new Nodo(val);
  }
  if (val < nodo->value)
    nodo->left = insert(nodo->left, val);
  else
    nodo->right = insert(nodo->right, val);

  nodo->height = 1 + max(getHeight(nodo->left), getHeight(nodo->right));

  /* Aca en esta parte añadir los autobalanceos del arbol */
  leftHeight = getHeight(nodo->left);
  rightHeight = getHeight(nodo->right);
  balanceFactor = leftHeight - rightHeight;

  if (balanceFactor < -1 && val > nodo->right->value) return rrRotation(nodo);
  if (balanceFactor > 1 && val < nodo->left->value) return llRotation(nodo);

  if (balanceFactor > 1 && val > nodo->left->value) return lrRotation(nodo);
  if (balanceFactor < -1 && val < nodo->right->value) return rlRotation(nodo);

  // basicamente estamos comprobando que este imbalanceado y que tipo de
  // rotacion se hace si el arbol esta desbalanceado y el valor que insertamos
  // esta en cierta posicion se calcula el tipo de rotacion que se hace
  return nodo;
}

avlTree::Nodo* avlTree::llRotation(Nodo* nodo) {
  Nodo* newRoot = nodo->left;
  Nodo* rootRight = newRoot->right;

  newRoot->right = nodo;
  nodo->left = rootRight;

  nodo->height = max(getHeight(nodo->left), getHeight(nodo->right)) + 1;
  newRoot->height =
      max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

avlTree::Nodo* avlTree::rrRotation(Nodo* nodo) {
  Nodo* newRoot = nodo->right;
  Nodo* rootLeft = newRoot->left;

  newRoot->left = nodo;
  nodo->right = rootLeft;

  newRoot->height =
      max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
  nodo->height = max(getHeight(nodo->left), getHeight(nodo->right)) + 1;

  return newRoot;
}

avlTree::Nodo* avlTree::lrRotation(Nodo* nodo) {
  nodo->left = rrRotation(nodo->left);
  return llRotation(nodo);
}

avlTree::Nodo* avlTree::rlRotation(Nodo* nodo) {
  nodo->right = llRotation(nodo->right);
  return rrRotation(nodo);
}

int avlTree::getHeight() { return getHeight(root); }
// Esta funcion tiene como parametro el nodo, ya que se calculara por defecto
// a partir de la raiz, pero en un avl es necesario calcular de los sub
// arboles que se creen
int avlTree::getHeight(Nodo* nodo) {
  // Mi idea: recorrer los nodos hasta encontrar el ultimo, ir sumando por
  // cada uno que se encuentre, ya sea del lado derecho y del izquierdo y
  // comparar su valor
  int leftH, rightH;
  if (nodo == nullptr) {
    return 0;
  }
  leftH = getHeight(nodo->left);
  rightH = getHeight(nodo->right);
  return max(leftH, rightH) + 1;
}

void avlTree::generateGraphviz() const {
  ofstream file;
  file.open("./utils/graphviz/avlTree.dot");
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
void avlTree::generateGraphviz(ofstream& file, Nodo* node) const {
  if (node == nullptr) {
    return;
  }
  file << "\"" << node << "\"" << "[label=\"" << node->value << "("
       << node->height << ")" << "\"];" << endl;

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

void avlTree::preorder() { preorder(root); }
void avlTree::preorder(Nodo* node) {
  if (node == nullptr) return;
  cout << node->value << " ";
  preorder(node->left);
  preorder(node->right);
}

void avlTree::inorder() { inorder(root); }
void avlTree::inorder(Nodo* node) {
  if (node == nullptr) return;
  inorder(node->left);
  cout << node->value << " ";
  inorder(node->right);
}

void avlTree::postorder() { postorder(root); }
void avlTree::postorder(Nodo* node) {
  if (node == nullptr) return;
  postorder(node->left);
  cout << node->value << " ";
  postorder(node->right);
}
