#include "../include/redBlackTree.h"
#include <iostream>
#include <sstream>

using namespace std;

RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::~RedBlackTree() {
  // Implementar la liberación de memoria si es necesario
}

void RedBlackTree::insert(int val) {
  Node* newNode = new Node(val, RED);
  root = insert(root, newNode);
  fixViolation(newNode);
}

RedBlackTree::Node* RedBlackTree::insert(Node* node, Node* newNode) {
  if (node == nullptr) {
    return newNode;
  }

  if (newNode->valor < node->valor) {
    node->left = insert(node->left, newNode);
    node->left->padre = node;
  } else if (newNode->valor > node->valor) {
    node->right = insert(node->right, newNode);
    node->right->padre = node;
  }

  return node;
}

void RedBlackTree::fixViolation(Node* node) {
  Node* padre = nullptr;
  Node* abuelo = nullptr;

  while ((node != root) && (node->color != BLACK) &&
         (node->padre->color == RED)) {
    padre = node->padre;
    abuelo = padre->padre;

    // Caso 1: El padre es el hijo izquierdo del abuelo
    if (padre == abuelo->left) {
      Node* tio = abuelo->right;

      // Caso 1.1: El tío es rojo, solo se necesita recolorar
      if (tio != nullptr && tio->color == RED) {
        abuelo->color = RED;
        padre->color = BLACK;
        tio->color = BLACK;
        node = abuelo;
      } else {
        // Caso 1.2: El nodo es el hijo derecho del padre, se necesita una rotación a la izquierda
        if (node == padre->right) {
          rotateLeft(padre);
          node = padre;
          padre = node->padre;
        }

        // Caso 1.3: El nodo es el hijo izquierdo del padre, se necesita una rotación a la derecha
        rotateRight(abuelo);
        swap(padre->color, abuelo->color);
        node = padre;
      }
    } else  // Caso 2: El padre es el hijo derecho del abuelo
    {
      Node* tio = abuelo->left;

      // Caso 2.1: El tío es rojo, solo se necesita recolorar
      if (tio != nullptr && tio->color == RED) {
        abuelo->color = RED;
        padre->color = BLACK;
        tio->color = BLACK;
        node = abuelo;
      } else {
        // Caso 2.2: El nodo es el hijo izquierdo del padre, se necesita una rotación a la derecha
        if (node == padre->left) {
          rotateRight(padre);
          node = padre;
          padre = node->padre;
        }

        // Caso 2.3: El nodo es el hijo derecho del padre, se necesita una rotación a la izquierda
        rotateLeft(abuelo);
        swap(padre->color, abuelo->color);
        node = padre;
      }
    }
  }

  root->color = BLACK;
}

void RedBlackTree::rotateLeft(Node* node) {
  Node* rightChild = node->right;
  node->right = rightChild->left;

  if (node->right != nullptr) {
    node->right->padre = node;
  }

  rightChild->padre = node->padre;

  if (node->padre == nullptr) {
    root = rightChild;
  } else if (node == node->padre->left) {
    node->padre->left = rightChild;
  } else {
    node->padre->right = rightChild;
  }

  rightChild->left = node;
  node->padre = rightChild;
}

void RedBlackTree::rotateRight(Node* node) {
  Node* leftChild = node->left;
  node->left = leftChild->right;

  if (node->left != nullptr) {
    node->left->padre = node;
  }

  leftChild->padre = node->padre;

  if (node->padre == nullptr) {
    root = leftChild;
  } else if (node == node->padre->left) {
    node->padre->left = leftChild;
  } else {
    node->padre->right = leftChild;
  }

  leftChild->right = node;
  node->padre = leftChild;
}

RedBlackTree::Node* RedBlackTree::getUncle(Node* node) {
  if (node->padre == nullptr || node->padre->padre == nullptr) {
    return nullptr;
  }

  if (node->padre == node->padre->padre->left) {
    return node->padre->padre->right;
  } else {
    return node->padre->padre->left;
  }
}

string RedBlackTree::colorToString(Color color) const {
  return color == RED ? "RED" : "BLACK";
}

void RedBlackTree::printTree(Node* node, int indent) const {
  if (node == nullptr) {
    return;
  }

  printTree(node->right, indent + 4);

  for (int i = 0; i < indent; i++) {
    cout << " ";
  }

  cout << node->valor << " (" << colorToString(node->color) << ")" << endl;

  printTree(node->left, indent + 4);
}

void RedBlackTree::printTree() const {
  printTree(root, 0);
}
string RedBlackTree::generateGraphviz() const {
  stringstream file;
  file << "digraph g {" << endl;
  file << "node [shape=circle, fontname=\"Helvetica\"];" << endl;
  generateGraphviz(file, root);
  file << "rankdir=TB;" << endl;
  file << "nodesep = 0.1;" << endl;
  file << "}" << endl;

  return file.str();
}

void RedBlackTree::generateGraphviz(stringstream& file, Node* node) const {
  if (node == nullptr) {
    return;
  }
  file << "\"" << node << "\"" << "[label=\"" << node->valor << "\" color=\""
       << (node->color == RED ? "red" : "black") << "\"]" << endl;

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
