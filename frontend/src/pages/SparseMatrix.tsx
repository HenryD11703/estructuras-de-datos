import { useState, useEffect } from 'react';
import styles from './SparseMatrix.module.css';
import {
  fetchInitialData,
  insertColor,
  deleteColor,
  cleanMatrix,
  exportJSON,
  importJSON,
} from '../scripts/sparseMatrixService';

const SparseMatrix = () => {
  const [selectedColor, setSelectedColor] = useState('#000000');
  const [matrix, setMatrix] = useState<{ [key: string]: string }>({});

  // Cargar datos iniciales del backend
  useEffect(() => {
    const loadInitialData = async () => {
      try {
        const data = await fetchInitialData();
        const newMatrix: { [key: string]: string } = {};
        data.forEach((item: { row: number; column: number; color: string }) => {
          newMatrix[`${item.row},${item.column}`] = item.color;
        });
        setMatrix(newMatrix);
      } catch (error) {
        console.error('Error al cargar datos iniciales:', error);
      }
    };

    loadInitialData();
  }, []);

  const handleCellClick = async (row: number, col: number) => {
    if (selectedColor !== '#ffffff') {
      try {
        const response = await insertColor(row, col, selectedColor);
        if (response.status === 'success') {
          setMatrix((prevMatrix) => ({
            ...prevMatrix,
            [`${row},${col}`]: selectedColor,
          }));
        } else {
          console.error('Error al insertar color:', response.message);
        }
      } catch (error) {
        console.error('Error en la solicitud:', error);
      }
    } else {
      try {
        const response = await deleteColor(row, col);
        if (response.status === 'success') {
          const newMatrix = { ...matrix };
          delete newMatrix[`${row},${col}`];
          setMatrix(newMatrix);
        } else {
          console.error('Error al eliminar color:', response.message);
        }
      } catch (error) {
        console.error('Error en la solicitud:', error);
      }
    }
  };

  const handleClean = async () => {
    try {
      const response = await cleanMatrix();
      if (response.status === 'success') {
        setMatrix({}); // Limpiar la matriz en el estado local
      } else {
        console.error('Error al limpiar la matriz:', response.message);
      }
    } catch (error) {
      console.error('Error al limpiar la matriz:', error);
    }
  };

  const handleExportJSON = async () => {
    try {
      const data = await exportJSON();
      const { status, message, ...matrixData } = data;
      const blob = new Blob([JSON.stringify(matrixData, null, 2)], {
        type: 'application/json',
      });
      const url = window.URL.createObjectURL(blob);
      const a = document.createElement('a');
      a.href = url;
      a.download = 'sparse-matrix.json';
      a.click();
      window.URL.revokeObjectURL(url);
    } catch (error) {
      console.error('Error al exportar JSON:', error);
    }
  };

  const handleImportJSON = async (
    event: React.ChangeEvent<HTMLInputElement>
  ) => {
    const file = event.target.files?.[0];
    if (!file) return;

    try {
      const reader = new FileReader();
      reader.onload = async (e) => {
        const content = e.target?.result as string;
        const jsonData = JSON.parse(content);

        // Verificar si el JSON tiene la estructura correcta
        if (jsonData.matrix && Array.isArray(jsonData.matrix)) {
          const newMatrix: { [key: string]: string } = {};
          jsonData.matrix.forEach(
            (item: { row: number; column: number; color: string }) => {
              newMatrix[`${item.row},${item.column}`] = item.color;
            }
          );
          setMatrix(newMatrix);
        } else {
          console.error('El archivo JSON no tiene la estructura correcta.');
        }
      };
      reader.readAsText(file);
    } catch (error) {
      console.error('Error al importar JSON:', error);
    }
  };

  // Renderizar la cuadrícula
  const renderGrid = () => {
    const grid = [];
    for (let i = 0; i < 50; i++) {
      const row = [];
      for (let j = 0; j < 50; j++) {
        const cellColor = matrix[`${i},${j}`] || '#ffffff';
        row.push(
          <div
            key={`${i}-${j}`}
            className={styles.Cell}
            style={{ backgroundColor: cellColor }}
            onClick={() => handleCellClick(i, j)}
          />
        );
      }
      grid.push(
        <div key={i} className={styles.Row}>
          {row}
        </div>
      );
    }
    return grid;
  };

  return (
    <div className={styles.Container}>
      <div className={styles.Header}>Sparse Matrix Component</div>
      <div className={styles.Form}>
        <div className={styles.InputContainer}>
          <label>Color:</label>
          <input
            type="color"
            value={selectedColor}
            onChange={(e) => setSelectedColor(e.target.value)}
          />
        </div>
        <div className={styles.Buttons}>
          <button className={styles.Button} onClick={handleClean}>
            Clean Matrix
          </button>
          <button className={styles.Button} onClick={handleExportJSON}>
            Export JSON
          </button>
          <label className={styles.Button}>
            Import JSON
            <input
              type="file"
              accept=".json"
              onChange={handleImportJSON}
              style={{ display: 'none' }}
            />
          </label>
        </div>
      </div>

      <div className={styles.ContentContainer}>
        <div className={styles.MatrixContainer}>
          <div className={styles.Grid}>{renderGrid()}</div>
        </div>
      </div>
    </div>
  );
};

export default SparseMatrix;
