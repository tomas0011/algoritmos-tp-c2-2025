#ifndef DISTRIBUTION_CENTER_SERVICE_H
#define DISTRIBUTION_CENTER_SERVICE_H

#include "../../utils/dataStructures/graph/GraphHashTable.h"
#include "../../entities/distributionCenter/DistributionCenter.h"
#include <iostream>
#include <vector>
#include <string>

class DistributionCenterService {
private:
    List& distributionCenters;  // Reference to storage list
    GraphHashTable& distributionNetwork;  // Reference to storage graph

public:
    DistributionCenterService(List& centersList, GraphHashTable& network);
    ~DistributionCenterService();

    // CRUD operations según Item A del enunciado
    
    // Mostrar la informacion de un centro de distribucion especifico
    void showCenterInfo(const std::string& code);
    
    // Agregar un nuevo centro
    bool addCenter(const std::string& code, const std::string& name,
                   const std::string& city, int capacity,
                   int dailyPackages, int numEmployees);
    
    // Eliminar un centro existente
    bool removeCenter(const std::string& code);
    
    // Actualizar informacion de un centro
    bool updateCenter(const std::string& code, int capacity,
                      int dailyPackages, int numEmployees);
    
    // Mostrar todos los centros
    void displayAllCenters();
    
    // Mostrar todos los centros ordenados
    void displayCentersSortedByCapacity();
    void displayCentersSortedByPackages();
    void displayCentersSortedByEmployees();
    
    // Verificar si un centro existe
    bool centerExists(const std::string& code);
    
    // Obtener un centro por codigo
    DistributionCenter* getCenter(const std::string& code);
    
    // Obtener todos los centros como vector (para ordenamiento)
    std::vector<DistributionCenter*> getAllCenters();
    
    // Obtener estadisticas generales
    void displayStatistics();
    
    // Cargar centros desde datos mock o archivo
    void loadMockCenters();
    
    // === Gestion de Conexiones ===
    
    // Agregar una conexion bidireccional entre dos centros
    bool addConnection(const std::string& origin, const std::string& destination, double distance);
    
    // Mostrar todas las conexiones de un centro
    void showCenterConnections(const std::string& code);
    
    // Mostrar todas las conexiones del sistema
    void displayAllConnections();
    
    // Cargar conexiones de ejemplo
    void loadMockConnections();
    
    // === Algoritmo de Dijkstra ===
    
    // Calcular y mostrar el camino minimo entre dos centros
    void calculateShortestPath(const std::string& origin, const std::string& destination);
    
    // Calcular y mostrar todas las distancias desde un centro origen
    void calculateAllDistancesFrom(const std::string& origin);
    
    // Obtener el grafo de la red (para acceso directo si es necesario)
    GraphHashTable& getRedDistribucion() { return distributionNetwork; }
};

#endif // DISTRIBUTION_CENTER_SERVICE_H
