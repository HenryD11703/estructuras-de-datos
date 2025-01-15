#include <iostream>
#include <nlohmann/json.hpp>

#include "../include/doublyCircularList.h"
#include "../lib/httplib.h"

using namespace nlohmann;
using namespace std;
using namespace httplib;

class DoublyCircularListServer {
 private:
  doublyCircularList dcl;

 public:
  void handleInsertHead(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);  // Parsear JSON
      int value = body.at("value");       // Obtener valor como entero
      dcl.insertAtHead(value);            // Insertar en la lista
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
    dcl.deleteAtHead();
    json response = {{"status", "success"},
                     {"message", "Valor eliminado de la cabeza"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleInsertTail(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);  // Parsear JSON
      int value = body.at("value");       // Obtener valor como entero
      cout << "Valor Insertado al final: " << value << endl;
      dcl.insertAtTail(value);
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

  void handleDeleteTail(const Request& req, Response& res) {
    dcl.deleteAtTail();
    json response = {{"status", "success"},
                     {"message", "Valor eliminado del final"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleInsertAtIndex(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      int value = body.at("value");
      int index = body.at("index");
      cout << "Valor Insertado: " << value << " en índice: " << index << endl;
      dcl.insertAtIndex(index, value);
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
      dcl.deleteAtIndex(index);
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
      int found = dcl.search(value);
      json response = {{"status", "success"},
                       {"message", "Búsqueda completada"},
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
    json response = {{"status", "success"},
                     {"message", "Lista obtenida correctamente"},
                     {"length", dcl.getLength()}};
    res.set_content(response.dump(), "application/json");
  }

  void updateGraph(const Request& req, Response& res) {
    dcl.generateGraphviz();
    json response = {{"status", "success"},
                     {"message", "Graphviz generado correctamente"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleGetLength(const Request& req, Response& res) {
    json response = {{"status", "success"},
                     {"message", "Longitud de la lista obtenida correctamente"},
                     {"length", dcl.getLength()}};
    res.set_content(response.dump(), "application/json");
  }
};
