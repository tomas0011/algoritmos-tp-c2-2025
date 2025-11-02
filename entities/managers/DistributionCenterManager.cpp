#include "DistributionCenterManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Constructor
DistributionCenterManager::DistributionCenterManager() {
    // HashTable propia ya tiene capacidad inicial de 6257 (número primo)
    // No necesita reserve() como unordered_map
}

// Normalizar código (convertir a mayúsculas los codigos. ej CBA, MZA)
std::string DistributionCenterManager::normalizeCode(const std::string& code) const {
    std::string normalized = code;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::toupper);
    return normalized;
}

// Cargar centros desde archivo centros.txt
// Formato: código nombre ciudad capacidad paquetes_diarios empleados
bool DistributionCenterManager::loadCentersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    int loaded = 0;
    
    std::cout << "\n=== Cargando centros desde " << filename << " ===" << std::endl;
    
    while (std::getline(file, line)) {
        lineNumber++;
        std::istringstream iss(line);
        std::string code, name, city;
        int capacity, dailyPackages, employees;
        
        if (iss >> code >> name >> city >> capacity >> dailyPackages >> employees) {
            DistributionCenter center(code, name, city, capacity, dailyPackages, employees);
            if (addCenter(center)) {
                loaded++;
                std::cout << "✓ Cargado: " << code << " - " << name << std::endl;
            } else {
                std::cout << "⚠ Centro duplicado: " << code << std::endl;
            }
        } else {
            std::cerr << "Error en línea " << lineNumber << ": formato incorrecto" << std::endl;
        }
    }
    
    file.close();
    std::cout << "Total centros cargados: " << loaded << std::endl;
    std::cout << "======================================" << std::endl;
    return loaded > 0;
}

// Cargar conexiones desde archivo conexiones.txt
// Formato: centro_origen centro_destino distancia
bool DistributionCenterManager::loadConnectionsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    int loaded = 0;
    
    std::cout << "\n=== Cargando conexiones desde " << filename << " ===" << std::endl;
    
    while (std::getline(file, line)) {
        lineNumber++;
        std::istringstream iss(line);
        std::string origin, destination;
        int distance;
        
        if (iss >> origin >> destination >> distance) {
            origin = normalizeCode(origin);
            destination = normalizeCode(destination);
            
            // Grafo no dirigido: agregar conexión en ambos sentidos
            // Obtener o crear vector de conexiones para origen
            std::vector<std::pair<std::string, int>>* originConnections = graph.find(origin);
            if (!originConnections) {
                graph.insert(origin, std::vector<std::pair<std::string, int>>());
                originConnections = graph.find(origin);
            }
            originConnections->push_back({destination, distance});
            
            // Hacer lo mismo para destino
            std::vector<std::pair<std::string, int>>* destConnections = graph.find(destination);
            if (!destConnections) {
                graph.insert(destination, std::vector<std::pair<std::string, int>>());
                destConnections = graph.find(destination);
            }
            destConnections->push_back({origin, distance});
            
            loaded++;
            std::cout << "✓ " << origin << " <-> " << destination << " (" << distance << " km)" << std::endl;
        } else {
            std::cerr << "Error en línea " << lineNumber << ": formato incorrecto" << std::endl;
        }
    }
    
    file.close();
    std::cout << "Total conexiones cargadas: " << loaded << std::endl;
    std::cout << "======================================" << std::endl;
    return loaded > 0;
}

// Agregar un nuevo centro
bool DistributionCenterManager::addCenter(const DistributionCenter& center) {
    std::string code = normalizeCode(center.getCode());
    
    // Verificar si ya existe usando nuestra HashTable
    if (centersByCode.contains(code)) {
        return false; // Ya existe
    }
    
    // Crear copia con código normalizado
    DistributionCenter normalizedCenter(
        code,
        center.getName(),
        center.getCity(),
        center.getCapacity(),
        center.getDailyPackages(),
        center.getEmployeeCount()
    );
    
    // Insertar usando nuestra HashTable
    centersByCode.insert(code, normalizedCenter);
    return true;
}

