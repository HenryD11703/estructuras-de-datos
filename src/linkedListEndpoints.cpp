#include <iostream>

#include "../include/linkedList.h"
#include "../lib/httplib.h"

using namespace httplib;
using namespace std;

class LinkedListServer {
 private:
  linkedList ll;

 public:
  void handleInsertHead(const Request& req, Response& res) {
    string value = req.get_param_value("value");
    ll.insertAtHead(stoi(value));
    res.set_content("Valor insertado: " + value + "\n", "text/plain");
  }

  void handleDeleteHead(const Request& req, Response& res) {
    ll.deleteHead();
    res.set_content("Valor eliminado de la cabeza\n", "text/plain");
  }

  void handleInsertEnd(const Request& req, Response& res) {
    string value = req.get_param_value("value");
    ll.insertAtEnd(stoi(value));
    res.set_content("Valor insertado al final: " + value + "\n", "text/plain");
  }

  void handleDeleteEnd(const Request& req, Response& res) {
    ll.deleteEnd();
    res.set_content("Valor eliminado del final\n", "text/plain");
  }

  void handleInsertAtIndex(const Request& req, Response& res) {
    string value = req.get_param_value("value");
    string index = req.get_header_value("index");
    ll.insertAtIndex(stoi(value), stoi(index));
    res.set_content(
        "Valor insertado en el indice: " + index + ". " + value + "\n",
        "text/plain");
  }

  void handleInsertAtIndex(const Request& req, Response& res) {
    string index = req.get_header_value("index");
    ll.deleteAtIndex(stoi(index));
    res.set_content("Valor eliminado del indice: " + index + "\n",
                    "text/plain");
  }
};
