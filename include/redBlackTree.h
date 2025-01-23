#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <sstream>

using namespace std;

class RedBlackTree {
 private:
  enum Color { RED, BLACK };
  struct Node {
    int valor;
    Node* left;
    Node* right;
    Node* padre;
    Color color;
    Node(int val, Color color)
        : valor(val),
          left(nullptr),
          right(nullptr),
          padre(nullptr),
          color(color) {}
  };
  Node* root;

 public:
  RedBlackTree();
  ~RedBlackTree();
  void destroyTree(Node* node);
  void deleteNode(int val);
  Node* deleteNode(Node* node, int val);
  void insert(int val);
  Node* insert(Node* node, Node* newNode);
  void fixViolation(Node* node);
  void rotateLeft(Node* node);
  void rotateRight(Node* node);
  Node* getUncle(Node* node);
  string generateGraphviz() const;
  void generateGraphviz(stringstream& file, Node* node) const;
  string colorToString(Color color) const;
  void printTree(Node* node, int indent) const;
  void printTree() const;
};

#endif