#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <any>
#include "../list/List.h"
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;


// =======================================================
// Clase Edge (Arista)
// =======================================================

class Edge {
private:
    int origen;   // índice del nodo origen
    int destino;  // índice del nodo destino
    double peso;  // peso de la arista

    //no se guarda explícitamente un índice dentro de la clase node, pero su índice está implícito: 
    //es su posición dentro del vector<Node*> nodes del Graph.

public:
    Edge(int origen, int destino, double peso = 1.0) //peso por defecto, si no le pones, es 1
        : origen(origen), destino(destino), peso(peso) {}

    int getOrigen() const { return origen; }
    int getDestino() const { return destino; }
    double getPeso() const { return peso; }

    string toString() const {
        ostringstream oss;
        oss << "(origen: " << origen << ", dest: " << destino << ", peso: " << peso << ")";
        return oss.str();
    }
};

// =======================================================
// Clase Node (Nodo)
// =======================================================
class GraphNode {
private:
    any data;                 // dato genérico
    List edges;       // lista de aristas

public:
    GraphNode(any newData)
        : data(newData) {}

    any getData() const { return data; }


    //esta función la usa la clase grafo, agrega validación
    void addEdge(int origen, int destino, double peso = 1.0) {
    edges.push(Edge(origen, destino, peso));
    }

    const List& getEdges() const {
        return edges;
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
        Node* current = edges.getHead();
        while (current != nullptr) {
            Edge edge = any_cast<Edge>(current->getData());
            oss << edge.toString() << " ";
            current = current->getNext();
        }
        return oss.str();
    }
};

// =======================================================
// Clase Graph (Grafo)
// =======================================================
class Graph {
private:
    List nodes;  // todos los nodos

public:
    Graph() = default;

    ~Graph() {
        Node* current = nodes.getHead();
        while (current != nullptr) {
            delete any_cast<GraphNode*>(current->getData());
            current = current->getNext();
        }
    }

    // agrega un nodo y devuelve su índice
    int addNode(any data) {
        nodes.push(new GraphNode(data));
        return nodes.getSize() - 1;
    }

    // agrega una arista desde origen a destino
void addEdge(int origen, int destino, double peso = 1.0) {
    if (origen >= 0 && origen < nodes.getSize() &&
        destino >= 0 && destino < nodes.getSize()) {
        GraphNode* nodeOrigen = any_cast<GraphNode*>(nodes.getNodeAt(origen)->getData());
        nodeOrigen->addEdge(origen, destino, peso);
    } else {
        cerr << "Error: índice de nodo inválido." << endl;
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