#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include "../../../entities/distributionCenter/DistributionCenter.h"

// Grafo no dirigido y ponderado (para modelar conexiones entre centros)
class Graph {
private:
    // asociamos ID con nodos
    std::map<int, DistributionCenter*> nodes; // ID -> centro
    
    std::map<int, std::vector<std::pair<int, double>>> adj; // ID -> [(destino, distancia)]

public:
    Graph() = default;

    // --- Gestión de nodos ---
    void addNode(DistributionCenter* center);
    DistributionCenter* getNode(int id);
    bool existsNode(int id);

    // --- Gestión de aristas ---
    void addEdge(int fromId, int toId, double distance);
    bool existsEdge(int fromId, int toId);
    double getDistance(int fromId, int toId);

    // --- Visualización ---
    void displayGraph();

    // --- Utilidades ---
    
    // retorna los ID conectados a un ID dado
    std::vector<int> getConnections(int id);

    // retorna todos los punteros a centros almacenados en el grafo
    std::vector<DistributionCenter*> getAllCenters();
};

#endif // GRAPH_H
