#include <iostream>

#include "../include/doublyLinkedList.h"
#include "../include/linkedList.h"

using namespace std;

int main() {
  doublyLinkedList lista;
  lista.insertAtHead(1);
  lista.insertAtHead(2);
  lista.insertAtHead(3);
  cout << lista.search(3) << endl;
  lista.generateGraphviz();

  // lista.deleteHead();

  lista.display();

  return 0;
}

void menu() {
  while (true) {
    cout << "Seleccione una opcion: " << endl;
  }
}
