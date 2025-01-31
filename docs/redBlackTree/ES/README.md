# Árbol Rojo-Negro

El árbol rojo-negro es un tipo de árbol de auto-balanceo que se utiliza para mantener el equilibrio del árbol.
Es un árbol binario de búsqueda con un bit adicional de almacenamiento por nodo. Este bit adicional representa el color del nodo,
que puede ser rojo o negro. El color se utiliza para garantizar que el árbol permanezca aproximadamente equilibrado durante las inserciones y eliminaciones.

La complejidad temporal del árbol rojo-negro es **O(log n)** para todas las operaciones, como búsqueda, inserción y eliminación.

Un árbol rojo-negro es un tipo de árbol binario de búsqueda que cumple con las siguientes propiedades:

1. Cada nodo es **rojo** o **negro**.
2. La raíz siempre es **negra**.
3. Cada hoja (NIL) es **negra**.
4. Si un nodo es **rojo**, entonces sus hijos deben ser **negros**.
5. Cada camino desde un nodo hasta sus nodos descendientes NIL debe contener el mismo número de nodos **negros**.

## Aplicaciones del Árbol Rojo-Negro

1. Se utiliza en la implementación de **arreglos asociativos**.
2. Se utiliza en la implementación de la **biblioteca estándar de C++**.
3. Se utiliza en el **kernel de Linux** para la planificación de procesos.

## Operaciones en el Árbol Rojo-Negro

### Inserción

```cpp
void RedBlackTree::insert(int val) {
  Node* newNode = new Node(val, RED);
  root = insert(root, newNode);
  fixViolation(newNode);
}

RedBlackTree::Node* RedBlackTree::insert(Node* node, Node* newNode) {
  if (node == nullptr) {
    return newNode;
  }

  if (newNode->valor < node->valor) {
    node->left = insert(node->left, newNode);
    node->left->padre = node;
  } else if (newNode->valor > node->valor) {
    node->right = insert(node->right, newNode);
    node->right->padre = node;
  }

  return node;
}
```

Este código realiza la inserción de un nodo en el árbol rojo-negro. El nuevo nodo se inserta como un nodo rojo. Después de la inserción, el árbol se ajusta para mantener las propiedades del árbol rojo-negro.

La función fixViolation se utiliza para corregir el árbol rojo-negro después de la inserción del nuevo nodo.

```cpp
void RedBlackTree::fixViolation(Node* node) {
  Node* padre = nullptr;
  Node* abuelo = nullptr;

  while ((node != root) && (node->color != BLACK) &&
         (node->padre->color == RED)) {
    padre = node->padre;
    abuelo = padre->padre;

    // Caso 1: El padre es el hijo izquierdo del abuelo
    if (padre == abuelo->left) {
      Node* tio = abuelo->right;

      // Caso 1.1: El tío es rojo, solo se necesita recolorar
      if (tio != nullptr && tio->color == RED) {
        abuelo->color = RED;
        padre->color = BLACK;
        tio->color = BLACK;
        node = abuelo;
      } else {
        // Caso 1.2: El nodo es el hijo derecho del padre, se necesita una
        // rotación a la izquierda
        if (node == padre->right) {
          rotateLeft(padre);
          node = padre;
          padre = node->padre;
        }

        // Caso 1.3: El nodo es el hijo izquierdo del padre, se necesita una
        // rotación a la derecha
        rotateRight(abuelo);
        swap(padre->color, abuelo->color);
        node = padre;
      }
    } else {  // Caso 2: El padre es el hijo derecho del abuelo
      Node* tio = abuelo->left;

      // Caso 2.1: El tío es rojo, solo se necesita recolorar
      if (tio != nullptr && tio->color == RED) {
        abuelo->color = RED;
        padre->color = BLACK;
        tio->color = BLACK;
        node = abuelo;
      } else {
        // Caso 2.2: El nodo es el hijo izquierdo del padre, se necesita una
        // rotación a la derecha
        if (node == padre->left) {
          rotateRight(padre);
          node = padre;
          padre = node->padre;
        }

        // Caso 2.3: El nodo es el hijo derecho del padre, se necesita una
        // rotación a la izquierda
        rotateLeft(abuelo);
        swap(padre->color, abuelo->color);
        node = padre;
      }
    }
  }

  root->color = BLACK;
}
```

Los pasos basicos para la inserción son los siguientes:

1. Insertar el nodo como un nodo rojo.

2. Si el nodo padre del nodo insertado es rojo, entonces hay un conflicto de colores y se deben realizar las siguientes operaciones:

   - El tío del nodo es rojo.
   - El tío del nodo es negro y el nodo es el hijo derecho del padre.
   - El tío del nodo es negro y el nodo es el hijo izquierdo del padre.

### Eliminacion

```cpp
void RedBlackTree::deleteNode(int val) { root = deleteNode(root, val); }

RedBlackTree::Node* RedBlackTree::deleteNode(Node* node, int val) {
  if (node == nullptr) {
    return node;
  }

  if (val < node->valor) {
    node->left = deleteNode(node->left, val);
  } else if (val > node->valor) {
    node->right = deleteNode(node->right, val);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      Node* temp = node->left ? node->left : node->right;

      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }
      delete temp;
    } else {
      Node* temp = node->right;

      while (temp->left != nullptr) {
        temp = temp->left;
      }

      node->valor = temp->valor;
      node->right = deleteNode(node->right, temp->valor);
    }
  }

  if (node == nullptr) {
    return node;
  }

  return node;
}
```

Este código realiza la eliminación de un nodo en el árbol rojo-negro. El nodo se elimina y el árbol se ajusta para mantener las propiedades del árbol rojo-negro.

La función deleteNode se utiliza para eliminar el nodo del árbol rojo-negro.

Los pasos básicos de la eliminación son:

1. Eliminar el nodo del árbol rojo-negro.

2. Ajustar el árbol para mantener las propiedades del árbol rojo-negro.

## Referencias

- [Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
- [GeeksforGeeks](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)
- [Programiz](https://www.programiz.com/dsa/red-black-tree)
- [TutorialsPoint](https://www.tutorialspoint.com/data_structures_algorithms/red_black_tree_algorithm.htm)
- [Red Black Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)
