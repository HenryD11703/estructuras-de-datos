#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

using namespace std;

class linkedList {
 private:
  struct Nodo {
    int data;
    Nodo* next;
    Nodo(int d) : data(d), next(nullptr) {}
  };
  Nodo* head;

 public:
  linkedList();
  ~linkedList();
  int insertAtHead(int id);
  int insertAtIndex(int id, int index);
  int insertAtEnd(int id);
  int deleteHead();
  int deleteEnd();
  int deleteAtIndex(int index);
  int getLength();
  void display();
  string generateGraphviz();
  int search(int id);
  int get(int index);
};

#endif