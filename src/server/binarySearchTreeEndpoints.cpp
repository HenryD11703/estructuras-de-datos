#include <iostream>

#include "../include/binarySearchTree.h"
#include "../lib/httplib.h"
#include "../lib/json.hpp"

using namespace httplib;
using namespace nlohmann;
using namespace std;

class BinarySearchTreeServer {
 private:
  binarySearchTree bst;

 public:
  void handleInsert(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      bst.insert(value);
      json response = {{"status", "success"},
                       {"message", "valor insertado en bst"},
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
      json response = {{"status", "success"},
                       {"message", "valor eliminado en bst"},
                       {"valor", value}};
      res.set_content(response.dump(), "application/json");
      bst.deleteNode(value);
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
      string graph = bst.generateGraphviz();
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

  void handlePreorder(const Request& req, Response& res) {
    try {
      string preorden = bst.preorder();
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
      string inorder = bst.inorder();
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
      string postorder = bst.postorder();
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