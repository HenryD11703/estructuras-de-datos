#include "../include/doublyCircularList.h"

#include <fstream>
#include <iostream>

using namespace std;

doublyCircularList::doublyCircularList() : head(nullptr), tail(nullptr) {}

doublyCircularList::~doublyCircularList() {
  if (head == nullptr) return;
  Nodo* actual = head;
  do {
    Nodo* siguiente = actual->next;
    delete actual;
    actual = siguiente;
  } while (actual != head);
}

int doublyCircularList::insertAtHead(int id) {
  Nodo* nuevo = new Nodo(id);
  if (tail == nullptr) {
    nuevo->next = nuevo;
    nuevo->prev = nuevo;
    head = nuevo;
    tail = nuevo;
    return 1;
  } else {
    nuevo->next = head;
    nuevo->prev = tail;

    tail->next = nuevo;
    head->prev = nuevo;

    head = nuevo;
    return 1;
  }
}

int doublyCircularList::deleteAtHead() {
  if (tail == nullptr) {
    cout << "Error lista vacia :(" << endl;
    return -1;
  } else if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
    return 1;
  } else {
    tail->next = head->next;
    head->next->prev = tail;
    delete head;
    head = tail->next;
    return 1;
  }
}

void doublyCircularList::generateGraphviz() {
  ofstream file;
  file.open("./utils/graphviz/doublyCircularList.dot");
  if (file.is_open()) {
    file << "digraph g {" << endl;
    file << "node [shape=box, style=filled, fontname=\"Helvetica\"];" << endl;

    // Head and Tail nodes
    file << "Head [label=\"Head\",color=lightblue, fillcolor=lightblue];"
         << endl;
    file << "Tail [label=\"Tail\",color=lightblue, fillcolor=lightblue];"
         << endl;

    Nodo* actual = head;

    if (tail == nullptr) {
      file << "\"Empty List\"" << endl;
    } else if (head == tail) {
      file << "\"" << actual << "\"" << "[label=\"" << actual->data << "\"];"
           << endl;
      file << "Head ->" << "\"" << actual << "\"" << endl;
      file << "Tail ->" << "\"" << actual << "\"" << endl;
      file << "\"" << actual << "\"" << "->" << "\"" << actual << "\"" << endl;
      file << "\"" << actual << "\"" << "->" << "\"" << actual << "\"" << endl;
    } else {
      file << "Head ->" << "\"" << head << "\"" << endl;
      file << "Tail ->" << "\"" << tail << "\"" << endl;

      file << "\"" << actual << "\"" << "[label=\"" << actual->data << "\"];"
           << endl;

      file << "\"" << actual << "\"" << "->" << "\"" << actual->next << "\""
           << "[label=\"Next\", color=black]" << endl;
      file << "\"" << actual << "\"" << "->" << "\"" << actual->prev << "\""
           << "[label=\"Prev\", color=black]" << endl;

      actual = actual->next;
      while (actual != head) {
        file << "\"" << actual << "\"" << "[label=\"" << actual->data << "\"];"
             << endl;
        file << "\"" << actual << "\"" << "->" << "\"" << actual->next << "\""
             << "[label=\"Next\", color=black]" << endl;
        file << "\"" << actual << "\"" << "->" << "\"" << actual->prev << "\""
             << "[label=\"Prev\", color=black]" << endl;

        actual = actual->next;
      }
    }
    file << "rankdir=LR;" << endl;
    file << "nodesep = 0.1" << endl;
    file << "}" << endl;
  }
  file.close();
}