// Eliminar un centro existente
bool DistributionCenterManager::removeCenter(const std::string& code) {
    std::string normalizedCode = normalizeCode(code);
    
    // Verificar si existe y eliminar de nuestra HashTable
    if (!centersByCode.remove(normalizedCode)) {
        return false; // No existe
    }
    
    // Eliminar conexiones relacionadas del grafo
    graph.remove(normalizedCode);
    
    // Remover referencias en las conexiones de otros nodos
    auto allNodes = graph.getAll();
    for (const auto& nodePair : allNodes) {
        const std::string& nodeCode = nodePair.first;
        std::vector<std::pair<std::string, int>> connections = nodePair.second;
        
        // Filtrar conexiones que apuntan al nodo eliminado
        std::vector<std::pair<std::string, int>> filteredConnections;
        for (const auto& conn : connections) {
            if (conn.first != normalizedCode) {
                filteredConnections.push_back(conn);
            }
        }
        
        // Actualizar en el grafo
        graph.insert(nodeCode, filteredConnections);
    }
    
    return true;
}

// Obtener un centro por código
DistributionCenter* DistributionCenterManager::getCenter(const std::string& code) {
    std::string normalizedCode = normalizeCode(code);
    return centersByCode.find(normalizedCode);
}

// Verificar si un centro existe
bool DistributionCenterManager::centerExists(const std::string& code) const {
    std::string normalizedCode = normalizeCode(code);
    return centersByCode.contains(normalizedCode);
}

// Mostrar información de un centro específico
void DistributionCenterManager::displayCenter(const std::string& code) const {
    std::string normalizedCode = normalizeCode(code);
    DistributionCenter* center = const_cast<HashTable<std::string, DistributionCenter>*>(&centersByCode)->find(normalizedCode);
    
    if (center) {
        center->display();
    } else {
        std::cout << "Centro '" << code << "' no encontrado." << std::endl;
    }
}

// Mostrar todos los centros
void DistributionCenterManager::displayAllCenters() const {
    auto allCenters = centersByCode.getAll();
    
    if (allCenters.empty()) {
        std::cout << "No hay centros registrados." << std::endl;
        return;
    }
    
    std::cout << "\n=== TODOS LOS CENTROS ===" << std::endl;
    for (const auto& pair : allCenters) {
        pair.second.display();
        std::cout << std::endl;
    }
}

// Listar centros ordenados por criterio
std::vector<DistributionCenter> DistributionCenterManager::listCentersSortedBy(SortCriterion criterion) const {
    std::vector<DistributionCenter> centers;
    
    // Obtener todos los centros de nuestra HashTable
    auto allCenters = centersByCode.getAll();
    centers.reserve(allCenters.size());
    
    // Copiar todos los centros a vector
    for (const auto& pair : allCenters) {
        centers.push_back(pair.second);
    }
    
    // Ordenar según criterio
    switch (criterion) {
        case SortCriterion::CAPACITY:
            std::sort(centers.begin(), centers.end(),
                [](const DistributionCenter& a, const DistributionCenter& b) {
                    return a.getCapacity() > b.getCapacity(); // Descendente
                });
            std::cout << "\n=== Centros ordenados por CAPACIDAD ===" << std::endl;
            break;
            
        case SortCriterion::DAILY_PACKAGES:
            std::sort(centers.begin(), centers.end(),
                [](const DistributionCenter& a, const DistributionCenter& b) {
                    return a.getDailyPackages() > b.getDailyPackages(); // Descendente
                });
            std::cout << "\n=== Centros ordenados por PAQUETES DIARIOS ===" << std::endl;
            break;
            
        case SortCriterion::EMPLOYEES:
            std::sort(centers.begin(), centers.end(),
                [](const DistributionCenter& a, const DistributionCenter& b) {
                    return a.getEmployeeCount() > b.getEmployeeCount(); // Descendente
                });
            std::cout << "\n=== Centros ordenados por EMPLEADOS ===" << std::endl;
            break;
    }
    
    // Mostrar resultados
    for (const auto& center : centers) {
        std::cout << center.getCode() << " | " << center.getName() 
                  << " | Cap: " << center.getCapacity()
                  << " | Paq: " << center.getDailyPackages()
                  << " | Emp: " << center.getEmployeeCount() << std::endl;
    }
    std::cout << "======================================" << std::endl;
    
    return centers;
}

