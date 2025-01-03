#include "../lib/DoublyLinkedList.h"

#include <iostream>

using namespace std;

doublyLinkedList::doublyLinkedList() : head(nullptr) {}

doublyLinkedList::~doublyLinkedList() {
  Nodo* actual = head;
  while (actual != nullptr) {
    Nodo* siguiente = actual->next;
    delete actual;
    actual = siguiente;
  }
}

int doublyLinkedList::insertAtHead(int id) {
  Nodo* nuevo = new Nodo(id);
  nuevo->next = head;
  if (head != nullptr) {
    head->prev = nuevo;
  }
  head = nuevo;
  return 1;
}

int doublyLinkedList::deleteHead() {
  if (head == nullptr) {
    cout << "Empty List" << endl;
    return 0;
  }
  Nodo* temp = head;
  head = temp->next;
  if (head != nullptr) {
    head->prev = nullptr;
  }
  delete temp;
  return 1;
}

int doublyLinkedList::insertAtEnd(int id) {
  if (head == nullptr) {
    insertAtHead(id);
    return 1;
  }
  Nodo* nuevo = new Nodo(id);
  Nodo* actual = head;
  while (actual->next != nullptr) {
    actual = actual->next;
  }
  actual->next = nuevo;
  nuevo->prev = actual;
  return 1;
}

void doublyLinkedList::display() {
  Nodo* actual = head;
  cout << "nullptr";
  while (actual != nullptr) {
    cout << "<-";
    cout << actual->data << "->";
    actual = actual->next;
  }
  cout << "nullptr" << endl;
}
