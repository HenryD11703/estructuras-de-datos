import GraphvizComponent from '../utils/Graphviz';
import { useState, useEffect, useCallback } from 'react';
import styles from './DoublyCircularLinkedList.module.css';
import {
  fetchGraphviz,
  fetchLength,
  insertHead,
  deleteHead,
  insertEnd,
  deleteEnd,
  insertAtIndex,
  deleteAtIndex,
} from '../scripts/doublyCircularListService';

const DoublyCircularList = () => {
  const [dclInput, setDclInput] = useState<string>();
  const [nodeValue, setNodeValue] = useState<number | string>('');
  const [indexValue, setIndexValue] = useState<number | string>('');
  const [listLength, setListLength] = useState<number>(0);

  const updateListData = useCallback(async () => {
    try {
      const [graphvizData, lengthData] = await Promise.all([
        fetchGraphviz(),
        fetchLength(),
      ]);
      setDclInput(graphvizData);
      setListLength(lengthData);
    } catch (error) {
      console.error('Error updating list data:', error);
    }
  }, []);

  const handleInsertHead = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await insertHead(nodeValue);
        await updateListData();
      } catch (error) {
        console.error('Error al insertar en la cabeza:', error);
      }
    }
    setNodeValue('');
  };

  const handleDeleteHead = async () => {
    try {
      await deleteHead();
      await updateListData();
    } catch (error) {
      console.error('Error al eliminar la cabeza:', error);
    }
  };

  const handleInsertEnd = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await insertEnd(nodeValue);
        await updateListData();
      } catch (error) {
        console.error('Error al insertar al final:', error);
      }
    }
    setNodeValue('');
  };

  const handleDeleteEnd = async () => {
    try {
      await deleteEnd();
      await updateListData();
    } catch (error) {
      console.error('Error al eliminar del final:', error);
    }
  };

  const handleInsertAtIndex = async () => {
    if (typeof nodeValue === 'number' && typeof indexValue === 'number') {
      try {
        await insertAtIndex(nodeValue, indexValue);
        await updateListData();
      } catch (error) {
        console.error('Error al insertar en el índice:', error);
      }
    }
    setNodeValue('');
    setIndexValue('');
  };

  const handleDeleteAtIndex = async () => {
    if (typeof indexValue === 'number') {
      try {
        await deleteAtIndex(indexValue);
        await updateListData();
      } catch (error) {
        console.error('Error al eliminar del índice:', error);
      }
    }
    setIndexValue('');
  };

  useEffect(() => {
    updateListData();
  }, [updateListData]);

  return (
    <div className={styles.Container}>
      <div className={styles.Header}>
        Doubly Circular Linked List Component
        <div className={styles.LengthBadge}>Length: {listLength}</div>
      </div>
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
        <div className={styles.InputContainer}>
          <label>Index:</label>
          <input
            type="number"
            value={indexValue}
            onChange={(e) => setIndexValue(Number(e.target.value))}
            placeholder="Enter index"
          />
        </div>
        <div className={styles.Buttons}>
          <button className={styles.Button} onClick={handleInsertHead}>
            Insert Head
          </button>
          <button className={styles.Button} onClick={handleDeleteHead}>
            Delete Head
          </button>
          <button className={styles.Button} onClick={handleInsertEnd}>
            Insert End
          </button>
          <button className={styles.Button} onClick={handleDeleteEnd}>
            Delete End
          </button>
          <button className={styles.Button} onClick={handleInsertAtIndex}>
            Insert at Index
          </button>
          <button className={styles.Button} onClick={handleDeleteAtIndex}>
            Delete at Index
          </button>
        </div>
      </div>

      <div className={styles.ContentContainer}>
        <div className={styles.GraphContainer}>
          <GraphvizComponent input={dclInput} />
        </div>
      </div>
    </div>
  );
};

export default DoublyCircularList;
