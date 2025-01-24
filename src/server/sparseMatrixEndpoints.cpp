#include <iostream>

#include "../include/sparceMatrix.h"
#include "../lib/httplib.h"
#include "../lib/json.hpp"

using namespace std;
using namespace nlohmann;
using namespace httplib;

class SparseMatrixServer {
 private:
  sparseMatrix mtx;

 public:
  void handleInsert(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      string color = body.at("color");
      int col = body.at("column");
      int row = body.at("row");
      mtx.insertColor(color, col, row);
      json response = {{"status", "success"},
                       {"message", "color ingresado correctamente"},
                       {"color", color}};
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
      int col = body.at("column");
      int row = body.at("row");
      mtx.deleteColor(col, row);
      json response = {{"status", "success"},
                       {"message", "color eliminado correctamente"}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }

  void handleToJson(const Request& req, Response& res) {
    try {
      json file = mtx.toJson();
      json response = {{"status", "success"},
                       {"message", "json obtenido correctamente"},
                       {"matrix", file["matrix"]}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }
  void handleInsertJson(const Request& req, Response& res) {
    try {
      auto body = json::parse(req.body);
      json file = body.at("file");
      mtx.insertJson(file);
      json response = {{"status", "success"},
                       {"message", "json cargado correctamente"}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error procesando la solicitud"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }
  void handleGetInitialData(const Request& req, Response& res) {
    try {
      json file = mtx.toJson();
      json response = {{"status", "success"},
                       {"message", "Datos iniciales obtenidos correctamente"},
                       {"matrix", file["matrix"]}};
      res.set_content(response.dump(), "application/json");
    } catch (const exception& e) {
      json error = {{"status", "error"},
                    {"message", "Error obteniendo datos iniciales"},
                    {"exception", e.what()}};
      res.set_content(error.dump(), "application/json");
      res.status = 500;
    }
  }
  void handleClean(const Request& req, Response& res) {
    try {
      mtx.clearMatrix();
      json response = {{"status", "success"},
                       {"message", "matriz limpiada correctamente"}};
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