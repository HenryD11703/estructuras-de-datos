#include <iostream>
#include <sstream>

#include "../include/sparceMatrix.h"

using namespace std;

sparseMatrix::sparseMatrix() : head(new Nodo("XXXXX", 0, 0)) {}