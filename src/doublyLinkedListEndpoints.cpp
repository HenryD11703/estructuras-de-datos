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
    string value = req.get_param_value("value");
    cout << "Valor Insertado" << endl;
    dll.insertAtHead(stoi(value));
    json response = {{"status", "success"},
                     {"message", "Valor insertado en la cabeza"},
                     {"value", value}};
    res.set_content(response.dump(), "application/json");
  }

  void handleDeleteHead(const Request& req, Response& res) {
    dll.deleteHead();
    json response = {{"status", "success"},
                     {"message", "Valor eliminado de la cabeza"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleInsertEnd(const Request& req, Response& res) {
    string value = req.get_param_value("value");
    dll.insertAtEnd(stoi(value));
    json response = {{"status", "success"},
                     {"message", "Valor insertado al final"},
                     {"value", value}};
    res.set_content(response.dump(), "application/json");
  }

  void handleDeleteEnd(const Request& req, Response& res) {
    dll.deleteEnd();
    json response = {{"status", "success"},
                     {"message", "Valor eliminado del final"}};
    res.set_content(response.dump(), "application/json");
  }

  void handleInsertAtIndex(const Request& req, Response& res) {
    string value = req.get_param_value("value");
    string index = req.get_header_value("index");
    dll.insertAtIndex(stoi(value), stoi(index));
    json response = {{"status", "success"},
                     {"message", "Valor insertado en el índice especificado"},
                     {"value", value},
                     {"index", index}};
    res.set_content(response.dump(), "application/json");
  }

  void handleDeleteAtIndex(const Request& req, Response& res) {
    string index = req.get_header_value("index");
    dll.deleteAtIndex(stoi(index));
    json response = {{"status", "success"},
                     {"message", "Valor eliminado del índice especificado"},
                     {"index", index}};
    res.set_content(response.dump(), "application/json");
  }

  void handleSearch(const Request& req, Response& res) {
    string value = req.get_header_value("value");
    int found = dll.search(stoi(value));
    json response = {
        {"status", "success"},
        {"message", found != -1 ? "Valor encontrado" : "Valor no encontrado"},
        {"value", value},
        {"position", found}};
    res.set_content(response.dump(), "application/json");
  }

  void handleGet(const Request& req, Response& res) {
    string index = req.get_header_value("index");
    int value = dll.get(stoi(index));
    json response = {
        {"status", "succes"},
        {"message", value != -1 ? "Posicion invalida" : "Posicion correcta"},
        {"value", value},
        {"position", index}};
    res.set_content(response.dump(), "application/json");
  }

  void updateGraph(const Request& req, Response& res) {
    cout << "Graphviz" << endl;
    dll.generateGraphviz();
    json response = {{"status", "success"},
                     {"message", "Updated graph succesfully"}};
    res.set_content(response.dump(), "application/json");
  }
};