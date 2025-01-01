#include <iostream>

#include "../lib/MyClass.h"

using namespace std;

struct Objeto {
  int numeros;
};

MyClass::MyClass() {}

void MyClass::hola() {
  Objeto obj;
  obj.numeros = 12;
  cout << "Hola mundo" << endl;
  cout << obj.numeros << endl;
}