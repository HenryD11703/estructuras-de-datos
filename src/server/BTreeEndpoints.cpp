#include <iostream>

#include "../include/BTree.h"
#include "../lib/httplib.h"
#include "../lib/json.hpp"

using namespace std;
using namespace httplib;
using namespace nlohmann;

class BTreeServer {
 private:
  int max_claves;
  BTree arbol;

 public:
  BTreeServer() : max_claves(5), arbol(max_claves) {}

  void handleInsert(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      arbol.insertar(value);
      json response = {{"status", "success"},
                       {"message", "valor ingresado correctamente"},
                       {"valor", value}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleGenerateGraphviz(const Request& req, Response& res) {
    try {
      string graph = arbol.generateGraphviz();
      json response = {{"status", "success"},
                       {"message", "Graṕhviz generado correctamente"},
                       {"graph", graph}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }
};
