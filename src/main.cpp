#include <iostream>

#include "../lib/httplib.h"
#include "binarySearchTreeEndpoints.cpp"
#include "doublyCircularListEndpoints.cpp"
#include "doublyLinkedListEndpoints.cpp"
#include "linkedListEndpoints.cpp"

using namespace httplib;
using namespace std;

void handleCORS(const Request& req, Response& res) {
  res.set_header("Access-Control-Allow-Origin", "*");
  res.set_header("Access-Control-Allow-Methods",
                 "GET, POST, PUT, DELETE, OPTIONS");
  res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

void linkedListRoutes(Server& svr, LinkedListServer& llServer) {
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

  svr.Post("/linkedList/insertAtIndex",
           [&llServer](const Request& req, Response& res) {
             llServer.handleInsertAtIndex(req, res);
           });

  svr.Delete("/linkedList/deleteAtIndex",
             [&llServer](const Request& req, Response& res) {
               llServer.handleDeleteAtIndex(req, res);
             });

  svr.Get("/linkedList/search", [&llServer](const Request& req, Response& res) {
    llServer.handleSearch(req, res);
  });

  svr.Get("/linkedList/get", [&llServer](const Request& req, Response& res) {
    llServer.handleGet(req, res);
  });

  svr.Get("/linkedList/updateGraph",
          [&llServer](const Request& req, Response& res) {
            llServer.updateGraph(req, res);
          });
}

void doublyLinkedListRoutes(Server& svr, DoublyLinkedListServer& dllServer) {
  svr.Post("/doublyLinkedList/insertHead",
           [&dllServer](const Request& req, Response& res) {
             dllServer.handleInsertHead(req, res);
           });

  svr.Delete("/doublyLinkedList/deleteHead",
             [&dllServer](const Request& req, Response& res) {
               dllServer.handleDeleteHead(req, res);
             });

  svr.Post("/doublyLinkedList/insertEnd",
           [&dllServer](const Request& req, Response& res) {
             dllServer.handleInsertEnd(req, res);
           });

  svr.Delete("/doublyLinkedList/deleteEnd",
             [&dllServer](const Request& req, Response& res) {
               dllServer.handleDeleteEnd(req, res);
             });

  svr.Post("/doublyLinkedList/insertAtIndex",
           [&dllServer](const Request& req, Response& res) {
             dllServer.handleInsertAtIndex(req, res);
           });

  svr.Delete("/doublyLinkedList/deleteAtIndex",
             [&dllServer](const Request& req, Response& res) {
               dllServer.handleDeleteAtIndex(req, res);
             });

  svr.Get("/doublyLinkedList/search",
          [&dllServer](const Request& req, Response& res) {
            dllServer.handleSearch(req, res);
          });

  svr.Get("/doublyLinkedList/get",
          [&dllServer](const Request& req, Response& res) {
            dllServer.handleGet(req, res);
          });

  svr.Get("/doublyLinkedList/updateGraph",
          [&dllServer](const Request& req, Response& res) {
            handleCORS(req, res);
            dllServer.updateGraph(req, res);
          });
}

void doublyCircularListRoutes(Server& svr,
                              DoublyCircularListServer& dclServer) {
  svr.Post("/doublyCircularList/insertHead",
           [&dclServer](const Request& req, Response& res) {
             dclServer.handleInsertHead(req, res);
           });

  svr.Delete("/doublyCircularList/deleteHead",
             [&dclServer](const Request& req, Response& res) {
               dclServer.handleDeleteHead(req, res);
             });

  svr.Post("/doublyCircularList/insertEnd",
           [&dclServer](const Request& req, Response& res) {
             dclServer.handleInsertTail(req, res);
           });

  svr.Delete("/doublyCircularList/deleteEnd",
             [&dclServer](const Request& req, Response& res) {
               dclServer.handleDeleteTail(req, res);
             });

  svr.Post("/doublyCircularList/insertAtIndex",
           [&dclServer](const Request& req, Response& res) {
             dclServer.handleInsertAtIndex(req, res);
           });

  svr.Delete("/doublyCircularList/deleteAtIndex",
             [&dclServer](const Request& req, Response& res) {
               dclServer.handleDeleteAtIndex(req, res);
             });

  svr.Get("/doublyCircularList/search",
          [&dclServer](const Request& req, Response& res) {
            dclServer.handleSearch(req, res);
          });

  svr.Get("/doublyCircularList/get",
          [&dclServer](const Request& req, Response& res) {
            dclServer.handleGet(req, res);
          });

  svr.Get("/doublyCircularList/updateGraph",
          [&dclServer](const Request& req, Response& res) {
            dclServer.updateGraph(req, res);
          });
  svr.Get("/doublyCircularList/lenght",
          [&dclServer](const Request& req, Response& res) {
            dclServer.handleGetLength(req, res);
          });
}

void binarySearchTreeRoutes(Server& svr, BinarySearchTreeServer bstServer) {
  svr.Post("/binarySearchTree/insert",
           [&bstServer](const Request& req, Response& res) {
             bstServer.handleInsert(req, res);
           });

  svr.Delete("/binarySearchTree/delete",
             [&bstServer](const Request& req, Response& res) {
               bstServer.handleDelete(req, res);
             });

  svr.Get("/binarySearchTree/getGraphviz",
          [&bstServer](const Request& req, Response& res) {
            bstServer.handleGenerateGraphviz(req, res);
          });
  svr.Get("/binarySearchTree/Preorder",
          [&bstServer](const Request& req, Response& res) {
            bstServer.handlePreorder(req, res);
          });
  svr.Get("/binarySearchTree/Inorder",
          [&bstServer](const Request& req, Response& res) {
            bstServer.handleInorder(req, res);
          });
  svr.Get("/binarySearchTree/Postorder",
          [&bstServer](const Request& req, Response& res) {
            bstServer.handlePostorder(req, res);
          });
}

int main() {
  LinkedListServer llServer;
  DoublyLinkedListServer dllServer;
  DoublyCircularListServer dclServer;
  BinarySearchTreeServer bstServer;

  httplib::Server svr;

  linkedListRoutes(svr, llServer);
  doublyLinkedListRoutes(svr, dllServer);
  doublyCircularListRoutes(svr, dclServer);
  binarySearchTreeRoutes(svr, bstServer);

  std::cout << "Servidor corriendo en http://localhost:8080" << std::endl;
  svr.listen("0.0.0.0", 8080);

  return 0;
}