#include <iostream>
#include <nlohmann/json.hpp>

#include "../include/doublyLinkedList.h"
#include "../lib/httplib.h"

using namespace nlohmann;
using namespace httplib;
using namespace std;

class DoublyLinkedListServer {
 private:
  doublyLinkedList dll;

 public:
  void handleInsertHead(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      cout << "Valor Insertado en la cabeza: " << value << endl;
      dll.insertAtHead(value);
      json response = {{"status", "success"},
                       {"message", "Valor insertado en la cabeza"},
                       {"value", value}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleDeleteHead(const Request& req, Response& res) {
    try {
      dll.deleteHead();
      json response = {{"status", "success"},
                       {"message", "Valor eliminado de la cabeza"}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error al eliminar de la cabeza"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleInsertEnd(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      cout << "Valor Insertado al final: " << value << endl;
      dll.insertAtEnd(value);
      json response = {{"status", "success"},
                       {"message", "Valor insertado al final"},
                       {"value", value}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleDeleteEnd(const Request& req, Response& res) {
    try {
      dll.deleteEnd();
      json response = {{"status", "success"},
                       {"message", "Valor eliminado del final"}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error al eliminar del final"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleInsertAtIndex(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      int index = body.at("index");
      cout << "Insertando valor " << value << " en índice " << index << endl;
      dll.insertAtIndex(value, index);
      json response = {{"status", "success"},
                       {"message", "Valor insertado en el índice especificado"},
                       {"value", value},
                       {"index", index}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
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
      cout << "Eliminando valor en índice: " << index << endl;
      dll.deleteAtIndex(index);
      json response = {{"status", "success"},
                       {"message", "Valor eliminado del índice especificado"},
                       {"index", index}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
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
      cout << "Buscando valor: " << value << endl;
      int found = dll.search(value);
      json response = {
          {"status", "success"},
          {"message", found != -1 ? "Valor encontrado" : "Valor no encontrado"},
          {"value", value},
          {"position", found}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
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
      int index = body.at("index");
      int value = dll.get(index);
      json response = {
          {"status", "success"},
          {"message", value != -1 ? "Posición válida" : "Posición inválida"},
          {"value", value},
          {"position", index}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void updateGraph(const Request& req, Response& res) {
    try {
      string dot = dll.generateGraphviz();
      json response = {{"status", "success"},
                       {"message", "Updated graph successfully"},
                       {"dot", dot}};
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error al generar el grafo"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }
};