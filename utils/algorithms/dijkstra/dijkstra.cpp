#include "dijkstra.h"
#include <iostream>

using namespace std;

// Funcion auxiliar para encontrar el nodo no visitado con menor distancia
string findMinDistanceNodeGraph(HashTable* distances, HashTable* visited) {
    double minDist = numeric_limits<double>::infinity();
    string minNode = "";
    
    List keys = distances->getKeys();
    Node* current = keys.getHead();
    
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        
        bool isVisited = false;
        if (visited->contains(code)) {
            isVisited = any_cast<bool>(visited->search(code));
        }
        
        if (!isVisited) {
            double* distPtr = any_cast<double*>(distances->search(code));
            if (distPtr && *distPtr < minDist) {
                minDist = *distPtr;
                minNode = code;
            }
        }
        
        current = current->getNext();
    }
    
    return minNode;
}

DijkstraGraphResult* dijkstra(const GraphHashTable& graph, 
                                   const string& origin, 
                                   const string& destination) {
    DijkstraGraphResult* result = new DijkstraGraphResult();
    
    // Verificar que el origen existe
    if (!graph.hasNode(origin)) {
        cout << "Error: Centro origen '" << origin << "' no encontrado." << endl;
        return result;
    }
    
    // Si se especifico destino, verificar que existe
    if (!destination.empty() && !graph.hasNode(destination)) {
        cout << "Error: Centro destino '" << destination << "' no encontrado." << endl;
        return result;
    }
    
    // Inicializar estructuras
    result->distances = new HashTable(23);
    result->previous = new HashTable(23);
    HashTable visited(23);
    
    // Inicializar distancias a infinito y visitados a false
    List allNodes = graph.getNodeCodes();
    Node* current = allNodes.getHead();
    
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        
        double* dist = new double(numeric_limits<double>::infinity());
        result->distances->insert(code, dist);
        
        string* prev = new string("");
        result->previous->insert(code, prev);
        
        visited.insert(code, false);
        
        current = current->getNext();
    }
    
    // Distancia del origen a si mismo es 0
    double* originDist = any_cast<double*>(result->distances->search(origin));
    *originDist = 0.0;
    
    // Algoritmo de Dijkstra
    int numNodes = graph.getNodeCount();
    
    for (int i = 0; i < numNodes; i++) {
        // Encontrar el nodo no visitado con menor distancia
        string u = findMinDistanceNodeGraph(result->distances, &visited);
        
        if (u.empty()) break;
        
        visited.insert(u, true);
        
        // Si llegamos al destino, podemos terminar
        if (!destination.empty() && u == destination) {
            result->success = true;
            break;
        }
        
        // Obtener distancia actual del nodo u
        double* uDistPtr = any_cast<double*>(result->distances->search(u));
        double uDist = *uDistPtr;
        
        if (uDist == numeric_limits<double>::infinity()) {
            continue;
        }
        
        // Relajar las aristas (obtener vecinos del grafo)
        List* aristas = graph.getAristas(u);
        if (aristas) {
            Node* aristaNode = aristas->getHead();
            
            while (aristaNode != nullptr) {
                Connection* arista = any_cast<Connection*>(aristaNode->getData());
                string v = arista->getDistributionCenterDestination();
                double weight = arista->getDistance();
                
                double newDist = uDist + weight;
                
                double* vDistPtr = any_cast<double*>(result->distances->search(v));
                
                if (newDist < *vDistPtr) {
                    *vDistPtr = newDist;
                    
                    string* prevPtr = any_cast<string*>(result->previous->search(v));
                    *prevPtr = u;
                }
                
                aristaNode = aristaNode->getNext();
            }
        }
    }
    
    result->success = true;
    return result;
}

List reconstructPathGraph(const DijkstraGraphResult* result, 
                         const string& origin, 
                         const string& destination) {
    List path;
    
    if (!result || !result->success) {
        return path;
    }
    
    double* distPtr = any_cast<double*>(result->distances->search(destination));
    if (!distPtr || *distPtr == numeric_limits<double>::infinity()) {
        return path;
    }
    
    string current = destination;
    
    while (!current.empty() && current != origin) {
        path.unshift(current);
        
        string* prevPtr = any_cast<string*>(result->previous->search(current));
        current = *prevPtr;
    }
    
    if (current == origin) {
        path.unshift(origin);
    }
    
    return path;
}

void displayDijkstraGraphResult(const DijkstraGraphResult* result, const string& origin) {
    if (!result || !result->success) {
        cout << "No se pudo calcular el camino." << endl;
        return;
    }
    
    cout << "\n=== Distancias Minimas desde " << origin << " ===" << endl;
    cout << string(60, '=') << endl;
    
    List allNodes = result->distances->getKeys();
    Node* current = allNodes.getHead();
    
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        double* distPtr = any_cast<double*>(result->distances->search(code));
        
        cout << origin << " -> " << code << ": ";
        
        if (*distPtr == numeric_limits<double>::infinity()) {
            cout << "∞ (no alcanzable)";
        } else {
            cout << *distPtr << " km";
        }
        cout << endl;
        
        current = current->getNext();
    }
    
    cout << string(60, '=') << endl;
}

void displayPathGraph(const DijkstraGraphResult* result, 
                     const string& origin, 
                     const string& destination) {
    if (!result || !result->success) {
        cout << "No se pudo calcular el camino." << endl;
        return;
    }
    
    double* distPtr = any_cast<double*>(result->distances->search(destination));
    if (!distPtr || *distPtr == numeric_limits<double>::infinity()) {
        cout << "No existe un camino desde " << origin << " hasta " << destination << endl;
        return;
    }
    
    List path = reconstructPathGraph(result, origin, destination);
    
    if (path.getSize() == 0) {
        cout << "No se pudo reconstruir el camino." << endl;
        return;
    }
    
    cout << "\n=== Camino Minimo (usando GraphHashTable) ===" << endl;
    cout << "Origen: " << origin << endl;
    cout << "Destino: " << destination << endl;
    cout << "Distancia total: " << *distPtr << " km" << endl;
    cout << "\nRuta:" << endl;
    
    Node* current = path.getHead();
    int step = 1;
    
    while (current != nullptr) {
        string code = any_cast<string>(current->getData());
        
        cout << step << ". " << code;
        
        if (current->getNext() != nullptr) {
            string nextCode = any_cast<string>(current->getNext()->getData());
            
            double* currentDistPtr = any_cast<double*>(result->distances->search(code));
            double* nextDistPtr = any_cast<double*>(result->distances->search(nextCode));
            double segmentDist = *nextDistPtr - *currentDistPtr;
            
            cout << " --(" << segmentDist << " km)--> ";
        } else {
            cout << " [DESTINO]";
        }
        
        cout << endl;
        
        current = current->getNext();
        step++;
    }
    
    cout << string(50, '=') << endl;
}

