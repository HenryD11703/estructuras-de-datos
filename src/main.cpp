#include <iostream>

#include "../lib/httplib.h"
#include "AVLTreeEndpoints.cpp"
#include "binarySearchTreeEndpoints.cpp"
#include "doublyCircularListEndpoints.cpp"
#include "doublyLinkedListEndpoints.cpp"
#include "linkedListEndpoints.cpp"
#include "sparseMatrixEndpoints.cpp"

using namespace httplib;
using namespace std;

void setupCORS(Server& svr) {
  svr.set_pre_routing_handler([](const Request& req, Response& res) {
    // Permitir solicitudes desde cualquier origen
    res.set_header("Access-Control-Allow-Origin", "*");

    res.set_header("Access-Control-Allow-Methods",
                   "GET, POST, DELETE, OPTIONS");

    res.set_header("Access-Control-Allow-Headers",
                   "Content-Type, Authorization");

    res.set_header("Access-Control-Max-Age", "86400");

    if (req.method == "OPTIONS") {
      res.status = 204;
      return Server::HandlerResponse::Handled;
    }
    return Server::HandlerResponse::Unhandled;
  });
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

void binarySearchTreeRoutes(Server& svr, BinarySearchTreeServer& bstServer) {
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

void AVLTreeRoutes(Server& svr, AVLTreeServer& avlServer) {
  svr.Post("/avlTree/insert", [&avlServer](const Request& req, Response& res) {
    avlServer.handleInsert(req, res);
  });

  svr.Delete("/avlTree/delete",
             [&avlServer](const Request& req, Response& res) {
               avlServer.handleDelete(req, res);
             });

  svr.Get("/avlTree/getGraphviz",
          [&avlServer](const Request& req, Response& res) {
            avlServer.handleGenerateGraphviz(req, res);
          });
  svr.Get("/avlTree/Preorder", [&avlServer](const Request& req, Response& res) {
    avlServer.handlePreorder(req, res);
  });
  svr.Get("/avlTree/Inorder", [&avlServer](const Request& req, Response& res) {
    avlServer.handleInorder(req, res);
  });
  svr.Get("/avlTree/Postorder",
          [&avlServer](const Request& req, Response& res) {
            avlServer.handlePostorder(req, res);
          });
}

void sparseMatrixRoutes(Server& svr, SparseMatrixServer& mtxServer) {
  svr.Post("/sparseMatrix/insert",
           [&mtxServer](const Request& req, Response& res) {
             mtxServer.handleInsert(req, res);
           });

  svr.Post("/sparseMatrix/loadJSON",
           [&mtxServer](const Request& req, Response& res) {
             mtxServer.handleInsertJson(req, res);
           });

  svr.Delete("/sparseMatrix/delete",
             [&mtxServer](const Request& req, Response& res) {
               mtxServer.handleDelete(req, res);
             });

  svr.Get("/sparseMatrix/getJSON",
          [&mtxServer](const Request& req, Response& res) {
            mtxServer.handleToJson(req, res);
          });

  svr.Get("/sparseMatrix/clean",
          [&mtxServer](const Request& req, Response& res) {
            mtxServer.handleClean(req, res);
          });
}

int main() {
  LinkedListServer llServer;
  DoublyLinkedListServer dllServer;
  DoublyCircularListServer dclServer;
  BinarySearchTreeServer bstServer;
  AVLTreeServer avlServer;
  SparseMatrixServer mtxServer;

  httplib::Server svr;

  setupCORS(svr);

  linkedListRoutes(svr, llServer);
  doublyLinkedListRoutes(svr, dllServer);
  doublyCircularListRoutes(svr, dclServer);
  binarySearchTreeRoutes(svr, bstServer);
  AVLTreeRoutes(svr, avlServer);
  sparseMatrixRoutes(svr, mtxServer);

  cout << "Servidor corriendo en http://localhost:8080" << endl;
  svr.listen("0.0.0.0", 8080);

  return 0;
}