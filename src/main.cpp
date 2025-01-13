#include <iostream>

#include "../lib/httplib.h"
#include "linkedListEndpoints.cpp"

using namespace httplib;
using namespace std;

int main() {
  httplib::Server svr;

  LinkedListServer llServer;

  svr.Post("/linkedList/insertHead",
           [&llServer](const Request& req, Response& res) {
             llServer.handleInsertHead(req, res);
           });

  svr.Delete("/linkedList/deleteHead",
             [&llServer](const Request& req, Response& res) {
               llServer.handleDeleteHead(req, res);
             });

  svr.Post("/linkedList/insertEnd",
           [&llServer](const Request& req, Response& res) {
             llServer.handleInsertEnd(req, res);
           });

  svr.Delete("/linkedList/deleteEnd",
             [&llServer](const Request& req, Response& res) {
               llServer.handleDeleteEnd(req, res);
             });

    std::cout << "Servidor corriendo en http://localhost:8080" << std::endl;
  svr.listen("0.0.0.0", 8080);

  return 0;
}
