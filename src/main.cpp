#include <iostream>

#include "../include/doublyCircularList.h"
#include "../include/doublyLinkedList.h"
#include "../include/linkedList.h"

using namespace std;

int main() {
  doublyLinkedList lista;
  lista.insertAtHead(1);
  lista.insertAtHead(2);
  lista.insertAtHead(3);
  lista.insertAtHead(4);

  lista.generateGraphviz();

  return 0;
}
