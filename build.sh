#!/bin/bash

# Crear directorios si no existen
mkdir -p build
mkdir -p bin

# Cambiar a la raíz del proyecto, donde está el Makefile
cd /app

# Ejecutar el Makefile
make clean
make
