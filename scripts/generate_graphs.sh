#!/bin/bash

# Directorio donde están los archivos .dot
GRAPHVIZ_DIR=../utils/graphviz

# Verificar si Graphviz está instalado
if ! command -v dot &> /dev/null
then
    echo "Graphviz no está instalado. Instálalo para generar los gráficos."
    exit 1
fi

# Generar los gráficos para los archivos .dot
for dot_file in $GRAPHVIZ_DIR/*.dot; do
  # Generar el archivo PNG correspondiente
  dot -Tpng "$dot_file" -o "${dot_file%.dot}.png"
  echo "Gráfico generado: ${dot_file%.dot}.png"
done
