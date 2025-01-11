# Árbol de Búsqueda Binaria

Un árbol de búsqueda binaria es un árbol binario en el que cada nodo cumple una propiedad específica de ordenamiento: todos los descendientes izquierdos <= n < todos los descendientes derechos. Esto debe ser verdadero para cada nodo n.

Esta estructura de datos proporciona operaciones eficientes de inserción, eliminación y búsqueda. También se conoce como árbol binario ordenado.

## Propiedades

- El subárbol izquierdo de un nodo contiene solo nodos con claves menores que la clave del nodo.
- El subárbol derecho de un nodo contiene solo nodos con claves mayores que la clave del nodo.
- Los subárboles izquierdo y derecho también deben ser árboles de búsqueda binaria.

Para poder entender el árbol de búsqueda binaria, necesitamos entender los siguientes términos:

- **Raíz**: El nodo superior en un árbol.
- **Padre**: Cualquier nodo excepto el nodo raíz tiene un borde hacia arriba que conecta con un nodo llamado padre.
- **Hijo**: El nodo debajo de un nodo dado conectado por su borde hacia abajo se llama nodo hijo.
- **Hoja**: El nodo que no tiene ningún nodo hijo se llama nodo hoja.
- **Subárbol**: Un subárbol es un árbol que existe dentro de un árbol.

Una de las cosas más importantes que hay que saber cuando se trabaja con árboles de búsqueda binaria es la **recursión**. La recursión es una técnica en la que una función se llama a sí misma como una subrutina. Esto nos permite descomponer problemas complejos en problemas más simples que son más fáciles de resolver.

### Recursión

Cualquier función que se llama a sí misma se llama recursiva. Un método recursivo resuelve un problema llamando a una copia de sí mismo para trabajar en un problema más pequeño. Esto se llama el paso de recursión. El paso de recursión puede resultar en muchas más llamadas recursivas.

La recursión es una técnica útil tomada de las matemáticas. El código recursivo es generalmente más corto y más fácil de escribir que el código iterativo. Generalmente, los bucles se convierten en funciones recursivas cuando se compilan o interpretan.

Una función recursiva realiza una tarea en parte llamándose a sí misma para realizar las subtareas. En algún punto, la función encuentra una subtarea que puede realizar sin llamarse a sí misma. Este caso, donde la función no recurre, se llama el caso base. El anterior, donde la función se llama a sí misma para realizar una subtarea, se conoce como el caso recursivo. Podemos escribir todas las funciones recursivas usando el formato. (Estructuras de Datos y Algoritmos simplificados: Estructuras de Datos y Rompecabezas Algorítmicos, Narasimha Karumanchi)

```cpp
void funcionRecursiva(parametros) {
    if (caso base) {
        // caso base
        return algun valor del caso base;
    } else if (otro caso base) {
        // otro caso base
        return algun otro valor del caso base;
    } else {
        // caso recursivo
        funcionRecursiva(parametros modificados);
    }
}
```

Otra cosa importante a tener en cuenta es el nivel de un nodo. El nivel de un nodo es el número de bordes en el camino desde el nodo raíz hasta ese nodo. El nodo raíz está en el nivel 0.

Y la complejidad temporal de las operaciones del árbol de búsqueda binaria es O(h), donde h es la altura del árbol. La altura del árbol es el número de bordes en el camino más largo desde el nodo raíz hasta un nodo hoja.

## La estructura del nodo

La estructura del nodo es el bloque básico de construcción de un árbol de búsqueda binaria. Contiene los siguientes campos:

- **valor**: Los datos que se almacenarán en el nodo.
- **izquierda**: Un puntero al nodo hijo izquierdo.
- **derecha**: Un puntero al nodo hijo derecho.
- **contador**: El número de veces que el valor está presente en el árbol, esto es útil cuando permitimos duplicados en el árbol.

```cpp
struct Nodo {
    Nodo* izquierda;
    Nodo* derecha;
    int valor;
    int contador;
    Nodo(int val) : izquierda(nullptr), derecha(nullptr), valor(val), contador(1) {}
};
```

## Operaciones

### Inserción

La inserción es el proceso de agregar un nuevo nodo al árbol de búsqueda binaria. El nuevo nodo se agrega según el valor del nodo. Si el valor del nuevo nodo es menor que el valor del nodo actual, se agrega al subárbol izquierdo. Si el valor del nuevo nodo es mayor que el valor del nodo actual, se agrega al subárbol derecho.

Hay múltiples casos a considerar al insertar un nuevo nodo:

1. Si el árbol está vacío, el nuevo nodo se convierte en el nodo raíz.

2. Si el valor ya existe en el árbol, incrementamos el contador del nodo.

3. Si el valor es menor que el nodo actual, insertamos recursivamente el valor en el subárbol izquierdo.

4. Si el valor es mayor que el nodo actual, insertamos recursivamente el valor en el subárbol derecho.

