#include "../include/linkedList.h"

#include <fstream>
#include <iostream>

using namespace std;

// el puntero head, apunta al primer elemento
// o si la lista esta vacia a nullptr

linkedList::linkedList() : head(nullptr) {}

linkedList::~linkedList() {
  Nodo* actual = head;
  while (actual != nullptr) {
    Nodo* siguiente = actual->next;
    delete actual;
    actual = siguiente;
  }
}
// por eso, cuando se crea un nodo en el inicio
// se pone que el head apunta a este
// y el next de este nuevo nodo ahora apunta al que
// antes fue el head, y el head se apunta al nuevo

// Complejidad O(1) por que no recorre
int linkedList::insertAtHead(int id) {
  Nodo* nuevo = new Nodo(id);
  nuevo->next = head;
  head = nuevo;
  return 1;
}

int linkedList::deleteHead() {
  if (head == nullptr) {
    return 0;
  }
  Nodo* temp = head;
  head = head->next;
  delete temp;
  return 1;
}

int linkedList::insertAtIndex(int id, int index) {
  if (index == 0) {
    insertAtHead(id);
    return 1;
  }

  int posicion = 0;
  Nodo* actual = head;
  while (actual != nullptr && posicion + 1 != index) {
    posicion++;
    actual = actual->next;
  }
  if (actual != nullptr) {
    Nodo* nuevo = new Nodo(id);
    nuevo->next = actual->next;
    actual->next = nuevo;
  } else {
    cout << "Posicion invalida" << endl;
    return 0;
  }
  return 1;
}

int linkedList::deleteAtIndex(int index) {
  if (index < 0) {
    cout << "No existen indices negativos" << endl;
    return 0;  // Índice inválido
  }
  if (index == 0) {
    deleteHead();
    return 0;
  }
  if (head == nullptr) {
    return 0;
  }
  int contador = 0;
  Nodo* actual = head;
  while (actual != nullptr && contador != index - 1) {
    contador++;
    actual = actual->next;
  }
  if (actual == nullptr || actual->next == nullptr) {
    cout << "No se encontro el indice" << endl;
    return 0;
  }
  Nodo* nodeToDelete = actual->next;
  actual->next = nodeToDelete->next;
  delete nodeToDelete;
  return 1;
}

int linkedList::insertAtEnd(int id) {
  Nodo* actual = head;
  while (actual->next != nullptr) {
    actual = actual->next;
  }
  // actual apunta a nullptr, entonces
  // hacer que actual apunte a mi nuevo nodo
  Nodo* nuevo = new Nodo(id);
  actual->next = nuevo;
  return 1;
}

int linkedList::deleteEnd() {
  if (head == nullptr) {
    return 0;
  }
  Nodo* actual = head;
  while (actual->next != nullptr && actual->next->next != nullptr) {
    actual = actual->next;
  }

  delete actual->next;
  actual->next = nullptr;
  return 1;
}

void linkedList::display() {
  Nodo* actual = head;
  while (actual != nullptr) {
    cout << actual->data << " -> ";
    actual = actual->next;
  }
  cout << "nullptr" << endl;
}

void linkedList::generateGraphviz() {
  ofstream archivo;
  archivo.open("../utils/graphviz/linkedList.dot");
  if (archivo.is_open()) {
    archivo << "digraph g {" << endl;
    archivo << "Head [label=\"head\"];" << endl;
    archivo << "Head -> 1" << endl;

    Nodo* actual = head;
    int contador = 1;

    while (actual != nullptr) {
      archivo << contador << "[label=\"" << actual->data << "\\n"
              << actual << "\"]" << endl;
      archivo << contador << "->" << contador + 1 << endl;
      contador++;
      actual = actual->next;
    }
    archivo << contador << "[label=\"nullptr\"]" << endl;
    archivo << "}" << endl;
    archivo.close();
  }
}

int linkedList::getLength() {
  int contador = 0;
  Nodo* actual = head;
  while (actual != nullptr) {
    actual = actual->next;
    contador++;
  }
  return contador;
}

int linkedList::search(int id) {
  int posicion = 0;
  Nodo* actual = head;
  while (actual != nullptr) {
    if (actual->data == id) {
      return posicion;
    }
    posicion++;
    actual = actual->next;
  }
  return -1;
}

int linkedList::get(int index) {
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
