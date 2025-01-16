import GraphvizComponent from '../utils/Graphviz';
import { useState, useEffect, useCallback } from 'react';
import styles from './DoublyCircularLinkedList.module.css';

const DoublyCircularList = () => {
  const [dclInput, setDclInput] = useState<string>();
  const [nodeValue, setNodeValue] = useState<number | string>('');
  const [indexValue, setIndexValue] = useState<number | string>('');
  const [listLength, setListLength] = useState<number>(0);

  const fetchGraphviz = async () => {
    try {
      const response = await fetch(
        'http://192.168.1.113:8080/doublyCircularList/updateGraph'
      );
      const data = await response.json();
      if (data.status === 'success') {
        setDclInput(data.dot);
      } else {
        console.error('Error al obtener Graphviz:', data.message);
      }
    } catch (error) {
      console.error('Error en la solicitud:', error);
    }
  };

  const fetchLength = async () => {
    try {
      const response = await fetch(
        'http://192.168.1.113:8080/doublyCircularList/lenght'
      );
      const data = await response.json();
      if (data.status === 'success') {
        setListLength(data.length);
      }
    } catch (error) {
      console.error('Error al obtener la longitud:', error);
    }
  };

  const updateListData = useCallback(async () => {
    await Promise.all([fetchGraphviz(), fetchLength()]);
  }, []);

  const handleInsertHead = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await fetch('http://192.168.1.113:8080/doublyCircularList/insertHead', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ value: nodeValue }),
        });
        await updateListData();
      } catch (error) {
        console.error('Error al insertar en la cabeza:', error);
      }
    }
    setNodeValue('');
  };

  const handleDeleteHead = async () => {
    try {
      await fetch('http://192.168.1.113:8080/doublyCircularList/deleteHead', {
        method: 'DELETE',
      });
      await updateListData();
    } catch (error) {
      console.error('Error al eliminar la cabeza:', error);
    }
  };

  const handleInsertEnd = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await fetch('http://192.168.1.113:8080/doublyCircularList/insertEnd', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ value: nodeValue }),
        });
        await updateListData();
      } catch (error) {
        console.error('Error al insertar al final:', error);
      }
    }
    setNodeValue('');
  };

  const handleDeleteEnd = async () => {
    try {
      await fetch('http://192.168.1.113:8080/doublyCircularList/deleteEnd', {
        method: 'DELETE',
      });
      await updateListData();
    } catch (error) {
      console.error('Error al eliminar del final:', error);
    }
  };

  const handleInsertAtIndex = async () => {
    if (typeof nodeValue === 'number' && typeof indexValue === 'number') {
      try {
        await fetch(
          'http://192.168.1.113:8080/doublyCircularList/insertAtIndex',
          {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ value: nodeValue, index: indexValue }),
          }
        );
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
        await fetch(
          'http://192.168.1.113:8080/doublyCircularList/deleteAtIndex',
          {
            method: 'DELETE',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({ index: indexValue }),
          }
        );
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
