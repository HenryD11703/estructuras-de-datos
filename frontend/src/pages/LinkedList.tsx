import GraphvizComponent from '../utils/Graphviz';
import { useState, useEffect, useCallback } from 'react';
import styles from './LinkedList.module.css';

const LinkedList = () => {
  const [llInput, setLlInput] = useState<string>();
  const [nodeValue, setNodeValue] = useState<number | string>('');
  const [indexValue, setIndexValue] = useState<number | string>('');

  const fetchGraphviz = async () => {
    try {
      const response = await fetch(
        'http://192.168.1.113:8080/linkedList/updateGraph'
      );
      const data = await response.json();
      if (data.status === 'success') {
        setLlInput(data.dot);
      } else {
        console.error('Error al obtener Graphviz:', data.message);
      }
    } catch (error) {
      console.error('Error en la solicitud:', error);
    }
  };

  const updateListData = useCallback(async () => {
    await fetchGraphviz();
  }, []);

  const handleInsertHead = async () => {
    if (typeof nodeValue === 'number') {
      try {
        await fetch('http://192.168.1.113:8080/linkedList/insertHead', {
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
      await fetch('http://192.168.1.113:8080/linkedList/deleteHead', {
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
        await fetch('http://192.168.1.113:8080/linkedList/insertEnd', {
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
      await fetch('http://192.168.1.113:8080/linkedList/deleteEnd', {
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
        await fetch('http://192.168.1.113:8080/linkedList/insertAtIndex', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ value: nodeValue, index: indexValue }),
        });
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
        await fetch('http://192.168.1.113:8080/linkedList/deleteAtIndex', {
          method: 'DELETE',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ index: indexValue }),
        });
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
      <div className={styles.Header}>Linked List Component</div>
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
          <GraphvizComponent input={llInput} />
        </div>
      </div>
    </div>
  );
};

export default LinkedList;
