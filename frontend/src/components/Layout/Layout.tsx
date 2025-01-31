import { useState } from 'react';
import Sidebar from './Sidebar';
import styles from './Layout.module.css';
import LinkedList from '../../pages/LinkedList';
import BinarySearchTree from '../../pages/BinarySearchTree';
import AVLTree from '../../pages/AVLTree';
import DoublyLinkedList from '../../pages/DoublyLinkedList';
import DoublyCircularLinkedList from '../../pages/DoublyCircularLinkedList';
import GraphvizComponent from '../../utils/Graphviz';
import SparseMatrix from '../../pages/SparseMatrix';
import RedBlackTree from '../../pages/RedBlackTree';
import BTree from '../../pages/BTree';

const Layout = () => {
  const [selectedStructure, setSelectedStructure] = useState<string | null>(
    null
  );

  const handleStructureSelect = (structure: string) => {
    setSelectedStructure(structure);
  };
  //   const structures = [
  //     { name: 'Linked List', icon: '📃' },
  //     { name: 'Doubly Linked List', icon: '📜' },
  //     { name: 'Doubly Circular Linked List', icon: '🔄' },
  //     { name: 'Binary Search Tree (BST)', icon: '🌳' },
  //     { name: 'AVL Tree', icon: '🏗️' },
  //     { name: 'Red-Black Tree', icon: '🍁' },
  //     { name: 'B-Tree', icon: '🌴' },
  //   ];
  const renderSelectedStructure = () => {
    switch (selectedStructure) {
      case 'Linked List':
        return <LinkedList />;
      case 'Binary Search Tree (BST)':
        return <BinarySearchTree />;
      case 'AVL Tree':
        return <AVLTree />;
      case 'Doubly Linked List':
        return <DoublyLinkedList />;
      case 'Doubly Circular Linked List':
        return <DoublyCircularLinkedList />;
      case 'Sparse Matrix':
        return <SparseMatrix />;
      case 'Red-Black Tree':
        return <RedBlackTree />
      case 'B-Tree':
        return <BTree />;
      default:
        return <div>Seleccione una estructura de datos</div>;
    }
  };

  return (
    <div className={styles.Layout}>
      <Sidebar onSelectStructure={handleStructureSelect} />
      <div className={styles.Content}>{renderSelectedStructure()}</div>
    </div>
  );
};

export default Layout;
