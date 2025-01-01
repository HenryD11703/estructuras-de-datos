#include <iostream>

#include "../lib/MyClass.h"
#include "../lib/linkedList.h"

using namespace std;

int main() {
  linkedList lista;
  lista.insertAtHead(3);
  lista.insertAtEnd(99);
  lista.insertAtHead(2);
  lista.insertAtHead(1);

  lista.insertAtIndex(100, 1);

  lista.insertAtEnd(200);

  lista.deleteAtIndex(5);

  lista.display();
  lista.generateGraphviz();
  return 0;
}

void menu() {
  while (true) {
    cout << "Seleccione una opcion: " << endl;
  }
}
