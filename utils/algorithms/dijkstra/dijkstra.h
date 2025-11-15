#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <limits>
#include "../../dataStructures/graph/GraphHashTable.h"
#include "../../dataStructures/hashtable/HashTable.h"
#include "../../dataStructures/list/List.h"

using namespace std;

// Estructura para el resultado de Dijkstra
struct DijkstraGraphResult {
    HashTable* distances;      // Distancias minimas desde origen
    HashTable* previous;       // Nodo previo en el camino optimo
    bool success;              // Si se encontro un camino
    
    DijkstraGraphResult() : distances(nullptr), previous(nullptr), success(false) {}
    
    ~DijkstraGraphResult() {
        if (distances) {
            List keys = distances->getKeys();
            Node* current = keys.getHead();
            while (current != nullptr) {
                string key = any_cast<string>(current->getData());
                double* dist = any_cast<double*>(distances->search(key));
                delete dist;
                current = current->getNext();
            }
            delete distances;
        }
        
        if (previous) {
            List keys = previous->getKeys();
            Node* current = keys.getHead();
            while (current != nullptr) {
                string key = any_cast<string>(current->getData());
                string* prev = any_cast<string*>(previous->search(key));
                delete prev;
                current = current->getNext();
            }
            delete previous;
        }
    }
};

/**
 * Algoritmo de Dijkstra usando GraphHashTable
 * 
 * @param graph El grafo con la red de centros
 * @param origin Codigo del centro origen
 * @param destination Codigo del centro destino (opcional)
 * @return DijkstraGraphResult con las distancias y caminos optimos
 */
DijkstraGraphResult* dijkstra(const GraphHashTable& graph, 
                                   const string& origin, 
                                   const string& destination = "");

/**
 * Reconstruir el camino desde origen hasta destino
 */
List reconstructPathGraph(const DijkstraGraphResult* result, 
                         const string& origin, 
                         const string& destination);

/**
 * Mostrar el resultado de Dijkstra
 */
void displayDijkstraGraphResult(const DijkstraGraphResult* result, 
                               const string& origin);

/**
 * Mostrar el camino especifico entre dos centros
 */
void displayPathGraph(const DijkstraGraphResult* result, 
                     const string& origin, 
                     const string& destination);

#endif // DIJKSTRA_GRAPH_H

// Made with Bob
