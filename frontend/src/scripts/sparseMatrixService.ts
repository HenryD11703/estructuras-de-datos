import { API_BASE_URL } from './config';

export const fetchInitialData = async () => {
  try {
    const response = await fetch(`${API_BASE_URL}/sparseMatrix/getInitialData`);
    const data = await response.json();
    if (data.status === 'success' && data.matrix) {
      return data.matrix;
    } else {
      console.error('Error al cargar datos iniciales:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const insertColor = async (row: number, col: number, color: string) => {
  try {
    const response = await fetch(`${API_BASE_URL}/sparseMatrix/insert`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        color,
        column: col + 1,
        row: row + 1,
      }),
    });

    const data = await response.json();
    if (data.status === 'success') {
      return data;
    } else {
      console.error('Error al insertar color:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const deleteColor = async (row: number, col: number) => {
  try {
    const response = await fetch(`${API_BASE_URL}/sparseMatrix/delete`, {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        column: col,
        row: row,
      }),
    });

    const data = await response.json();
    if (data.status === 'success') {
      return data;
    } else {
      console.error('Error al eliminar color:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const cleanMatrix = async () => {
  try {
    const response = await fetch(`${API_BASE_URL}/sparseMatrix/clean`, {
      method: 'GET',
    });

    const data = await response.json();
    if (data.status === 'success') {
      return data;
    } else {
      console.error('Error al limpiar la matriz:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const exportJSON = async () => {
  try {
    const response = await fetch(`${API_BASE_URL}/sparseMatrix/getJSON`);
    const data = await response.json();
    if (data.status === 'success') {
      return data;
    } else {
      console.error('Error al exportar JSON:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const importJSON = async (file: File) => {
  try {
    const reader = new FileReader();
    return new Promise((resolve, reject) => {
      reader.onload = async (e) => {
        const content = e.target?.result as string;
        const jsonData = JSON.parse(content);

        const response = await fetch(`${API_BASE_URL}/sparseMatrix/loadJSON`, {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify({ file: jsonData.matrix }),
        });

        const data = await response.json();
        if (data.status === 'success') {
          resolve(data);
        } else {
          console.error('Error al importar JSON:', data.message);
          reject(new Error(data.message));
        }
      };
      reader.readAsText(file);
    });
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};
