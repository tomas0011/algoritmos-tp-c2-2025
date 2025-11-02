#ifndef DISTRIBUTION_CENTER_MANAGER_H
#define DISTRIBUTION_CENTER_MANAGER_H

#include "../distributionCenter/DistributionCenter.h"
#include "../../utils/dataStructures/hashtable/HashTable.h"
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <cstdint>

// Enum para criterios de ordenamiento
enum class SortCriterion {
    CAPACITY,
    DAILY_PACKAGES,
    EMPLOYEES
};

class DistributionCenterManager {
private:
    // Tabla hash PROPIA con función personalizada (Folding + División)
    // Implementa los métodos vistos en clase:
    // 1. Folding: divide la clave en partes y suma sus valores ASCII
    // 2. División: aplica módulo con número primo (6257)
    HashTable<std::string, DistributionCenter> centersByCode;
    
    // Grafo de conexiones: código -> [(código_destino, distancia)]
    // Usamos vector (estructura estándar aceptable) para lista de adyacencia
    HashTable<std::string, std::vector<std::pair<std::string, int>>> graph;
    
    // Métodos privados
    std::string normalizeCode(const std::string& code) const;
    void buildGraph();

public:
    // Constructor
    DistributionCenterManager();
    
    // Carga de datos desde archivos
    bool loadCentersFromFile(const std::string& filename);
    bool loadConnectionsFromFile(const std::string& filename);
    
    // Gestión de centros
    bool addCenter(const DistributionCenter& center);
    bool removeCenter(const std::string& code);
    DistributionCenter* getCenter(const std::string& code);
    bool centerExists(const std::string& code) const;
    
    // Mostrar información
    void displayCenter(const std::string& code) const;
    void displayAllCenters() const;
    
    // Ordenamiento y listado
    std::vector<DistributionCenter> listCentersSortedBy(SortCriterion criterion) const;
    
    // Camino mínimo (Dijkstra)
    std::pair<int, std::vector<std::string>> shortestPath(
        const std::string& origin, 
        const std::string& destination
    );
    
    // Utilidades
    int getTotalCenters() const;
    void printStatistics() const;
};

#endif // DISTRIBUTION_CENTER_MANAGER_H
