#ifndef GRAPH_HASHTABLE_H
#define GRAPH_HASHTABLE_H

#include <iostream>
#include <any>
#include <string>
#include <sstream>
#include "utils/dataStructures/hashtable/HashTable.h"
#include "utils/dataStructures/list/List.h"

using namespace std;

// Función helper para generar IDs únicos para Arista
inline int generateAristaId() {
    static int nextId = 1;
    return nextId++;
}

// Estructura interna para aristas del grafo
struct Arista {
    int id;
    string origen;
    string destino;
    double peso;
    
    Arista(string org, string dest, double p) 
        : id(generateAristaId()), origen(org), destino(dest), peso(p) {}
        
    Arista(int aristaId, string org, string dest, double p) 
        : id(aristaId), origen(org), destino(dest), peso(p) {}
};

// =======================================================
// Clase HashGraphNode (Nodo del Grafo con HashTable)
// =======================================================
class HashGraphNode {
private:
    string code;        // codigo único del nodo (ej: CBA, MZA)
    any data;           // dato generico (puede ser DistributionCenter*)
    List aristas;       // lista de aristas salientes

public:
    HashGraphNode(string nodeCode, any nodeData)
        : code(nodeCode), data(nodeData) {}

    string getCode() const { return code; }
    any getData() const { return data; }
    const List& getConnections() const { return aristas; }
    
    // Método para obtener aristas (alias para compatibilidad)
    const List& getAristas() const { return aristas; }
    
    // Método para agregar aristas usando estructura interna
    void addArista(string destination, double weight = 1.0) {
        Arista* arista = new Arista(code, destination, weight);
        aristas.push(arista);
    }
    
    // Método para agregar arista usando objeto Arista existente
    void addArista(Arista* arista) {
        aristas.push(arista);
    }

    // Obtener todas las conexiones como lista
    List* getConnectionsList() {
        return &aristas;
    }
    
    // Versión const para métodos const
    const List* getConnectionsList() const {
        return &aristas;
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
                return "[object]";
        } catch (const bad_any_cast&) {
            return "[error]";
        }
    }

    string toString() const {
        ostringstream oss;
        oss << code << " (" << dataToString() << ") -> ";
        
        Node* current = aristas.getHead();
        while (current != nullptr) {
            try {
                Arista* arista = std::any_cast<Arista*>(current->getData());
                oss << arista->origen << " -> " << arista->destino 
                    << " (" << arista->peso << ") ";
            } catch (const bad_any_cast&) {
                oss << "[invalid] ";
            }
            current = current->getNext();
        }
        
        return oss.str();
    }

    ~HashGraphNode() {
        // Limpiar las aristas
        Node* current = aristas.getHead();
        while (current != nullptr) {
            Arista* arista = any_cast<Arista*>(current->getData());
            delete arista;
            current = current->getNext();
        }
    }
};

// =======================================================
// Clase Graph con HashTable
// =======================================================
class GraphHashTable {
private:
    HashTable* nodes;  // HashTable: codigo -> HashGraphNode*
    int nodeCount;

public:
    GraphHashTable(int initialCapacity = 23) : nodeCount(0) {
        nodes = new HashTable(initialCapacity);
    }

    // Copy constructor - deep copy
    GraphHashTable(const GraphHashTable& other) : nodeCount(0) {
        // Crear una nueva HashTable vacía con la misma capacidad
        nodes = new HashTable(other.nodes->getCapacity());
        
        // Copiar todos los nodos
        List allCodes = other.nodes->getKeys();
        Node* current = allCodes.getHead();
        
        while (current != nullptr) {
            string code = any_cast<string>(current->getData());
            HashGraphNode* originalNode = any_cast<HashGraphNode*>(other.nodes->search(code));
            
            // Crear un nuevo nodo con los datos copiados
            HashGraphNode* newNode = new HashGraphNode(originalNode->getCode(), originalNode->getData());
            
            // Copiar las aristas
            const List& originalConnections = originalNode->getConnections();
            Node* connectionNode = originalConnections.getHead();
            while (connectionNode != nullptr) {
                Arista* originalArista = any_cast<Arista*>(connectionNode->getData());
                newNode->addArista(originalArista->destino, originalArista->peso);
                connectionNode = connectionNode->getNext();
            }
            
            nodes->insert(code, newNode);
            nodeCount++;
            current = current->getNext();
        }
    }

