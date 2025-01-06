# Doubly Linked List

A doubly linked list is a data structure that consists of a sequence of elements in which each element has a reference to the next and the previous element in the sequence. This allows for efficient insertion and deletion operations at both the beginning and end of the list.

## Advantages of Doubly Linked Lists over Singly Linked Lists

1. Bidirectional traversal
2. Ease of insertion/deletion at both ends

## The node class

```cpp
  struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int d) : data(d), next(nullptr), prev(nullptr) {}
  };
```

As mentioned earlier, the Node class is the building block of the doubly linked list. Each node object must contain three fields: `data`, `next`, and `prev`. The `data` field will store the value of the element, the `next` field is a pointer to the next node in the list, and the `prev` field is a pointer to the previous node in the list.

This helps to create a chain-like structure where each node is connected to the next and previous nodes. The first node will have a `prev` field with a `null` value, and the last node will have a `next` field with a `null` value.

```mermaid
graph TD
    Head["head"]
    Head --> node1["1 | 0x5f4e03efb310"]
    node1 --> node0["nullptr"]
    node1 --> node2["100 | 0x5f4e03efb330"]
    node2 --> node3["2 | 0x5f4e03efb2f0"]
    node3 --> node4["3 | 0x5f4e03efb2b0"]
    node4 --> node5["99 | 0x5f4e03efb2d0"]
    node5 --> node6["nullptr"]
    node2 --> node1
    node3 --> node2
    node4 --> node3
    node5 --> node4
```

As you can see, each node points to the next and previous nodes, creating a doubly linked list structure.

## Operations on Doubly Linked List

### Insert at Head

```cpp
int doublyLinkedList::insertAtHead(int id) {
  Nodo* nuevo = new Nodo(id);
  nuevo->next = head;
  if (head != nullptr) {
    head->prev = nuevo;
  }
  head = nuevo;
  return 1;
}

```

This creates a new node with the given data, then moves the node that was the head to the next field of the new node, and finally sets the new node as the head.

![Insert at Head](InsertAtHead.png)

The time complexity of this operation is O(1) because it doesn't depend on the number of nodes in the list.

### Delete at Head

```cpp
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
```

This operation deletes the head node by moving the head to the next node and setting the previous field of the new head to `nullptr`.

![Delete at Head](DeleteAtHead.png)

The time complexity of this operation is O(1) because it doesn't depend on the number of nodes in the list.

### Insert at End

```cpp
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
```

This operation inserts a new node at the end of the list by traversing the list until the last node and then setting the next field of the last node to the new node.

![Insert at End](InsertAtEnd.png)

The time complexity of this operation is O(n) in the worst case because it depends on the number of nodes in the list.

### Delete at End

```cpp
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
```

This operation deletes the last node in the list by traversing the list until the second-to-last node and then setting the next field of the second-to-last node to `nullptr`.

![Delete at End](DeleteAtEnd.png)

The time complexity of this operation is O(n) in the worst case because it depends on the number of nodes in the list.

### Insert at Position

```cpp
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
```

This operation inserts a new node at the specified index by traversing the list until the node before the specified index and then setting the next field of the new node to the node at the specified index.

![Insert at Position](InsertAtPosition.png)

The time complexity of this operation is O(n) in the worst case because it depends on the number of nodes in the list.

### Delete at Position

```cpp
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
```

This operation deletes the node at the specified index by traversing the list until the node before the specified index and then setting the next field of the node before the specified index to the node after the specified index.

![Delete at Position](DeleteAtPosition.png)

The time complexity of this operation is O(n) in the worst case because it depends on the number of nodes in the list.

### Get Size

```cpp
int doublyLinkedList::getLength() {
  int contador = 0;
  Nodo* actual = head;
  while (actual != nullptr) {
    actual = actual->next;
    contador++;
  }
  return contador;
}
```

This operation returns the number of nodes in the list by traversing the list and counting the nodes.

The time complexity of this operation is O(n) because it depends on the number of nodes in the list.

### Search

```cpp
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
```

This operation searches for a node with the specified data by traversing the list and comparing the data of each node with the specified data.

The time complexity of this operation is O(n) because it depends on the number of nodes in the list.

### Get Element at Position

```cpp
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
```

This operation returns the data of the node at the specified index by traversing the list until the specified index and then returning the data of the node at that index.

The time complexity of this operation is O(n) because it depends on the number of nodes in the list.


