# Red Black Tree

The red black tree is a type of self balancing trees which is used to maintain the balance of the tree.
It is a binary search tree with one extra bit of storage per node. The extra bit represents the color of the node.
It is either red or black. The color is used to ensure that the tree remains approximately balanced during insertions and deletions.

The time complexity of the red black tree is O(log n) for all the operations like search, insert and delete.

The red black tree is a type of binary search tree which has the following properties:

1. Every node is either red or black.
2. The root is always black.
3. Every leaf (NIL) is black.
4. If a red node has children, then the children are always black.
5. Every path from a node to its descendant NIL nodes must have the same number of black nodes.

## Applications of Red Black Tree

1. It is used in the implementation of the associative arrays.
2. It is used in the implementation of the C++ standard library.
3. It is used in the Linux kernel for the process scheduling.

## Operations on Red Black Tree

### Insertion

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

This does the insertion of the node in the red black tree. The new node is inserted as a red node. After the insertion, the tree is fixed to maintain the properties of the red black tree.

The fixViolation function is used to fix the red black tree after the insertion of the new node.

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
    } else  // Caso 2: El padre es el hijo derecho del abuelo
    {
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

So basically Insertion steps are:

1. Insert the node as a red node.

2. Fix the tree to maintain the properties of the red black tree.

3. If the parent of the node is red, then there are three cases:

   1. The uncle of the node is red.
   2. The uncle of the node is black and the node is the right child of the parent.
   3. The uncle of the node is black and the node is the left child of the parent.

### Deletion

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

This does the deletion of the node in the red black tree. The node is deleted and the tree is fixed to maintain the properties of the red black tree.

The deleteNode function is used to delete the node from the red black tree.

So basically Deletion steps are:

1. Delete the node from the red black tree.

2. Fix the tree to maintain the properties of the red black tree.

## Complexity Analysis

The time complexity of the red black tree is O(log n) for all the operations like search, insert and delete.

## References

- [Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
- [GeeksforGeeks](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)
- [Programiz](https://www.programiz.com/dsa/red-black-tree)
- [TutorialsPoint](https://www.tutorialspoint.com/data_structures_algorithms/red_black_tree_algorithm.htm)
- [Red Black Tree Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)
