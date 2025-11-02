#include "DistributionCenterManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

// Constructor
DistributionCenterManager::DistributionCenterManager() {
}

// Normalizar código (convertir a mayúsculas)
string DistributionCenterManager::normalizeCode(const string& code) const {
    string normalized = code;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::toupper);
    return normalized;
}

// Cargar centros desde archivo
bool DistributionCenterManager::loadCentersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << filename << endl;
        return false;
    }
    
    string line;
    int loaded = 0;
    
    cout << "\n=== Cargando centros desde " << filename << " ===" << endl;
    
    while (getline(file, line)) {
        istringstream iss(line);
        string code, name, city;
        int capacity, dailyPackages, employees;
        
        if (iss >> code >> name >> city >> capacity >> dailyPackages >> employees) {
            DistributionCenter center(code, name, city, capacity, dailyPackages, employees);
            if (addCenter(center)) {
                loaded++;
                cout << "✓ Cargado: " << code << " - " << name << endl;
            }
        }
    }
    
    file.close();
    cout << "Total centros cargados: " << loaded << endl;
    return loaded > 0;
}

// Cargar conexiones desde archivo
bool DistributionCenterManager::loadConnectionsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << filename << endl;
        return false;
    }
    
    string line;
    int loaded = 0;
    
    cout << "\n=== Cargando conexiones desde " << filename << " ===" << endl;
    
    while (getline(file, line)) {
        istringstream iss(line);
        string origin, destination;
        int distance;
        
        if (iss >> origin >> destination >> distance) {
            origin = normalizeCode(origin);
            destination = normalizeCode(destination);
            
            // Grafo bidireccional
            vector<pair<string, int>>* originConn = graph.find(origin);
            if (!originConn) {
                graph.insert(origin, vector<pair<string, int>>());
                originConn = graph.find(origin);
            }
            originConn->push_back({destination, distance});
            
            vector<pair<string, int>>* destConn = graph.find(destination);
            if (!destConn) {
                graph.insert(destination, vector<pair<string, int>>());
                destConn = graph.find(destination);
            }
            destConn->push_back({origin, distance});
            
            loaded++;
            cout << "✓ " << origin << " <-> " << destination << " (" << distance << " km)" << endl;
        }
    }
    
    file.close();
    cout << "Total conexiones cargadas: " << loaded << endl;
    return loaded > 0;
}

// Agregar centro
bool DistributionCenterManager::addCenter(const DistributionCenter& center) {
    string code = normalizeCode(center.getCode());
    
    if (centersByCode.contains(code)) {
        return false;
    }
    
    DistributionCenter normalizedCenter(
        code,
        center.getName(),
        center.getCity(),
        center.getCapacity(),
        center.getDailyPackages(),
        center.getEmployeeCount()
    );
    
    centersByCode.insert(code, normalizedCenter);
    return true;
}

// Eliminar centro
bool DistributionCenterManager::removeCenter(const string& code) {
    string normalizedCode = normalizeCode(code);
    
    if (!centersByCode.remove(normalizedCode)) {
        return false;
    }
    
    graph.remove(normalizedCode);
    
    auto allNodes = graph.getAll();
    for (const auto& nodePair : allNodes) {
        const string& nodeCode = nodePair.first;
        vector<pair<string, int>> connections = nodePair.second;
        
        vector<pair<string, int>> filtered;
        for (const auto& conn : connections) {
            if (conn.first != normalizedCode) {
                filtered.push_back(conn);
            }
        }
        
        graph.insert(nodeCode, filtered);
    }
    
    return true;
}

// Obtener centro por código
DistributionCenter* DistributionCenterManager::getCenter(const string& code) {
    string normalizedCode = normalizeCode(code);
    return centersByCode.find(normalizedCode);
}

// Verificar si existe el centro
bool DistributionCenterManager::centerExists(const string& code) const {
    string normalizedCode = normalizeCode(code);
    return centersByCode.contains(normalizedCode);
}

// Mostrar información de un centro
void DistributionCenterManager::displayCenter(const string& code) const {
    string normalizedCode = normalizeCode(code);
    DistributionCenter* center = const_cast<HashTable<string, DistributionCenter>*>(&centersByCode)->find(normalizedCode);
    
    if (center) {
        center->display();
    } else {
        cout << "Centro '" << code << "' no encontrado." << endl;
    }
}

