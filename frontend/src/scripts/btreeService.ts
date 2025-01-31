import { API_BASE_URL } from "./config";

export const insertNode = async (value: number) => {
    try {
        await fetch(`${API_BASE_URL}/bTree/insert`, {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({ value }),
        });
    } catch (error) {
        console.error("Error al insertar el nodo:", error);
        throw error;
    }
    }

export const fetchGraphviz = async () => {
    try {
        const response = await fetch(`${API_BASE_URL}/bTree/getGraphviz`);
        const data = await response.json();
        if (data.status === "success") {
        return data.graph;
        } else {
        console.error("Error al obtener Graphviz:", data.message);
        throw new Error(data.message);
        }
    } catch (error) {
        console.error("Error en la solicitud:", error);
        throw error;
    }
}