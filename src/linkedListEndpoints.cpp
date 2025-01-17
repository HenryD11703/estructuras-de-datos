#include <iostream>

#include "../include/linkedList.h"
#include "../lib/httplib.h"
#include "../lib/json.hpp"

using namespace nlohmann;
using namespace httplib;
using namespace std;

class LinkedListServer {
 private:
  linkedList ll;

 public:
  void handleInsertHead(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      ll.insertAtHead(value);
      json response = {{"status", "success"},
                       {"message", "Valor insertado en Head correctamente"},
                       {"value", value}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleDeleteHead(const Request& req, Response& res) {
    ll.deleteHead();
    json response = {{"status", "success"},
                     {"message", "Valor eliminado de la cabeza"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleInsertEnd(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      ll.insertAtEnd(value);
      json response = {{"status", "success"},
                       {"message", "Valor insertado al final"},
                       {"value", value}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleDeleteEnd(const Request& req, Response& res) {
    ll.deleteEnd();
    json response = {{"status", "success"},
                     {"message", "Valor eliminado del final"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleInsertAtIndex(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int index = body.at("index");
      int value = body.at("value");
      ll.insertAtIndex(value, index);
      json response = {{"status", "success"},
                       {"message", "Valor insertado en el índice especificado"},
                       {"value", value},
                       {"index", index}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleDeleteAtIndex(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int index = body.at("index");
      ll.deleteAtIndex(index);
      json response = {{"status", "success"},
                       {"message", index ? "Indice eliminado correctamente"
                                         : "No se encontro el indice"},
                       {"index", index}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleSearch(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      int found = ll.search(value);
      json response = {
          {"status", "success"},
          {"message", found != -1 ? "Valor encontrado" : "Valor no encontrado"},
          {"value", value},
          {"position", found}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleGet(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      json response = {
          {"status", "succes"},
          {"message", value != -1 ? "Posicion invalida" : "Posicion correcta"},
          {"value", value}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void updateGraph(const Request& req, Response& res) {
    string dot = ll.generateGraphviz();
    json response = {{"status", "success"},
                     {"message", "Updated graph succesfully"},
                     {"dot", dot}};
    res.set_content(response.dump(), "application/json");
  }
};