# Árbol B (B-Tree)

## Descripción General

Un Árbol B es una estructura de datos de árbol autobalanceado diseñada para mantener datos ordenados y realizar operaciones eficientes de búsqueda, inserción y eliminación.

## Características Principales

- Permite múltiples hijos por nodo
- Mantiene los datos ordenados
- Optimizado para sistemas con acceso a disco
- Garantiza operaciones en tiempo logarítmico

## Propiedades de un Árbol B

### Definición Formal

Un Árbol B de orden `m` cumple las siguientes propiedades:

1. Cada nodo tiene como máximo `m` hijos
2. Cada nodo (excepto la raíz) tiene al menos `⌈m/2⌉` hijos
3. Cada nodo no-hoja con `k` hijos contiene `k-1` claves
4. Todas las hojas aparecen en el mismo nivel

## Operaciones

### Inserción

Pasos para insertar una clave `k`:

1. Comenzar en el nodo raíz
2. Si la raíz está llena, dividirla y promocionar la clave media
3. Descender recursivamente hasta un nodo hoja
4. Si el nodo hoja no está lleno, insertar directamente
5. Si el nodo hoja está lleno:
   - Dividir el nodo
   - Promocionar la clave media al nodo padre
6. Repetir el proceso de división si es necesario

### Eliminación

Pasos para eliminar una clave `k`:

1. Localizar el nodo que contiene la clave
2. Eliminar la clave del nodo
3. Rebalancear el árbol si es necesario:
   - Prestar claves de nodos hermanos
   - Fusionar nodos si no hay suficientes claves
4. Mantener las propiedades del Árbol B durante la eliminación

## Complejidad Computacional

| Operación   | Complejidad Temporal |
|-------------|----------------------|
| Búsqueda    | O(log₍m₎(n))         |
| Inserción   | O(log₍m₎(n))         |
| Eliminación | O(log₍m₎(n))         |

## Aplicaciones

- Sistemas de bases de datos
- Sistemas de archivos
- Índices en motores de búsqueda
- Sistemas de control de versiones
- Enrutadores de red

## Ventajas

- Alto rendimiento en operaciones de disco
- Autobalanceo
- Eficiente manejo de grandes volúmenes de datos
- Búsquedas rápidas

## Referencias

- Cormen, T. H. et al. "Introduction to Algorithms"
- [Documentación de Wikipedia sobre Árboles B](https://es.wikipedia.org/wiki/%C3%81rbol_B)
