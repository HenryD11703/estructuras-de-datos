#include <iostream>
#include <nlohmann/json.hpp>

#include "../include/avlTree.h"
#include "../lib/httplib.h"

using namespace std;
using namespace httplib;
using namespace nlohmann;

class AVLTreeServer {
 private:
  avlTree avl;

 public:
  void handleInsert(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      avl.insert(value);
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
      avl.deleteNode(value);
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

  void handleGenerateGraphviz(const Request& req, Response& res) {
    try {
      string graph = avl.generateGraphviz();
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
      string preorden = avl.preorder();
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
      string inorder = avl.inorder();
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
      string postorder = avl.postorder();
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