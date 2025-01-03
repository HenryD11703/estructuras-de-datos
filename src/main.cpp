#include <iostream>

#include "../lib/DoublyLinkedList.h"
#include "../lib/linkedList.h"

using namespace std;

int main() {
  doublyLinkedList lista;
  lista.insertAtHead(1);
  lista.insertAtHead(2);
  lista.insertAtHead(3);
  lista.insertAtEnd(100);

  // lista.deleteHead();

  lista.display();

  return 0;
}

void menu() {
  while (true) {
    cout << "Seleccione una opcion: " << endl;
  }
}
