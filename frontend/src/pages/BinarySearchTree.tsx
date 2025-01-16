import GraphvizComponent from '../utils/Graphviz';
import { useState, useEffect, useCallback } from 'react';
import styles from './BinarySearchTree.module.css';

const BinarySearchTree = () => {
  const [bstInput, setBstInput] = useState<string>();
  const [nodeValue, setNodeValue] = useState<number | string>('');
  const [traversals, setTraversals] = useState({
    preorder: '',
    inorder: '',
    postorder: '',
  });

  const fetchTraversals = async () => {
    try {
      const [preorderRes, inorderRes, postorderRes] = await Promise.all([
        fetch('http://192.168.1.113:8080/binarySearchTree/Preorder'),
        fetch('http://192.168.1.113:8080/binarySearchTree/Inorder'),
        fetch('http://192.168.1.113:8080/binarySearchTree/Postorder'),
      ]);

      const [preorderData, inorderData, postorderData] = await Promise.all([
        preorderRes.json(),
        inorderRes.json(),
        postorderRes.json(),
      ]);

      setTraversals({
        preorder: preorderData.preorden || '',
        inorder: inorderData.inorder || '',
        postorder: postorderData.postorder || '',
      });
    } catch (error) {
      console.error('Error al obtener los recorridos:', error);
    }
  };

  const fetchGraphviz = async () => {
    try {
      const response = await fetch(
        'http://192.168.1.113:8080/binarySearchTree/getGraphviz'
      );
      const data = await response.json();
      if (data.status === 'success') {
        setBstInput(data.graph);
      } else {
        console.error('Error al obtener Graphviz:', data.message);
      }
    } catch (error) {
      console.error('Error en la solicitud:', error);
    }
  };

  const updateTreeData = useCallback(async () => {
    await Promise.all([fetchGraphviz(), fetchTraversals()]);
  }, []);

  const handleInsert = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await fetch('http://192.168.1.113:8080/binarySearchTree/insert', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ value: nodeValue }),
        });
        await updateTreeData();
      } catch (error) {
        console.error('Error al insertar el nodo:', error);
      }
    }
    setNodeValue('');
  };

  const handleDelete = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await fetch('http://192.168.1.113:8080/binarySearchTree/delete', {
          method: 'DELETE',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ value: nodeValue }),
        });
        await updateTreeData();
      } catch (error) {
        console.error('Error al eliminar el nodo:', error);
      }
    }
    setNodeValue('');
  };

  useEffect(() => {
    updateTreeData();
  }, [updateTreeData]);

  return (
    <div className={styles.Container}>
      <div className={styles.Header}>Binary Search Tree (BST) Component</div>
      <div className={styles.Form}>
        <div className={styles.InputContainer}>
          <label>Node Value:</label>
          <input
            type="number"
            value={nodeValue}
            onChange={(e) => setNodeValue(Number(e.target.value))}
            placeholder="Enter node value"
          />
        </div>
        <div className={styles.Buttons}>
          <button className={styles.Button} onClick={handleInsert}>
            Insert
          </button>
          <button className={styles.Button} onClick={handleDelete}>
            Delete
          </button>
        </div>
      </div>

      <div className={styles.ContentContainer}>
        <div className={styles.GraphContainer}>
          <GraphvizComponent input={bstInput} />
        </div>

        <div className={styles.TraversalsContainer}>
          <h3 className={styles.TraversalsHeader}>Tree Traversals</h3>
          <div className={styles.TraversalItem}>
            <span className={styles.TraversalLabel}>Preorder:</span>
            <span className={styles.TraversalValue}>{traversals.preorder}</span>
          </div>
          <div className={styles.TraversalItem}>
            <span className={styles.TraversalLabel}>Inorder:</span>
            <span className={styles.TraversalValue}>{traversals.inorder}</span>
          </div>
          <div className={styles.TraversalItem}>
            <span className={styles.TraversalLabel}>Postorder:</span>
            <span className={styles.TraversalValue}>
              {traversals.postorder}
            </span>
          </div>
        </div>
      </div>
    </div>
  );
};

export default BinarySearchTree;
