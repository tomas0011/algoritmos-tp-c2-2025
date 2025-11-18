#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <any>
#include "../list/List.h"
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;


class Arista {
private:
    int origen;   // indice del nodo origen
    int destino;  // indice del nodo destino
    double peso;  // peso de la arista

    //no se guarda explicitamente un indice dentro de la clase node, pero su indice esta implicito: 
    //es su posicion dentro del vector<Node*> nodes del Graph.

public:
    Arista(int origen, int destino, double peso = 1.0) //peso por defecto, si no le pones, es 1
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

class GraphNode {
private:
    any data;                 // dato generico
    List aristas;       // lista de aristas

public:
    GraphNode(any newData)
        : data(newData) {}

    any getData() const { return data; }


    //esta funcion la usa la clase grafo, agrega validacion
    void addArista(int origen, int destino, double peso = 1.0) {
    aristas.push(Arista(origen, destino, peso));
    }

    const List& getAristas() const {
        return aristas;
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
        ::Node* current = aristas.getHead();
        while (current != nullptr) {
            Arista arista = any_cast<Arista>(current->getData());
            oss << arista.toString() << " ";
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

    // agrega una arista desde origen a destino
void addArista(int origen, int destino, double peso = 1.0) {
    if (origen >= 0 && origen < nodes.getSize() &&
        destino >= 0 && destino < nodes.getSize()) {
        GraphNode* nodeOrigen = any_cast<GraphNode*>(nodes.getNodeAt(origen)->getData());
        nodeOrigen->addArista(origen, destino, peso);
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