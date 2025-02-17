#include "../include/doublyLinkedList.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

int doublyLinkedList::deleteEnd() {
  if (head == nullptr) {
    return 0;
  }
  if (head->next == nullptr) {
    delete head;     // Liberar la memoria del único nodo.
    head = nullptr;  // Actualizar head a nullptr.
    return 1;
  }

  Nodo* actual = head;
  while (actual->next != nullptr && actual->next->next != nullptr) {
    actual = actual->next;
  }
  delete actual->next;
  actual->next = nullptr;
  return 1;
}

int doublyLinkedList::insertAtIndex(int id, int index) {
  if (head == nullptr) {
    return 0;
  }
  if (index == 0) {
    insertAtHead(id);
    return 1;
  }
  int contador = 0;
  Nodo* actual = head;
  while (contador + 1 != index && actual != nullptr) {
    actual = actual->next;
    contador++;
  }
  if (actual->next == nullptr) {
    insertAtEnd(id);
    return 1;
  }
  Nodo* nuevo = new Nodo(id);
  nuevo->prev = actual;
  nuevo->next = actual->next;
  actual->next->prev = nuevo;
  actual->next = nuevo;
  return 1;
}

int doublyLinkedList::deleteAtIndex(int index) {
  if (head == nullptr) {
    return 0;
  }
  if (index == 0) {
    deleteHead();
    return 1;
  }
  int contador = 0;
  Nodo* actual = head;
  while (contador + 1 != index && actual != nullptr) {
    actual = actual->next;
    contador++;
  }
  if (actual->next == nullptr || actual == nullptr) {
    return 0;  // indice fuera de rango
  }
  Nodo* temp = actual->next;
  actual->next = temp->next;

  if (temp->next != nullptr) {
    temp->next->prev = actual;
  }
  delete temp;
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

int doublyLinkedList::getLength() {
  int contador = 0;
  Nodo* actual = head;
  while (actual != nullptr) {
    actual = actual->next;
    contador++;
  }
  return contador;
}

int doublyLinkedList::search(int id) {
  Nodo* actual = head;
  int position = 0;

  while (actual != nullptr) {
    if (actual->data == id) {
      return position;
    }
    position++;
    actual = actual->next;
  }
  return -1;
}

int doublyLinkedList::get(int index) {
  Nodo* actual = head;
  int contador = 0;
  while (actual != nullptr) {
    if (contador == index) {
      return actual->data;
    }
    actual = actual->next;
    contador++;
  }
  return -1;
}

string doublyLinkedList::generateGraphviz() {
  stringstream file;

  file << "digraph g {" << endl;
  file << "rankdir=LR;" << endl;
  file << "node [shape=box, style=filled, fontname=\"Helvetica\"];" << endl;

  if (head == nullptr) {
    file << "Empty [label=\"Empty List\", color=lightblue, "
            "fillcolor=lightblue];"
         << endl;
    file << "}" << endl;
    return file.str();
  }

  file << "Head [label=\"Head\", color=lightblue, fillcolor=lightblue];"
       << endl;
  file << "null1 [label=\"nullptr\", color=lightblue, fillcolor=lightblue];"
       << endl;
  file << "null2 [label=\"nullptr\", color=lightblue, fillcolor=lightblue];"
       << endl;

  file << "Head -> \"" << head << "\";" << endl;

  Nodo* actual = head;
  while (actual != nullptr) {
    file << "\"" << actual << "\" [label=\"" << actual->data
         << "\", color=lightblue, fillcolor=lightblue];" << endl;

    if (actual->next != nullptr) {
      file << "\"" << actual << "\" -> \"" << actual->next
           << "\" [label=\"Next\", color=black];" << endl;
    } else {
      file << "\"" << actual << "\" -> null2 [label=\"Next\", color=black];"
           << endl;
    }

    if (actual->prev != nullptr) {
      file << "\"" << actual << "\" -> \"" << actual->prev
           << "\" [constraint=false, label=\"Prev\", color=black];" << endl;
    } else {
      file << "\"" << actual << "\" -> null1 [label=\"Prev\", color=black];"
           << endl;
    }

    actual = actual->next;
  }

  file << "}" << endl;
  return file.str();
}
