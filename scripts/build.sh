#!/bin/bash

# Crear directorios si no existen
mkdir -p ../build
mkdir -p ../bin

# Ejecutar el Makefile
cd ..

make clean

make

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
  ./bin/program
else
  echo "Error en la compilación."
fi
