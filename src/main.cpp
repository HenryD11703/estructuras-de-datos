#include <iostream>

#include "../include/binarySearchTree.h"
#include "../include/doublyCircularList.h"
#include "../include/doublyLinkedList.h"
#include "../include/linkedList.h"

using namespace std;

void displayMenu() {
  cout << "\n===============================" << endl;
  cout << "          Menu de Opciones     " << endl;
  cout << "===============================" << endl;
  cout << "1. Lista Enlazada (Simple)" << endl;
  cout << "2. Lista Doblemente Enlazada" << endl;
  cout << "3. Lista Doblemente Circular" << endl;
  cout << "4. Arbol Binario de Busqueda" << endl;
  cout << "5. Salir" << endl;
  cout << "Selecciona una opción: ";
}

void handleBinarySearchTree(binarySearchTree& bst) {
  int choice, value;
  cout << "\nOpciones del Arbol binario de busqueda: " << endl;
  cout << "1. Insertar" << endl;
  cout << "2. Eliminar" << endl;
  cin >> choice;

  switch (choice) {
    case 1:
      cout << "Valor a insertar: ";
      cin >> value;
      bst.insert(value);
      break;
    case 2:
      cout << "Valor a eliminar: ";
      cin >> value;
      bst.deleteNode(value);
      break;
    default:
      break;
  }
}

void handleLinkedList(linkedList& ll) {
  int choice, value, index;
  cout << "\nOpciones de Lista Enlazada:" << endl;
  cout << "1. Insertar al inicio" << endl;
  cout << "2. Insertar en índice" << endl;
  cout << "3. Insertar al final" << endl;
  cout << "4. Eliminar cabeza" << endl;
  cout << "5. Eliminar final" << endl;
  cout << "6. Mostrar lista" << endl;
  cout << "7. Buscar valor" << endl;
  cout << "8. Obtener valor por índice" << endl;
  cout << "9. Generar Graphviz" << endl;
  cout << "Selecciona una opción: ";
  cin >> choice;

  switch (choice) {
    case 1:
      cout << "Valor a insertar: ";
      cin >> value;
      ll.insertAtHead(value);
      break;
    case 2:
      cout << "Valor a insertar: ";
      cin >> value;
      cout << "Índice: ";
      cin >> index;
      ll.insertAtIndex(value, index);
      break;
    case 3:
      cout << "Valor a insertar: ";
      cin >> value;
      ll.insertAtEnd(value);
      break;
    case 4:
      ll.deleteHead();
      break;
    case 5:
      ll.deleteEnd();
      break;
    case 6:
      ll.display();
      break;
    case 7:
      cout << "Valor a buscar: ";
      cin >> value;
      cout << "Posición: " << ll.search(value) << endl;
      break;
    case 8:
      cout << "Índice: ";
      cin >> index;
      cout << "Valor: " << ll.get(index) << endl;
      break;
    case 9:
      ll.generateGraphviz();
      break;
    default:
      cout << "Opción no válida." << endl;
  }
}

void handleDoublyLinkedList(doublyLinkedList& dll) {
  int choice, value, index;
  cout << "\nOpciones de Lista Doblemente Enlazada:" << endl;
  cout << "1. Insertar al inicio" << endl;
  cout << "2. Insertar en índice" << endl;
  cout << "3. Insertar al final" << endl;
  cout << "4. Eliminar cabeza" << endl;
  cout << "5. Eliminar final" << endl;
  cout << "6. Mostrar lista" << endl;
  cout << "7. Buscar valor" << endl;
  cout << "8. Obtener valor por índice" << endl;
  cout << "9. Generar Graphviz" << endl;
  cout << "Selecciona una opción: ";
  cin >> choice;

  switch (choice) {
    case 1:
      cout << "Valor a insertar: ";
      cin >> value;
      dll.insertAtHead(value);
      break;
    case 2:
      cout << "Valor a insertar: ";
      cin >> value;
      cout << "Índice: ";
      cin >> index;
      dll.insertAtIndex(value, index);
      break;
    case 3:
      cout << "Valor a insertar: ";
      cin >> value;
      dll.insertAtEnd(value);
      break;
    case 4:
      dll.deleteHead();
      break;
    case 5:
      dll.deleteEnd();
      break;
    case 6:
      dll.display();
      break;
    case 7:
      cout << "Valor a buscar: ";
      cin >> value;
      cout << "Posición: " << dll.search(value) << endl;
      break;
    case 8:
      cout << "Índice: ";
      cin >> index;
      cout << "Valor: " << dll.get(index) << endl;
      break;
    case 9:
      dll.generateGraphviz();
      break;
    default:
      cout << "Opción no válida." << endl;
  }
}

void handleDoublyCircularList(doublyCircularList& dcl) {
  int choice, value, index;
  cout << "\nOpciones de Lista Doblemente Circular:" << endl;
  cout << "1. Insertar al inicio" << endl;
  cout << "2. Insertar al final" << endl;
  cout << "3. Eliminar cabeza" << endl;
  cout << "4. Eliminar final" << endl;
  cout << "5. Insertar en índice" << endl;
  cout << "6. Eliminar indice" << endl;
  cout << "7. Buscar valor" << endl;
  cout << "8. Obtener valor por índice" << endl;
  cout << "9. Obtener longitud" << endl;
  cout << "10. Generar Graphviz" << endl;
  cout << "Selecciona una opción: ";
  cin >> choice;

  switch (choice) {
    case 1:
      cout << "Valor a insertar: ";
      cin >> value;
      dcl.insertAtHead(value);
      break;
    case 2:
      cout << "Valor a insertar: ";
      cin >> value;
      dcl.insertAtTail(value);
      break;
    case 3:
      dcl.deleteAtHead();
      break;
    case 4:
      dcl.deleteAtTail();
      break;
    case 5:
      cout << "Valor a insertar: ";
      cin >> value;
      cout << "Indice: ";
      cin >> index;
      dcl.insertAtIndex(index, value);
      break;
    case 6:
      cout << "Indice: ";
      cin >> index;
      dcl.deleteAtIndex(index);
      break;
    case 7:
      cout << "Valor a buscar: ";
      cin >> value;
      dcl.search(value);
      break;
    case 8:
      cout << "Indice a buscar: ";
      cin >> index;
      dcl.get(index);
      break;
    case 9:
      cout << "\nLongitud de la lista: " << dcl.getLength() << endl;
      break;
    case 10:
      dcl.generateGraphviz();
      break;
    default:
      cout << "Opción no válida." << endl;
  }
}

int main() {
  linkedList ll;
  doublyLinkedList dll;
  doublyCircularList dcl;
  binarySearchTree bst;

  int choice;
  while (true) {
    displayMenu();
    cin >> choice;

    switch (choice) {
      case 1:
        handleLinkedList(ll);
        break;
      case 2:
        handleDoublyLinkedList(dll);
        break;
      case 3:
        handleDoublyCircularList(dcl);
        break;
      case 4:
        handleBinarySearchTree(bst);
        break;
      case 5:
        cout << "Saliendo del programa..." << endl;
        return 0;
      default:
        cout << "Opción no válida. Por favor intenta de nuevo." << endl;
    }
  }

  return 0;
}
