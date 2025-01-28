import GraphvizComponent from '../utils/Graphviz';
import { useState, useEffect, useCallback } from 'react';
import styles from './RedBlackTree.module.css';
import {
  fetchTraversals,
  fetchGraphviz,
  insertNode,
  deleteNode,
} from '../scripts/redBlackTreeService';

const RedBlackTree = () => {
  const [rbInput, setRbInput] = useState<string>();
  const [nodeValue, setNodeValue] = useState<number | string>('');
  const [traversals, setTraversals] = useState({
    preorderRB: '',
    inorder: '',
    postorder: '',
  });

  const updateTreeData = useCallback(async () => {
    try {
      const [graphvizData, traversalsData] = await Promise.all([
        fetchGraphviz(),
        fetchTraversals(),
      ]);
      setRbInput(graphvizData);
      setTraversals(traversalsData);
    } catch (error) {
      console.error('Error updating tree data:', error);
    }
  }, []);

  const handleInsert = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await insertNode(nodeValue);
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
        await deleteNode(nodeValue);
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
      <div className={styles.Header}>Red-Black Tree Component</div>
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
          <GraphvizComponent input={rbInput} />
        </div>

        <div className={styles.TraversalsContainer}>
          <h3 className={styles.TraversalsHeader}>Tree Traversals</h3>
          <div className={styles.TraversalItem}>
            <span className={styles.TraversalLabel}>Preorder:</span>
            <span className={styles.TraversalValue}>
              {traversals.preorderRB}
            </span>
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

export default RedBlackTree;