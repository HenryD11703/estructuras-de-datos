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
  int counter;

 public:
  doublyCircularList();
  ~doublyCircularList();
  int insertAtHead(int val);
  int deleteAtHead();
  int insertAtTail(int val);
  int deleteAtTail();
  int insertAtIndex(int index, int val);
  int deleteAtIndex(int index);
  int getLength();
  int search(int id);
  int get(int idx);
  Nodo* findNodeAtIndex(int idx) const;
  void generateGraphviz();
};

#endif