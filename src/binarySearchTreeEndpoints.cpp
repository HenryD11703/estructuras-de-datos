#include <iostream>
#include <nlohmann/json.hpp>

#include "../include/binarySearchTree.h"
#include "../lib/httplib.h"

using namespace httplib;
using namespace nlohmann;
using namespace std;

class binarySearchTreeServer {
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
      bst.deleteNode(value);
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }
};