```cpp
void arbolBusquedaBinaria::insertar(int val) { raiz = insertar(raiz, val); }
arbolBusquedaBinaria::Nodo* arbolBusquedaBinaria::insertar(Nodo* nodo, int val) {
    if (nodo == nullptr) {
        return new Nodo(val);
    }
    if (val == nodo->valor) {
        nodo->contador++;
        return nodo;
    }
    if (val < nodo->valor)
        nodo->izquierda = insertar(nodo->izquierda, val);
    else
        nodo->derecha = insertar(nodo->derecha, val);

    return nodo;
}
```

Como puedes ver, comenzamos con la función que se llama desde el programa principal. Esta función llama a la función recursiva que realizará la inserción real. La función recursiva devolverá el nodo que se insertó o el nodo que se le pasó.

Primero comprobamos si el nodo es nulo, si lo es, creamos un nuevo nodo con el valor y lo devolvemos. Si el valor es igual al nodo actual, incrementamos el contador y devolvemos el nodo.

Si el valor es menor que el nodo actual, cambiamos la izquierda del nodo actual al resultado de la llamada recursiva con la izquierda del nodo actual y el valor. Si el valor es mayor que el nodo actual, cambiamos la derecha del nodo actual al resultado de la llamada recursiva con la derecha del nodo actual y el valor.

Esto se puede visualizar en esta imagen:

![Inserción](../insert.png)

### Eliminación

La eliminación es el proceso de eliminar un nodo del árbol de búsqueda binaria. Hay tres casos a considerar al eliminar un nodo:

1. Si el nodo a eliminar es un nodo hoja, simplemente lo eliminamos.

2. Si el nodo a eliminar tiene un solo hijo, eliminamos el nodo y lo reemplazamos con su hijo.

3. Si el nodo a eliminar tiene dos hijos, encontramos el sucesor inorden del nodo. El sucesor inorden es el nodo más pequeño en el subárbol derecho del nodo a eliminar. Copiamos el valor del sucesor inorden al nodo a eliminar y eliminamos el sucesor inorden.

```cpp
void arbolBusquedaBinaria::eliminarNodo(int val) { raiz = eliminarNodo(raiz, val); }
arbolBusquedaBinaria::Nodo* arbolBusquedaBinaria::eliminarNodo(Nodo* nodo, int val) {
    if (nodo == nullptr) {
        return nullptr;
    }
    if (val > nodo->valor) {
        nodo->derecha = eliminarNodo(nodo->derecha, val);
    } else if (val < nodo->valor) {
        nodo->izquierda = eliminarNodo(nodo->izquierda, val);
    }
    if (val == nodo->valor) {
        if (nodo->contador > 1) {
            nodo->contador--;
            return nodo;
        }
        if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
            // es hoja
            delete nodo;
            return nullptr;
        } else if (nodo->izquierda == nullptr || nodo->derecha == nullptr) {
            // tiene un solo hijo
            Nodo* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            delete nodo;
            return temp;
        } else {
            // tiene dos hijos
            Nodo* sucesor = nodo->derecha;
            while (sucesor->izquierda != nullptr) {
                sucesor = sucesor->izquierda;
            }

            nodo->valor = sucesor->valor;
            nodo->contador = sucesor->contador;

            nodo->derecha = eliminarNodo(nodo->derecha, sucesor->valor);
        }
    }
    return nodo;
}
```

Como puedes ver, comprobamos los múltiples casos, si el nodo es nulo, devolvemos nulo. Si el nodo tiene un solo hijo, devolvemos el hijo. Si el nodo es una hoja, lo eliminamos y devolvemos nulo.

Pero si el nodo tiene dos hijos, básicamente encontramos el nodo más pequeño en el subárbol derecho del nodo a eliminar, copiamos su valor al nodo a eliminar y eliminamos el nodo más pequeño en el subárbol derecho del nodo a eliminar.

Como puedes ver, realmente no eliminamos el nodo, solo cambiamos su valor y luego eliminamos el nodo más pequeño en el subárbol derecho del nodo a eliminar.

### Búsqueda

La búsqueda es el proceso de encontrar un nodo con un valor específico en el árbol de búsqueda binaria. Comenzamos en el nodo raíz y comparamos el valor con el valor del nodo actual. Si el valor es menor que el valor del nodo actual, buscamos en el subárbol izquierdo. Si el valor es mayor que el valor del nodo actual, buscamos en el subárbol derecho. Si el valor es igual al valor del nodo actual, devolvemos el nodo.

```cpp
arbolBusquedaBinaria::Nodo* arbolBusquedaBinaria::buscar(int val) { return buscar(raiz, val); }
arbolBusquedaBinaria::Nodo* arbolBusquedaBinaria::buscar(Nodo* nodo, int val) {
    if (nodo == nullptr || nodo->valor == val) {
        return nodo;
    }
    if (val > nodo->valor) {
        return buscar(nodo->derecha, val);
    } else if (val < nodo->valor) {
        return buscar(nodo->izquierda, val);
    }
}
```

Como puedes ver, comenzamos con la función que se llama desde el programa principal. Esta función llama a la función recursiva que realizará la búsqueda real. La función recursiva devolverá el nodo que se encontró o nulo.

