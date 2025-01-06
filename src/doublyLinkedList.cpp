#include "../include/doublyLinkedList.h"

#include <fstream>
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

void doublyLinkedList::generateGraphviz() {
  ofstream archivo;
  archivo.open("./utils/graphviz/doublyLinkedList.dot");

  if (archivo.is_open()) {
    archivo << "digraph g {" << endl;
    archivo << "rankdir=LR;"
            << endl;  // Para que el grafo se dibuje de izquierda a derecha

    // Caso lista vacía
    if (head == nullptr) {
      archivo << "Empty [label=\"Empty List\"];" << endl;
      archivo << "}" << endl;
      archivo.close();
      return;
    }

    // Nodos especiales
    archivo << "Head [label=\"head\"];" << endl;
    archivo << "null1 [label=\"nullptr\"];" << endl;
    archivo << "null2 [label=\"nullptr\"];" << endl;

    // Enlace desde head al primer nodo
    archivo << "Head -> \"" << head << "\";" << endl;

    // Recorrer la lista
    Nodo* actual = head;
    while (actual != nullptr) {
      // Crear nodo actual
      archivo << "\"" << actual << "\" [label=\"" << actual->data << "\"];"
              << endl;

      // Enlaces hacia adelante
      if (actual->next != nullptr) {
        archivo << "\"" << actual << "\" -> \"" << actual->next << "\";"
                << endl;
      } else {
        archivo << "\"" << actual << "\" -> null2;" << endl;
      }

      // Enlaces hacia atrás
      if (actual->prev != nullptr) {
        archivo << "\"" << actual << "\" -> \"" << actual->prev
                << "\" [constraint=false];" << endl;
      } else {
        archivo << "\"" << actual << "\" -> null1;" << endl;
      }

      actual = actual->next;
    }

    archivo << "}" << endl;
    archivo.close();
  }
}