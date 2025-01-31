# B-Tree

A B-Tree is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time. The B-tree is a generalization of a binary search tree in that a node can have more than two children. Unlike self-balancing binary search trees, the B-tree is optimized for systems that read and write large blocks of data. It is commonly used in databases and file systems.

## Why B-Tree?

The B-tree is a data structure that keeps data sorted and allows searches, insertions, and deletions in logarithmic amortized time. It is a generalization of a binary search tree in that a node can have more than two children. Unlike self-balancing binary search trees, the B-tree is optimized for systems that read and write large blocks of data. It is commonly used in databases and file systems.

## A bit of theory

A B-tree of order `m` is a tree which satisfies the following properties:

1. Every node has at most `m` children.
2. Every node (except root) has at least `m/2` children.
3. Every non-leaf node with `k` children contains `k-1` keys.
4. All leaves appear on the same level.

## Insertion

To insert a new element into a B-tree, we start at the root and recursively move down the tree until we reach a leaf node. If the leaf node has less than `m-1` keys, we can insert the new element into the leaf node. Otherwise, we must split the node into two nodes and promote the median key to the parent node.

Steps to insert a key `k` into a B-tree:

1. Start at the root node.

2. If the root node is full, split the root node into two nodes and promote the median key to the parent node.

3. Recursively move down the tree until we reach a leaf node.

4. If the leaf node is not full, insert the key `k` into the leaf node.

5. If the leaf node is full, split the leaf node into two nodes and promote the median key to the parent node.

6. If the parent node is full, split the parent node into two nodes and promote the median key to the grandparent node.

7. Continue this process until we reach the root node.

## Deletion

To delete an element from a B-tree, we start at the root and recursively move down the tree until we reach a leaf node. If the leaf node has more than `m/2` keys, we can delete the element from the leaf node. Otherwise, we must borrow a key from a sibling node or merge the node with a sibling node.

Steps to delete a key `k` from a B-tree:

1. Start at the root node.

2. Recursively move down the tree until we reach a leaf node.

3. If the leaf node has more than `m/2` keys, delete the key `k` from the leaf node.

4. If the leaf node has less than `m/2` keys, borrow a key from a sibling node or merge the node with a sibling node.

5. Continue this process until we reach the root node.

## Complexity

A B-tree of order `m` has the following time complexity:

- Search: `O(log_m(n))`

- Insertion: `O(log_m(n))`

- Deletion: `O(log_m(n))`

where `n` is the number of elements in the B-tree.

## Applications

B-trees are commonly used in databases and file systems because they can read and write large blocks of data efficiently. Some of the applications of B-trees include:

- Databases: B-trees are used to index data in databases, allowing fast searches, insertions, and deletions.

- File systems: B-trees are used to organize files on disk, allowing fast access to files and directories.

- Operating systems: B-trees are used to manage memory and disk space efficiently, allowing fast access to files and directories.

- Network routers: B-trees are used to store routing tables, allowing fast lookup of IP addresses.

- Version control systems: B-trees are used to store file revisions, allowing fast access to different versions of files.

## References

- [Wikipedia](https://en.wikipedia.org/wiki/B-tree)
- [GeeksforGeeks](https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/)