    // Assignment operator - deep copy
    GraphHashTable& operator=(const GraphHashTable& other) {
        if (this != &other) {
            // Limpiar nodos existentes
            List allCodes = nodes->getKeys();
            Node* current = allCodes.getHead();
            while (current != nullptr) {
                string code = any_cast<string>(current->getData());
                HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(code));
                delete node;
                current = current->getNext();
            }
            delete nodes;
            
            // Crear nueva HashTable y copiar
            nodeCount = 0;
            nodes = new HashTable(other.nodes->getCapacity());
            
            allCodes = other.nodes->getKeys();
            current = allCodes.getHead();
            
            while (current != nullptr) {
                string code = any_cast<string>(current->getData());
                HashGraphNode* originalNode = any_cast<HashGraphNode*>(other.nodes->search(code));
                
                HashGraphNode* newNode = new HashGraphNode(originalNode->getCode(), originalNode->getData());
                
                const List& originalConnections = originalNode->getConnections();
                Node* connectionNode = originalConnections.getHead();
                while (connectionNode != nullptr) {
                    Arista* originalArista = any_cast<Arista*>(connectionNode->getData());
                    newNode->addArista(originalArista->destino, originalArista->peso);
                    connectionNode = connectionNode->getNext();
                }
                
                nodes->insert(code, newNode);
                nodeCount++;
                current = current->getNext();
            }
        }
        return *this;
    }

    ~GraphHashTable() {
        // Limpiar todos los nodos
        List allCodes = nodes->getKeys();
        Node* current = allCodes.getHead();
        
        while (current != nullptr) {
            string code = any_cast<string>(current->getData());
            HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(code));
            delete node;
            current = current->getNext();
        }
        
        delete nodes;
    }

    // Agregar un nodo al grafo
    bool addNode(string code, any data) {
        if (nodes->contains(code)) {
            cerr << "Error: Nodo '" << code << "' ya existe." << endl;
            return false;
        }

        HashGraphNode* newNode = new HashGraphNode(code, data);
        nodes->insert(code, newNode);
        nodeCount++;
        return true;
    }

    // Agregar una arista dirigida
    bool addArista(string origin, string destination, double weight = 1.0) {
        if (!nodes->contains(origin)) {
            cerr << "Error: Nodo origen '" << origin << "' no existe." << endl;
            return false;
        }

        if (!nodes->contains(destination)) {
            cerr << "Error: Nodo destino '" << destination << "' no existe." << endl;
            return false;
        }

        HashGraphNode* originNode = any_cast<HashGraphNode*>(nodes->search(origin));
        originNode->addArista(destination, weight);
        return true;
    }
    
    // Nuevo método para agregar conexiones usando objetos Connection
    bool addConnection(string origin, string destination, double weight = 1.0) {
        if (!nodes->contains(origin)) {
            cerr << "Error: Nodo origen '" << origin << "' no existe." << endl;
            return false;
        }

        if (!nodes->contains(destination)) {
            cerr << "Error: Nodo destino '" << destination << "' no existe." << endl;
            return false;
        }

        HashGraphNode* originNode = any_cast<HashGraphNode*>(nodes->search(origin));
        originNode->addArista(destination, weight);
        return true;
    }
    
    // Método para agregar conexión desde capa de negocio (Connection -> Arista)
    bool addConnectionFromBusiness(const std::string& origin, const std::string& destination, double weight = 1.0) {
        return addConnection(origin, destination, weight);  // Reutiliza la lógica existente
    }
    
    // Agregar una conexión bidireccional usando aristas internas
    bool addUndirectedConnection(string node1, string node2, double weight = 1.0) {
        bool success1 = addConnection(node1, node2, weight);
        bool success2 = addConnection(node2, node1, weight);
        return success1 && success2;
    }

    // Obtener un nodo por su codigo
    HashGraphNode* getNode(string code) const {
        if (!nodes->contains(code)) {
            return nullptr;
        }
        return any_cast<HashGraphNode*>(nodes->search(code));
    }

    // Verificar si un nodo existe
    bool hasNode(string code) const {
        return nodes->contains(code);
    }

    // Obtener el número de nodos
    int getNodeCount() const {
        return nodeCount;
    }

    // Obtener todos los codigos de nodos
    List getNodeCodes() const {
        return nodes->getKeys();
    }

    // Obtener las aristas de un nodo
    List* getAristas(string code) const {
        if (!nodes->contains(code)) {
            return nullptr;
        }
        
        HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(code));
        // Necesitamos devolver un puntero no const, pero el método debe ser const
        // Para esto, devolvemos el puntero de manera que se pueda modificar
        return const_cast<List*>(node->getConnectionsList());
    }

    // Obtener vecinos de un nodo (nodos adyacentes)
    List getNeighbors(string code) const {
        List neighbors;
        
        if (!nodes->contains(code)) {
            return neighbors;
        }

        HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(code));
        const List& aristas = node->getAristas();
        
        Node* current = aristas.getHead();
        while (current != nullptr) {
            Arista* arista = any_cast<Arista*>(current->getData());
            neighbors.push(arista->destino);
            current = current->getNext();
        }
        
        return neighbors;
    }

    // Obtener el peso de una arista
    double getAristaWeight(string origin, string destination) const {
        if (!nodes->contains(origin)) {
            return -1.0;
        }

        HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(origin));
        const List& aristas = node->getAristas();
        
        Node* current = aristas.getHead();
        while (current != nullptr) {
            Arista* arista = any_cast<Arista*>(current->getData());
            if (arista->destino == destination) {
                return arista->peso;
            }
            current = current->getNext();
        }
        
        return -1.0; // No existe la arista
    }

    // Verificar si existe una arista
    bool hasArista(string origin, string destination) const {
        return getAristaWeight(origin, destination) >= 0;
    }

    // Mostrar el grafo completo
    void display() const {
        cout << "\n=== Grafo (HashTable) ===" << endl;
        cout << "Nodos: " << nodeCount << endl;
        cout << string(60, '-') << endl;

        List allCodes = nodes->getKeys();
        Node* current = allCodes.getHead();

        while (current != nullptr) {
            string code = any_cast<string>(current->getData());
            HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(code));
            cout << node->toString() << endl;
            current = current->getNext();
        }

        cout << string(60, '-') << endl;
    }

    // Convertir a string
    string toString() const {
        ostringstream oss;
        oss << "Graph(nodes=" << nodeCount << ")";
        return oss.str();
    }

    // Obtener estadisticas del grafo
    void displayStatistics() const {
        cout << "\n=== Estadisticas del Grafo ===" << endl;
        cout << "Total de nodos: " << nodeCount << endl;

        int totalAristas = 0;
        List allCodes = nodes->getKeys();
        Node* current = allCodes.getHead();

        while (current != nullptr) {
            string code = any_cast<string>(current->getData());
            HashGraphNode* node = any_cast<HashGraphNode*>(nodes->search(code));
            totalAristas += node->getAristas().getSize();
            current = current->getNext();
        }

        cout << "Total de aristas: " << totalAristas << endl;
        cout << "Densidad: " << (nodeCount > 1 ? (double)totalAristas / (nodeCount * (nodeCount - 1)) : 0) << endl;
        cout << "==============================" << endl;

        // Mostrar estadisticas de la HashTable interna
        nodes->displayStatistics();
    }

    // Obtener la HashTable interna (para algoritmos como Dijkstra)
    HashTable* getNodesHashTable() const {
        return nodes;
    }
};

#endif // GRAPH_HASHTABLE_H

