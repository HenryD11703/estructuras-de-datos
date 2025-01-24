// scripts/avlTreeService.ts
import { API_BASE_URL } from './config';

export const fetchTraversals = async () => {
  try {
    const [preorderRes, inorderRes, postorderRes] = await Promise.all([
      fetch(`${API_BASE_URL}/avlTree/Preorder`),
      fetch(`${API_BASE_URL}/avlTree/Inorder`),
      fetch(`${API_BASE_URL}/avlTree/Postorder`),
    ]);

    const [preorderData, inorderData, postorderData] = await Promise.all([
      preorderRes.json(),
      inorderRes.json(),
      postorderRes.json(),
    ]);

    return {
      preorderAVL: preorderData.preorden || '',
      inorder: inorderData.inorder || '',
      postorder: postorderData.postorder || '',
    };
  } catch (error) {
    console.error('Error al obtener los recorridos:', error);
    throw error;
  }
};

export const fetchGraphviz = async () => {
  try {
    const response = await fetch(`${API_BASE_URL}/avlTree/getGraphviz`);
    const data = await response.json();
    if (data.status === 'success') {
      return data.graph;
    } else {
      console.error('Error al obtener Graphviz:', data.message);
      throw new Error(data.message);
    }
  } catch (error) {
    console.error('Error en la solicitud:', error);
    throw error;
  }
};

export const insertNode = async (value: number) => {
  try {
    await fetch(`${API_BASE_URL}/avlTree/insert`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ value }),
    });
  } catch (error) {
    console.error('Error al insertar el nodo:', error);
    throw error;
  }
};

export const deleteNode = async (value: number) => {
  try {
    await fetch(`${API_BASE_URL}/avlTree/delete`, {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ value }),
    });
  } catch (error) {
    console.error('Error al eliminar el nodo:', error);
    throw error;
  }
};
