#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <any>
#include "../list/List.h"
#include <sstream>
#include <string>
#include <typeinfo>
#include "../../../entities/connection/Connection.h"

using namespace std;

class GraphConnection {
private:
    Connection* connection;  // Puntero a objeto Connection

public:
    GraphConnection(Connection* conn) : connection(conn) {}
    
    ~GraphConnection() {
        delete connection;
    }

    Connection* getConnection() const { return connection; }
    std::string getOrigen() const { return connection->getDistributionCenterOrigin(); }
    std::string getDestino() const { return connection->getDistributionCenterDestination(); }
    double getPeso() const { return connection->getDistance(); }

    string toString() const {
        ostringstream oss;
        oss << "(origen: " << connection->getDistributionCenterOrigin() 
            << ", dest: " << connection->getDistributionCenterDestination() 
            << ", dist: " << connection->getDistance() << ")";
        return oss.str();
    }
};

class GraphNode {
private:
    any data;                 // dato generico
    List connections;       // lista de conexiones

public:
    GraphNode(any newData)
        : data(newData) {}

    any getData() const { return data; }
    
    // Agregar conexión usando objeto Connection
    void addConnection(Connection* connection) {
        connections.push(new GraphConnection(connection));
    }

    const List& getConnections() const {
        return connections;
    }

    string dataToString() const {
        try {
            if (data.type() == typeid(int))
                return to_string(any_cast<int>(data));
            else if (data.type() == typeid(double))
                return to_string(any_cast<double>(data));
            else if (data.type() == typeid(string))
                return any_cast<string>(data);
            else if (data.type() == typeid(const char*))
                return string(any_cast<const char*>(data));
            else
                return "[unknown]";
        } catch (const bad_any_cast&) {
            return "[error]";
        }
    }

    string toString() const {
        ostringstream oss;
        oss << dataToString() << " -> ";
        ::Node* current = connections.getHead();
        while (current != nullptr) {
            try {
                GraphConnection* graphConn = std::any_cast<GraphConnection*>(current->getData());
                oss << graphConn->toString() << " ";
            } catch (const bad_any_cast&) {
                oss << "[invalid] ";
            }
            current = current->getNext();
        }
        return oss.str();
    }
};

class Graph {
private:
    List nodes;  // todos los nodos

public:
    Graph() = default;

    ~Graph() {
        ::Node* current = nodes.getHead();
        while (current != nullptr) {
            delete any_cast<GraphNode*>(current->getData());
            current = current->getNext();
        }
    }

    // agrega un nodo y devuelve su indice
    int addNode(any data) {
        nodes.push(new GraphNode(data));
        return nodes.getSize() - 1;
    }

    // agrega una conexión desde origen a destino
    void addConnection(int origen, int destino, double peso = 1.0) {
        if (origen >= 0 && origen < nodes.getSize() &&
            destino >= 0 && destino < nodes.getSize()) {
            GraphNode* nodeOrigen = any_cast<GraphNode*>(nodes.getNodeAt(origen)->getData());
            
            // Crear códigos temporales para la conexión
            std::string originCode = "N" + std::to_string(origen);
            std::string destCode = "N" + std::to_string(destino);
            
            Connection* conn = new Connection(0, originCode, destCode, peso);
            nodeOrigen->addConnection(conn);
        } else {
            cerr << "Error: indice de nodo invalido." << endl;
        }
    }

    GraphNode* getNode(int index) const {
        if (index >= 0 && index < nodes.getSize()) {
            return any_cast<GraphNode*>(nodes.getNodeAt(index)->getData());
        }
        return nullptr;
    }

    string toString() const {
        ostringstream oss;
        Node* current = nodes.getHead();
        int i = 0;
        while (current != nullptr) {
            GraphNode* n = any_cast<GraphNode*>(current->getData());
            oss << "Nodo " << i << ": " << n->toString() << "\n";
            current = current->getNext();
            i++;
        }
        return oss.str();
    }

    void display() const {
        cout << toString();
    }
};

#endif // GRAPH_H