Simplemente comprobamos si el nodo es mayor que el valor y continuamos la búsqueda en el subárbol derecho. Si el nodo es menor que el valor, continuamos la búsqueda en el subárbol izquierdo. Si el nodo es igual al valor, devolvemos el nodo, hacemos esto con cada subárbol hasta que encontramos el nodo o llegamos a un nodo nulo.

### Recorrido

El recorrido es el proceso de visitar todos los nodos en el árbol de búsqueda binaria. Hay tres tipos de recorrido:

1. **Inorden**: En este recorrido, primero visitamos el subárbol izquierdo, luego el nodo raíz y finalmente el subárbol derecho.

2. **Preorden**: En este recorrido, primero visitamos el nodo raíz, luego el subárbol izquierdo y finalmente el subárbol derecho.

3. **Postorden**: En este recorrido, primero visitamos el subárbol izquierdo, luego el subárbol derecho y finalmente el nodo raíz.

#### Inorden

```cpp
void arbolBusquedaBinaria::inorden() { inorden(raiz); }
void arbolBusquedaBinaria::inorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    inorden(nodo->izquierda);
    cout << nodo->valor << " ";
    inorden(nodo->derecha);
}
```

#### Preorden

```cpp
void arbolBusquedaBinaria::preorden() { preorden(raiz); }
void arbolBusquedaBinaria::preorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    cout << nodo->valor << " ";
    preorden(nodo->izquierda);
    preorden(nodo->derecha);
}
```

#### Postorden

```cpp
void arbolBusquedaBinaria::postorden() { postorden(raiz); }
void arbolBusquedaBinaria::postorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    postorden(nodo->izquierda);
    postorden(nodo->derecha);
    cout << nodo->valor << " ";
}
```

### Obtener nodo Máximo

```cpp
int arbolBusquedaBinaria::encontrarMax(Nodo* nodo) {
    while (nodo->derecha != nullptr) {
        nodo = nodo->derecha;
    }
    return nodo->valor;
}
```

En este caso, simplemente buscamos el nodo más a la derecha en el árbol, este nodo será el nodo máximo en el árbol.

### Obtener nodo Mínimo

```cpp
int arbolBusquedaBinaria::encontrarMin(Nodo* nodo) {
    while (nodo->izquierda != nullptr) {
        nodo = nodo->izquierda;
    }
    return nodo->valor;
}
```

En este caso, simplemente buscamos el nodo más a la izquierda en el árbol, este nodo será el nodo mínimo en el árbol.

### Generar archivo Graphviz

```cpp
void binarySearchTree::generateGraphviz() const {
  ofstream file;
  file.open("./utils/graphviz/binarySearchTree.dot");
  if (file.is_open()) {
    file << "digraph g {" << endl;
    file << "node [shape=circle, style=filled, fontname=\"Helvetica\"];"
         << endl;
    generateGraphviz(file, root);
    file << "rankdir=TB;" << endl;
    file << "nodesep = 0.1" << endl;
    file << "}" << endl;
  }
  file.close();
}
void binarySearchTree::generateGraphviz(ofstream& file, Nodo* node) const {
  if (node == nullptr) {
    return;
  }
  file << "\"" << node << "\"" << "[label=\"" << node->value << "("
       << node->count << ")" << "\"];" << endl;

  // si el nodo, tiene hijo izquierdo
  if (node->left) {
    file << "\"" << node << "\"" << "->" << "\"" << node->left << "\""
         << "[label=\"L\", color=black]" << endl;
    generateGraphviz(file, node->left);
  }
  if (node->right) {
    file << "\"" << node << "\"" << "->" << "\"" << node->right << "\""
         << "[label=\"R\", color=black]" << endl;
    generateGraphviz(file, node->right);
  }
}
```

Esta función genera un archivo Graphviz que se puede convertir en una imagen visual del árbol de búsqueda binaria. Graphviz es una herramienta de visualización de gráficos de código abierto. Puede encontrar más información sobre Graphviz en [Graphviz](https://graphviz.org/).

Esta funcion hace un recorrido en preorden del árbol y escribe en el archivo dot las conexiones entre los nodos.

## Complejidad Temporal

La complejidad temporal de las operaciones del árbol de búsqueda binaria es O(h), donde h es la altura del árbol. La altura del árbol es el número de bordes en el camino más largo desde el nodo raíz hasta un nodo hoja.

## Problemas comunes

- **Desbalanceo del árbol**: Si insertamos los elementos en orden, el árbol se convierte en una lista enlazada. Esto aumenta la altura del árbol y disminuye la eficiencia de las operaciones.

Por eso existen árboles de búsqueda binaria balanceados como el árbol AVL y el árbol rojo-negro.

## Referencias

- [Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
- [GeeksforGeeks](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
- [Data Structures and Algorithms made easy: Data Structures and Algorithmic Puzzles, Narasimha Karumanchi](https://www.amazon.com/Data-Structures-Algorithms-Made-Easy/dp/1468101277)
