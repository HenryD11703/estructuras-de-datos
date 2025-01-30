#include "../include/BTree.h"

#include <iostream>
#include <sstream>
using namespace std;

BTree::Nodo::~Nodo() {
  for (int i = 0; i < num_claves; ++i) {
    if (!es_hoja) delete hijos[i];
  }
  if (!es_hoja) delete hijos[num_claves];
}

BTree::~BTree() {
  if (raiz) delete raiz;
}

BTree::Nodo::Nodo(int m, bool hoja) : M_nodo(m), es_hoja(hoja), num_claves(0) {
  claves.resize(M_nodo - 1);
  hijos.resize(M_nodo, nullptr);
}

void BTree::Nodo::dividirHijo(int indice, Nodo* hijo) {
  int split_idx = (hijo->M_nodo - 1) / 2;
  Nodo* nuevo = new Nodo(hijo->M_nodo, hijo->es_hoja);
  nuevo->num_claves = hijo->num_claves - split_idx - 1;

  for (int i = 0; i < nuevo->num_claves; ++i) {
    nuevo->claves[i] = hijo->claves[split_idx + 1 + i];
  }

  if (!hijo->es_hoja) {
    for (int i = 0; i <= nuevo->num_claves; ++i) {
      nuevo->hijos[i] = hijo->hijos[split_idx + 1 + i];
    }
  }

  hijo->num_claves = split_idx;

  for (int i = num_claves; i > indice; --i) {
    hijos[i + 1] = hijos[i];
  }
  hijos[indice + 1] = nuevo;

  for (int i = num_claves - 1; i >= indice; --i) {
    claves[i + 1] = claves[i];
  }
  claves[indice] = hijo->claves[split_idx];
  num_claves++;
}

void BTree::Nodo::insertarNoLleno(int clave) {
  int i = num_claves - 1;

  if (es_hoja) {
    while (i >= 0 && claves[i] > clave) {
      claves[i + 1] = claves[i];
      i--;
    }
    claves[i + 1] = clave;
    num_claves++;
  } else {
    while (i >= 0 && claves[i] > clave) i--;
    i++;

    if (hijos[i]->num_claves == M_nodo - 1) {
      dividirHijo(i, hijos[i]);
      if (claves[i] < clave) i++;
    }
    hijos[i]->insertarNoLleno(clave);
  }
}

void BTree::Nodo::recorrer() {
  for (int i = 0; i < num_claves; ++i) {
    if (!es_hoja) hijos[i]->recorrer();
    std::cout << claves[i] << " ";
  }
  if (!es_hoja) hijos[num_claves]->recorrer();
}

BTree::BTree(int max_claves) : raiz(nullptr) { M = max_claves + 1; }

void BTree::insertar(int clave) {
  if (!raiz) {
    raiz = new Nodo(M, true);
    raiz->claves[0] = clave;
    raiz->num_claves = 1;
  } else {
    if (raiz->num_claves == M - 1) {
      // Split raíz
      Nodo* nueva_raiz = new Nodo(M, false);
      nueva_raiz->hijos[0] = raiz;
      nueva_raiz->dividirHijo(0, raiz);

      int i = 0;
      if (nueva_raiz->claves[0] < clave) i++;
      nueva_raiz->hijos[i]->insertarNoLleno(clave);

      raiz = nueva_raiz;
    } else {
      raiz->insertarNoLleno(clave);
    }
  }
}

void BTree::recorrer() {
  if (raiz) raiz->recorrer();
}

string BTree::Nodo::generateGraphviz() {
  stringstream ss;
  ss << "node" << this << " [shape=record, style=\"rounded,filled\", "
     << "fillcolor=\"#E8F4F9\", color=\"#2980B9\", penwidth=2.0, "
     << "label=\"";

  for (int i = 0; i < num_claves; ++i) {
    ss << "<f" << i << "> |{<v" << i << "> " << claves[i] << "}|";
  }
  ss << "<f" << num_claves << ">\"];\n";
  for (int i = 0; i <= num_claves; ++i) {
    if (hijos[i]) {
      ss << hijos[i]->generateGraphviz();

      ss << "node" << this << ":f" << i << " -> node" << hijos[i]
         << " [color=\"#3498DB\", penwidth=1.5, "
         << "arrowsize=0.8, arrowhead=vee];\n";
    }
  }

  return ss.str();
}

string BTree::generateGraphviz() {
  stringstream ss;

  ss << "digraph G {\n"
     << "  bgcolor=\"white\"\n"
     << "  node [fontname=\"Arial\", fontsize=14]\n"
     << "  edge [fontname=\"Arial\", fontsize=12]\n"
     << "  rankdir=TB\n"
     << "  splines=curved\n";

  if (raiz) {
    ss << raiz->generateGraphviz();
  }

  ss << "}\n";
  return ss.str();
}