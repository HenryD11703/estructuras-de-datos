#include <iostream>
#include <sstream>

#include "../include/redBlackTree.h"
#include "../lib/httplib.h"
#include "../lib/json.hpp"

using namespace std;
using namespace httplib;
using namespace nlohmann;

class RedBlackTreeServer {
 private:
  RedBlackTree rbt;

 public:
  void handleInsert(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      rbt.insert(value);
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
  void handleDelete(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      rbt.deleteNode(value);
      json response = {{"status", "success"},
                       {"message", "valor eliminado correctamente"},
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
  void handleGraphviz(const Request& req, Response& res) {
    try {
      cout << "Generando Graphviz" << endl;
      string graphviz = rbt.generateGraphviz();
      json response = {{"status", "success"},
                       {"message", "Graphviz generado correctamente"},
                       {"graphviz", graphviz}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handlePreorder(const Request& req, Response& res) {
    try {
      string preorden = rbt.preorder();
      json response = {{"status", "success"},
                       {"message", "Obtenido correctamente"},
                       {"preorden", preorden}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleInorder(const Request& req, Response& res) {
    try {
      string inorder = rbt.inorder();
      json response = {{"status", "success"},
                       {"message", "Obtenido correctamente"},
                       {"inorder", inorder}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handlePostorder(const Request& req, Response& res) {
    try {
      string postorder = rbt.postorder();
      json response = {{"status", "success"},
                       {"message", "Obtenido correctamente"},
                       {"postorder", postorder}};
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
