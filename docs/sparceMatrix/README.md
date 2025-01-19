# Sparce Matrix

A sparse matrix is a matrix in which most of the elements are zero. By contrast, if most of the elements are nonzero, then the matrix is considered dense. There is no strict definition how sparse a matrix must be to be considered sparse but a common criterion is that the number of non-zero elements is roughly the number of rows or the number of columns or less.

Sparse matrices are used in numerical analysis, data mining, and other fields where large datasets are represented. In these situations, memory can be an issue, and a typical use case is to store only non-zero elements.

There are several ways to store sparse matrices in memory. The most common is the coordinate list (COO) format, which stores the row and column indices of each non-zero element. Another common format is the compressed sparse row (CSR) format, which stores the row indices, column indices, and values of the non-zero elements.

In this repository, we provide a simple implementation of a sparse matrix in C++. The matrix is stored in a CSR format, and we provide functions to read and write the matrix from a json file.

## Usage

I implemented a matrix in a mostly visual way, I used a grid in the frontend to represent the matrix, so basically the user can add colors in a position and that is stored in the matrix.
this matrix then can create a json file representing the matrix.

### Operations

- Add a color to a position
- Remove a color from a position
- Save the matrix to a json file
- Load the matrix from a json file

### Add a color to a position

To add a color to a position, you can click on the grid and select a color from the color picker. Then click on the position you want to add the color to.

This calls this function:

```cpp
int sparseMatrix::insertColor(string color, int colIndex, int rowIndex) {
  if (rowIndex < 0 || colIndex < 0)
    return 0;

  HeaderNode* headerX = insertHeader(rowIndex, true);
  HeaderNode* headerY = insertHeader(colIndex, false);

  Nodo* nuevo = new Nodo(color, rowIndex, colIndex);

  if (headerX->dato == nullptr || headerX->dato->columna > colIndex) {
    // si el nodo a insertar es el primero en esta fila, o si esta en la primera
    // posicion
    nuevo->derecha = headerX->dato;
    headerX->dato = nuevo;
  } else {
    Nodo* temp = headerX->dato;
    headerX->dato = nuevo;
    while (temp->derecha != nullptr && temp->derecha->columna < colIndex) {
      temp = temp->derecha;
    }
    // si ya existe en esta posicion
    if (temp->derecha != nullptr && temp->derecha->columna == colIndex) {
      temp->derecha->color = color;
      delete nuevo;
      return 1;
    }
    nuevo->derecha = temp->derecha;
    temp->derecha = nuevo;
    if (nuevo->derecha != nullptr) {
      nuevo->derecha->izquierda = nuevo;
    }
    nuevo->izquierda = temp;
  }

  if (headerY->dato == nullptr || headerY->dato->fila > rowIndex) {
    nuevo->abajo = headerY->dato;
    headerY->dato = nuevo;
  } else {
    Nodo* temp = headerY->dato;
    headerY->dato = nuevo;
    while (temp->abajo != nullptr && temp->abajo->fila < rowIndex) {
      temp = temp->abajo;
    }
    if (temp->abajo != nullptr && temp->abajo->fila == rowIndex) {
      temp->abajo->color = color;
      delete nuevo;
      return 1;
    }
    nuevo->abajo = temp->abajo;
    temp->abajo = nuevo;
    if (nuevo->abajo != nullptr) {
      nuevo->abajo->arriba = nuevo;
    }
    nuevo->arriba = temp;
  }

  cout << "Color: " << color << " en la posicion: " << colIndex << ", "
       << rowIndex << endl;

  jsonFile["matrix"].push_back(
      {{"color", color}, {"column", colIndex}, {"row", rowIndex}});

  return 1;
}
```

As you can see, this function inserts a new node in the matrix, and then adds the color to the json file.

Step by step explanation:

1. Check if the position is valid
2. Insert the header if it doesn't exist
3. Insert the node in the row
4. Insert the node in the column
5. Add the color to the json file

### Read the matrix from a json file

To read the matrix from a json file, you can click on the "Import" button and select the json file you want to import.

This calls this function:

```cpp
void sparseMatrix::insertJson(json text) {
  if (text.is_array()) {
    for (const auto& element : text) {
      string color = element["color"];
      int column = element["column"];
      int row = element["row"];

      // Insertar cada elemento en la matriz
      insertColor(color, column, row);
    }
  } else {
    cout << "Error: Los datos enviados no son un array" << endl;
  }
}
```

As you can see, this function reads the json file and inserts each element in the matrix.

Step by step explanation:

1. Check if the json file is an array
2. Iterate over each element in the array
3. Get the color, column, and row from the element
4. Insert the element in the matrix

## How is this represented on the frontend?

The matrix is represented as a grid, where each cell can have a color. The user can click on a cell to add a color, and click again to remove the color. Its pretty much like a paint program. but instead of painting, you are adding colors to a matrix.

I think this is a good and fun way to represent a matrix, and it's also a good way to learn how to work with matrices.

![Frontend](image.png)

this is the matrix created in the frontend, as you can see, the user can add colors to the matrix and then save it to a json file.

The json file for this image is this

- [JSON of Pokeball](pokeball.json)

Which you can see has this structure

```json
{
    "matrix": [
        {
            "color": "#191f21",
            "column": 5,
            "row": 1
        },
        {
            "color": "#191f21",
            "column": 6,
            "row": 1
        },
        {
            "color": "#191f21",
            "column": 7,
            "row": 1
        }
        // ... more elements
    ]
}
```
