import { API_BASE_URL } from './config';

export const fetchGraphviz = async () => {
  try {
    const response = await fetch(
      `${API_BASE_URL}/doublyLinkedList/updateGraph`
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

export const insertHead = async (value: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyLinkedList/insertHead`, {
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
    await fetch(`${API_BASE_URL}/doublyLinkedList/deleteHead`, {
      method: 'DELETE',
    });
  } catch (error) {
    console.error('Error al eliminar la cabeza:', error);
    throw error;
  }
};

export const insertEnd = async (value: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyLinkedList/insertEnd`, {
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
    await fetch(`${API_BASE_URL}/doublyLinkedList/deleteEnd`, {
      method: 'DELETE',
    });
  } catch (error) {
    console.error('Error al eliminar del final:', error);
    throw error;
  }
};

export const insertAtIndex = async (value: number, index: number) => {
  try {
    await fetch(`${API_BASE_URL}/doublyLinkedList/insertAtIndex`, {
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
    await fetch(`${API_BASE_URL}/doublyLinkedList/deleteAtIndex`, {
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
