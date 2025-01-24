import { API_BASE_URL } from './config';

export const fetchGraphviz = async () => {
  try {
    const response = await fetch(
      `${API_BASE_URL}/doublyCircularList/updateGraph`
    );
    const data = await response.json();
    if (data.status === 'success') {
      return data.dot;
    } else {
      console.error('Error al obtener Graphviz:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const fetchLength = async () => {
  try {
    const response = await fetch(`${API_BASE_URL}/doublyCircularList/lenght`);
    const data = await response.json();
    if (data.status === 'success') {
      return data.length;
    } else {
      console.error('Error al obtener la longitud:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error al obtener la longitud:', error);
    throw error;
  }
};

export const insertHead = async (value: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyCircularList/insertHead`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ value }),
    });
  } catch (error) {
    console.error('Error al insertar en la cabeza:', error);
    throw error;
  }
};

export const deleteHead = async () => {
  try {
    await fetch(`${API_BASE_URL}/doublyCircularList/deleteHead`, {
      method: 'DELETE',
    });
  } catch (error) {
    console.error('Error al eliminar la cabeza:', error);
    throw error;
  }
};

export const insertEnd = async (value: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyCircularList/insertEnd`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ value }),
    });
  } catch (error) {
    console.error('Error al insertar al final:', error);
    throw error;
  }
};

export const deleteEnd = async () => {
  try {
    await fetch(`${API_BASE_URL}/doublyCircularList/deleteEnd`, {
      method: 'DELETE',
    });
  } catch (error) {
    console.error('Error al eliminar del final:', error);
    throw error;
  }
};

export const insertAtIndex = async (value: number, index: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyCircularList/insertAtIndex`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ value, index }),
    });
  } catch (error) {
    console.error('Error al insertar en el índice:', error);
    throw error;
  }
};

export const deleteAtIndex = async (index: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyCircularList/deleteAtIndex`, {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ index }),
    });
  } catch (error) {
    console.error('Error al eliminar del índice:', error);
    throw error;
  }
};
