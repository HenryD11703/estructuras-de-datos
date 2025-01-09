# Binary Search Tree

A binary search tree is a binary tree in which every node fits a specific ordering property: all left descendents <= n < all right descendents. This must be true for each node n.

This data structure provides efficient insertion, deletion, and search operations. It is also known as an ordered binary tree.

## Properties

- The left subtree of a node contains only nodes with keys lesser than the node’s key.
- The right subtree of a node contains only nodes with keys greater than the node’s key.
- The left and right subtree each must also be a binary search tree.

To be able to understand the binary search tree, we need to understand the following terms:

- **Root**: The top node in a tree.
- **Parent**: Any node except the root node has one edge upward to a node called a parent.
- **Child**: The node below a given node connected by its edge downward is called a child node.
- **Leaf**: The node which does not have any child node is called the leaf node.
- **Subtree**: A subtree is a tree that exists within a tree.

One of the most important things to know when working with binary search trees is **recursion**. Recursion is a technique in which a function calls itself as a subroutine. This allows us to break down complex problems into simpler problems that are easier to solve.

### Recursion

Any function which calls itself is called recursive. A recursive method solves a problem by
calling a copy of itself to work on a smaller problem. This is called the recursion step. The
recursion step can result in many more such recursive calls.

Recursion is a useful technique borrowed from mathematics. Recursive code is generally shorter
and easier to write than iterative code. Generally, loops are turned into recursive functions when they are compiled or interpreted.

A recursive function performs a task in part by calling itself to perform the subtasks. At some
point, the function encounters a subtask that it can perform without calling itself. This case, where the function does not recur, is called the base case. The former, where the function calls itself to perform a subtask, is referred to as the ecursive case. We can write all recursive functions using the format. (Data Structures and Algorithms made easy: Data Structures and Algorithmic Puzzles, Narasimha Karumanchi)

```cpp
void recursiveFunction(parameters) {
    if (base case) {
        // base case
        return some base case value;
    } else if (other base case) {
        // other base case
        return some other base case value;
    } else {
        // recursive case
        recursiveFunction(modified parameters);
    }
}
```

Another important thing to have in mind is the level of a node. The level of a node is the number of edges on the path from the root node to that node. The root node is at level 0.

And the time complexity of the binary search tree operations is O(h), where h is the height of the tree. The height of the tree is the number of edges on the longest path from the root node to a leaf node.

## The node structure

The node structure is the basic building block of a binary search tree. It contains the following fields:

- **value**: The data to be stored in the node.
- **left**: A pointer to the left child node.
- **right**: A pointer to the right child node.
- **count**: The number of times the value is present in the tree, this is helpful when we allow duplicates in the tree.

```cpp
  struct Nodo {
    Nodo* left;
    Nodo* right;
    int value;
    int count;
    Nodo(int val) : left(nullptr), right(nullptr), value(val), count(1) {}
  };
```

