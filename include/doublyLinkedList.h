#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

using namespace std;

class doublyLinkedList {
 private:
  struct Nodo {
    int data;
    Nodo* prev;
    Nodo* next;
    Nodo(int val) : data(val), next(nullptr), prev(nullptr) {}
  };
  Nodo* head;

 public:
  doublyLinkedList();
  ~doublyLinkedList();
  int insertAtHead(int id);
  int insertAtIndex(int id, int index);
  int insertAtEnd(int id);
  int deleteHead();
  int deleteEnd();
  int deleteAtIndex(int index);
  int getLength();
  void display();
  int search(int id);
  int get(int index);
  void generateGraphviz();
};

#endif