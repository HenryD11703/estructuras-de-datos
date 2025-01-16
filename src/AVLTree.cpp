#include "../include/avlTree.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

void avlTree::deleteNode(int val) { root = deleteNode(root, val); }
avlTree::Nodo* avlTree::deleteNode(Nodo* node, int val) {
  int leftHeight, rightHeight, balanceFactor;
  if (node == nullptr) {
    return nullptr;
  }
  if (val < node->value) {
    node->left = deleteNode(node->left, val);
  } else if (val > node->value) {
    node->right = deleteNode(node->right, val);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    } else if (node->left == nullptr || node->right == nullptr) {
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
      node->right = deleteNode(node->right, sucesor->value);
    }
  }
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  leftHeight = getHeight(node->left);
  rightHeight = getHeight(node->right);
  balanceFactor = leftHeight - rightHeight;

  if (balanceFactor > 1) {
    int leftChildBalance =
        getHeight(node->left->left) - getHeight(node->left->right);
    if (leftChildBalance >= 0)
      return llRotation(node);
    else
      return lrRotation(node);
  }
  if (balanceFactor < -1) {
    int rightChildBalance =
        getHeight(node->right->left) - getHeight(node->right->right);
    if (rightChildBalance <= 0)
      return rrRotation(node);
    else
      return rlRotation(node);
  }

  return node;
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

string avlTree::preorder() {
  stringstream preorderString;
  preorder(preorderString, root);
  return preorderString.str();
}
void avlTree::preorder(stringstream& text, Nodo* node) {
  if (node == nullptr) return;
  text << node->value << " ";
  preorder(text, node->left);
  preorder(text, node->right);
}

string avlTree::inorder() {
  stringstream inorderString;
  inorder(inorderString, root);
  return inorderString.str();
}
void avlTree::inorder(stringstream& text, Nodo* node) {
  if (node == nullptr) return;
  inorder(text, node->left);
  text << node->value << " ";
  inorder(text, node->right);
}

string avlTree::postorder() {
  stringstream preorderString;
  preorder(preorderString, root);
  return preorderString.str();
}
void avlTree::postorder(stringstream& text, Nodo* node) {
  if (node == nullptr) return;
  postorder(text, node->left);
  postorder(text, node->right);
  text << node->value << " ";
}

string avlTree::generateGraphviz() const {
  stringstream file;
  file << "digraph g {" << endl;
  file << "node [shape=circle, style=filled, fontname=\"Helvetica\"];" << endl;
  generateGraphviz(file, root);
  file << "rankdir=TB;" << endl;
  file << "nodesep = 0.1" << endl;
  file << "}" << endl;

  return file.str();
}

void avlTree::generateGraphviz(stringstream& file, Nodo* node) const {
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