// Mostrar todos los centros
void DistributionCenterManager::displayAllCenters() const {
    auto allCenters = centersByCode.getAll();
    
    if (allCenters.empty()) {
        cout << "No hay centros registrados." << endl;
        return;
    }
    
    cout << "\n=== TODOS LOS CENTROS ===" << endl;
    for (const auto& pair : allCenters) {
        pair.second.display();
        cout << endl;
    }
}

// Listar centros ordenados por criterio
vector<DistributionCenter> DistributionCenterManager::listCentersSortedBy(SortCriterion criterion) const {
    vector<DistributionCenter> centers;
    
    auto allCenters = centersByCode.getAll();
    centers.reserve(allCenters.size());
    
    for (const auto& pair : allCenters) {
        centers.push_back(pair.second);
    }
    
    switch (criterion) {
        case SortCriterion::CAPACITY:
            sort(centers.begin(), centers.end(),
                [](const DistributionCenter& a, const DistributionCenter& b) {
                    return a.getCapacity() > b.getCapacity();
                });
            cout << "\n=== Centros ordenados por CAPACIDAD ===" << endl;
            break;
            
        case SortCriterion::DAILY_PACKAGES:
            sort(centers.begin(), centers.end(),
                [](const DistributionCenter& a, const DistributionCenter& b) {
                    return a.getDailyPackages() > b.getDailyPackages();
                });
            cout << "\n=== Centros ordenados por PAQUETES DIARIOS ===" << endl;
            break;
            
        case SortCriterion::EMPLOYEES:
            sort(centers.begin(), centers.end(),
                [](const DistributionCenter& a, const DistributionCenter& b) {
                    return a.getEmployeeCount() > b.getEmployeeCount();
                });
            cout << "\n=== Centros ordenados por EMPLEADOS ===" << endl;
            break;
    }
    
    for (const auto& center : centers) {
        cout << center.getCode() << " | " << center.getName() 
             << " | Cap: " << center.getCapacity()
             << " | Paq: " << center.getDailyPackages()
             << " | Emp: " << center.getEmployeeCount() << endl;
    }
    
    return centers;
}

// Algoritmo de Dijkstra para camino más corto
pair<int, vector<string>> DistributionCenterManager::shortestPath(
    const string& origin, 
    const string& destination
) {
    string normOrigin = normalizeCode(origin);
    string normDest = normalizeCode(destination);
    
    if (!centerExists(normOrigin) || !centerExists(normDest)) {
        cerr << "Error: Uno o ambos centros no existen" << endl;
        return {-1, {}};
    }
    
    // Estructuras para Dijkstra
    HashTable<string, int> distances;
    HashTable<string, string> previous;
    HashTable<string, bool> visited;
    
    // Cola de prioridad: (distancia, nodo)
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;
    
    // Inicializar
    const int INF = numeric_limits<int>::max();
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
        
        if (currentNode == normDest) break;
        
        vector<pair<string, int>>* neighbors = graph.find(currentNode);
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
    
    // Verificar si existe camino
    int* finalDist = distances.find(normDest);
    if (!finalDist || *finalDist == INF) {
        cerr << "No existe camino entre " << origin << " y " << destination << endl;
        return {-1, {}};
    }
    
    // Reconstruir camino
    vector<string> path;
    string current = normDest;
    while (current != normOrigin) {
        path.push_back(current);
        string* prev = previous.find(current);
        if (!prev) break;
        current = *prev;
    }
    path.push_back(normOrigin);
    reverse(path.begin(), path.end());
    
    // Mostrar resultado
    cout << "\n=== CAMINO MÁS CORTO ===" << endl;
    cout << "Origen: " << normOrigin << endl;
    cout << "Destino: " << normDest << endl;
    cout << "Distancia total: " << *finalDist << " km" << endl;
    cout << "Ruta: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    return {*finalDist, path};
}

// Obtener total de centros
int DistributionCenterManager::getTotalCenters() const {
    return centersByCode.getSize();
}

// Imprimir estadísticas
void DistributionCenterManager::printStatistics() const {
    cout << "\n=== ESTADÍSTICAS ===" << endl;
    cout << "Total de centros: " << centersByCode.getSize() << endl;
    cout << "Total de conexiones: " << graph.getSize() << endl;
    cout << "Factor de carga: " << centersByCode.getLoadFactor() * 100 << "%" << endl;
    cout << "Capacidad: " << centersByCode.getCapacity() << endl;
}
