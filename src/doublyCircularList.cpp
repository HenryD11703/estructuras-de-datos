#include "../include/doublyCircularList.h"

#include <fstream>
#include <iostream>

using namespace std;

doublyCircularList::doublyCircularList()
    : head(nullptr), tail(nullptr), counter(0) {}

doublyCircularList::~doublyCircularList() {
  if (head == nullptr) return;
  Nodo* actual = head;
  do {
    Nodo* siguiente = actual->next;
    delete actual;
    actual = siguiente;
  } while (actual != head);
  counter = 0;
}

int doublyCircularList::insertAtHead(int id) {
  Nodo* nuevo = new (std::nothrow) Nodo(id);
  if (!nuevo) return -1;
  if (tail == nullptr) {
    nuevo->next = nuevo;
    nuevo->prev = nuevo;
    head = nuevo;
    tail = nuevo;
  } else {
    nuevo->next = head;
    nuevo->prev = tail;

    tail->next = nuevo;
    head->prev = nuevo;

    head = nuevo;
  }
  counter++;
  return 1;
}

int doublyCircularList::deleteAtHead() {
  if (tail == nullptr) {
    cout << "Error lista vacia :(" << endl;
    return -1;
  } else if (head == tail) {
    delete head;
    head = nullptr;
    tail = nullptr;
  } else {
    tail->next = head->next;
    head->next->prev = tail;
    delete head;
    head = tail->next;
  }
  counter--;
  return 1;
}

int doublyCircularList::insertAtTail(int id) {
  Nodo* nuevo = new (std::nothrow) Nodo(id);
  if (!nuevo) return -1;

  if (tail == nullptr) {
    head = nuevo;
    tail = nuevo;
    nuevo->next = nuevo;
    nuevo->prev = nuevo;
  } else {
    head->prev = nuevo;
    tail->next = nuevo;

    nuevo->next = head;
    nuevo->prev = tail;

    tail = nuevo;
  }
  counter++;
  return 1;
}

int doublyCircularList::deleteAtTail() {
  if (tail == nullptr) {
    cout << "Error, lista vacia" << endl;
    return -1;
  } else if (tail == head) {
    delete tail;
    head = nullptr;
    tail = nullptr;
  } else {
    head->prev = tail->prev;
    tail->prev->next = head;
    delete tail;
    tail = head->prev;
  }
  counter--;
  return 1;
}

int doublyCircularList::insertAtIndex(int idx, int val) {
  Nodo* nuevo = new (std::nothrow) Nodo(val);
  if (!nuevo) return -1;
  if (tail == nullptr) {
    tail = nuevo;
    head = nuevo;
    nuevo->next = nuevo;
    nuevo->prev = nuevo;
  } else if (idx > counter || idx < 0) {
    cout << "Error, Indice fuera de rango" << endl;
    return -1;
  } else if (idx == 0) {
    delete nuevo;
    insertAtHead(val);
    return 1;
  } else if (idx == counter) {
    delete nuevo;
    insertAtTail(val);
    return 1;
  } else {
    Nodo* actual = nullptr;
    if (idx < counter / 2) {
      actual = head;
      for (int i = 0; i < idx; ++i) {
        actual = actual->next;
      }
    } else {
      actual = tail;
      for (int i = counter - 1; i > idx; --i) {
        actual = actual->prev;
      }
    }
    nuevo->prev = actual->prev;
    nuevo->next = actual;

    actual->prev->next = nuevo;
    actual->prev = nuevo;
  }
  counter++;
  return 1;
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