// Algoritmo de Dijkstra para encontrar camino mínimo
std::pair<int, std::vector<std::string>> DistributionCenterManager::shortestPath(
    const std::string& origin, 
    const std::string& destination
) {
    std::string normOrigin = normalizeCode(origin);
    std::string normDest = normalizeCode(destination);
    
    // Verificar que ambos centros existen
    if (!centerExists(normOrigin) || !centerExists(normDest)) {
        std::cerr << "Error: Uno o ambos centros no existen" << std::endl;
        return {-1, {}};
    }
    
    // Estructuras para Dijkstra - usando nuestra HashTable
    HashTable<std::string, int> distances;
    HashTable<std::string, std::string> previous;
    HashTable<std::string, bool> visited;
    
    // Priority queue: (distancia, nodo)
    std::priority_queue<
        std::pair<int, std::string>,
        std::vector<std::pair<int, std::string>>,
        std::greater<std::pair<int, std::string>>
    > pq;
    
    // Inicialización - insertar todos los nodos
    const int INF = std::numeric_limits<int>::max();
    auto allCenters = centersByCode.getAll();
    for (const auto& pair : allCenters) {
        distances.insert(pair.first, INF);
        visited.insert(pair.first, false);
    }
    
    distances[normOrigin] = 0;
    pq.push({0, normOrigin});
    
    // Algoritmo de Dijkstra
    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();
        
        bool* isVisited = visited.find(currentNode);
        if (isVisited && *isVisited) continue;
        visited[currentNode] = true;
        
        // Si llegamos al destino, podemos terminar
        if (currentNode == normDest) break;
        
        // Explorar vecinos - buscar conexiones en el grafo
        std::vector<std::pair<std::string, int>>* neighbors = graph.find(currentNode);
        if (neighbors) {
            for (const auto& [neighbor, weight] : *neighbors) {
                int newDist = currentDist + weight;
                int* currentNeighborDist = distances.find(neighbor);
                
                if (currentNeighborDist && newDist < *currentNeighborDist) {
                    distances[neighbor] = newDist;
                    previous[neighbor] = currentNode;
                    pq.push({newDist, neighbor});
                }
            }
        }
    }
    
    // Verificar si hay camino
    int* finalDist = distances.find(normDest);
    if (!finalDist || *finalDist == INF) {
        std::cerr << "No existe camino entre " << origin << " y " << destination << std::endl;
        return {-1, {}};
    }
    
    // Reconstruir camino
    std::vector<std::string> path;
    std::string current = normDest;
    while (current != normOrigin) {
        path.push_back(current);
        std::string* prev = previous.find(current);
        if (!prev) break;
        current = *prev;
    }
    path.push_back(normOrigin);
    std::reverse(path.begin(), path.end());
    
    // Mostrar resultado
    std::cout << "\n=== CAMINO MÍNIMO ===" << std::endl;
    std::cout << "Origen: " << normOrigin << std::endl;
    std::cout << "Destino: " << normDest << std::endl;
    std::cout << "Distancia total: " << *finalDist << " km" << std::endl;
    std::cout << "Ruta: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "=====================" << std::endl;
    
    return {*finalDist, path};
}

// Obtener total de centros
int DistributionCenterManager::getTotalCenters() const {
    return centersByCode.getSize();
}

// estadísticas
void DistributionCenterManager::printStatistics() const {
    std::cout << "\n=== ESTADÍSTICAS ===" << std::endl;
    std::cout << "Total de centros: " << centersByCode.getSize() << std::endl;
    std::cout << "Total de conexiones: " << graph.getSize() << std::endl;
    
    // Estadísticas de nuestra HashTable 
    std::cout << "Load factor: " << centersByCode.getLoadFactor() * 100 << "%" << std::endl;
    std::cout << "Capacidad: " << centersByCode.getCapacity() << std::endl;
    std::cout << "=====================" << std::endl;
}
