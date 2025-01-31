import GraphvizComponent from '../utils/Graphviz';
import { useState, useEffect, useCallback } from 'react';
import styles from './BTree.module.css';
import { insertNode, fetchGraphviz } from '../scripts/btreeService';

const BTree = () => {
    const [bTreeInput, setBTreeInput] = useState<string>('');
    const [nodeValue, setNodeValue] = useState<number | string>('');

    const updateTreeData = useCallback(async () => {
        try {
            const graphvizData = await fetchGraphviz();
            setBTreeInput(graphvizData);
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

    useEffect(() => {
        updateTreeData();
    }, [updateTreeData]);

    return (
        <div className={styles.Container}>
            <div className={styles.Header}>B Tree Component</div>
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
                </div>
            </div>

            <div className={styles.ContentContainer}>
                <div className={styles.GraphContainer}>
                    <GraphvizComponent input={bTreeInput} />
                </div>
            </div>
        </div>
    );
};

export default BTree;