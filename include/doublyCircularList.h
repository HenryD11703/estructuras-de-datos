#ifndef DOUBLY_CIRCULAR_LIST_H
#define DOUBLY_CIRCULAR_LIST_H

#include <iostream>

using namespace std;

class doublyCircularList {
 private:
  struct Nodo {
    Nodo* prev;
    Nodo* next;
    int data;
    Nodo(int val) : prev(nullptr), next(nullptr), data(val) {}
  };
  Nodo* head;
  Nodo* tail;

 public:
  doublyCircularList();
  ~doublyCircularList();
  int insertAtHead(int val);
  int deleteAtHead();
  void generateGraphviz();
};

#endif