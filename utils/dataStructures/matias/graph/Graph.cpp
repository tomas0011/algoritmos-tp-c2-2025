#include "Graph.h"

// --- NODOS ---
void Graph::addNode(DistributionCenter* center) {
    if (!existsNode(center->getId())) {
        nodes[center->getId()] = center;
    }
}

DistributionCenter* Graph::getNode(int id) {
    if (nodes.find(id) != nodes.end())
        return nodes[id];
    return nullptr;
}

bool Graph::existsNode(int id) {
    return nodes.find(id) != nodes.end();
}

// --- ARISTAS ---
void Graph::addEdge(int fromId, int toId, double distance) {
    if (!existsNode(fromId) || !existsNode(toId)) return; //si no existe algun nodo, no hace nada
    if (!existsEdge(fromId, toId)) {
        adj[fromId].push_back({toId, distance});
        adj[toId].push_back({fromId, distance}); // bidireccional
    }
}

bool Graph::existsEdge(int fromId, int toId) {
    for (auto& edge : adj[fromId]) {
        if (edge.first == toId) 
            return true;
    }
    return false;
}

double Graph::getDistance(int fromId, int toId) {
    for (auto& edge : adj[fromId]) {
        if (edge.first == toId) 
            return edge.second;
    }
    return -1.0; // si no existe
}

// --- VISUALIZACIÓN ---
void Graph::displayGraph() {
    std::cout << "\n=== Distribution Network ===" << std::endl;
    for (auto& [id, edges] : adj) {
        std::cout << "Center " << id << " (" << nodes[id]->getCity() << ") connected with: ";
        for (auto& [dest, dist] : edges) {
            std::cout << dest << " [" << dist << " km], ";
        }
        std::cout << std::endl;
    }
}

// --- UTILIDADES ---
std::vector<int> Graph::getConnections(int id) {
    std::vector<int> result;
    for (auto& edge : adj[id]) 
        result.push_back(edge.first);
    return result;
}

std::vector<DistributionCenter*> Graph::getAllCenters() {
    std::vector<DistributionCenter*> result;
    
    for (auto& [id, center] : nodes) 
        result.push_back(center);
    return result;
}