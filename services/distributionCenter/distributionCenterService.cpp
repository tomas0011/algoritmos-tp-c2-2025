#include "distributionCenterService.h"
#include "../../utils/algorithms/dijkstra/dijkstra.h"
#include <algorithm>
#include <iomanip>

DistributionCenterService::DistributionCenterService() {
    redDistribucion = new GraphHashTable(23);  // Grafo con HashTable interna
}

DistributionCenterService::~DistributionCenterService() {
    // Limpiar memoria de todos los centros
    List allCodes = redDistribucion->getNodeCodes();
    Node* current = allCodes.getHead();
    while (current != nullptr) {
        std::string code = any_cast<std::string>(current->getData());
        HashGraphNode* node = redDistribucion->getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
        delete center;
        current = current->getNext();
    }
    delete redDistribucion;
}

// Mostrar la informacion de un centro de distribucion especifico
void DistributionCenterService::showCenterInfo(const std::string& code) {
    if (!redDistribucion->hasNode(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return;
    }
    
    HashGraphNode* node = redDistribucion->getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
    center->display();
}

// Agregar un nuevo centro
bool DistributionCenterService::addCenter(const std::string& code, const std::string& name,
                                          const std::string& city, int capacity,
                                          int dailyPackages, int numEmployees) {
    if (redDistribucion->hasNode(code)) {
        std::cout << "Error: Ya existe un centro con codigo '" << code << "'." << std::endl;
        return false;
    }
    
    DistributionCenter* newCenter = new DistributionCenter(
        code, name, city, capacity, dailyPackages, numEmployees
    );
    
    redDistribucion->addNode(code, newCenter);
    std::cout << "Centro '" << code << "' agregado exitosamente." << std::endl;
    return true;
}

// Eliminar un centro existente
bool DistributionCenterService::removeCenter(const std::string& code) {
    if (!redDistribucion->hasNode(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return false;
    }
    
    HashGraphNode* node = redDistribucion->getNode(code);
    DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
delete center;
// GraphHashTable no tiene removeNode implementado
// El nodo permanece en el grafo pero sin datos validos

std::cout << " Centro '" << code << "' eliminado exitosamente." << std::endl;
std::cout << "Nota: El nodo permanece en el grafo." << std::endl;
    return true;
}

// Actualizar informacion de un centro
bool DistributionCenterService::updateCenter(const std::string& code, int capacity,
                                             int dailyPackages, int numEmployees) {
    if (!redDistribucion->hasNode(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return false;
    }
    
    HashGraphNode* node = redDistribucion->getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
    center->setCapacity(capacity);
    center->setDailyPackages(dailyPackages);
    center->setNumEmployees(numEmployees);
    
    std::cout << " Centro '" << code << "' actualizado exitosamente." << std::endl;
    return true;
}

// Mostrar todos los centros
void DistributionCenterService::displayAllCenters() {
    if (redDistribucion->getNodeCount() == 0) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }
    
    std::cout << "\n=== Todos los Centros de Distribucion ===" << std::endl;
    std::cout << "Total: " << redDistribucion->getNodeCount() << " centros" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    List allCodes = redDistribucion->getNodeCodes();
    Node* current = allCodes.getHead();
    
    while (current != nullptr) {
        std::string code = any_cast<std::string>(current->getData());
        HashGraphNode* node = redDistribucion->getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
        std::cout << center->toString() << std::endl;
        current = current->getNext();
    }
    std::cout << std::string(80, '-') << std::endl;
}

// Obtener todos los centros como vector
std::vector<DistributionCenter*> DistributionCenterService::getAllCenters() {
    std::vector<DistributionCenter*> result;
    
    List allCodes = redDistribucion->getNodeCodes();
    Node* current = allCodes.getHead();
    
    while (current != nullptr) {
        std::string code = any_cast<std::string>(current->getData());
        HashGraphNode* node = redDistribucion->getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
        result.push_back(center);
        current = current->getNext();
    }
    
    return result;
}

// Mostrar centros ordenados por capacidad
void DistributionCenterService::displayCentersSortedByCapacity() {
    std::vector<DistributionCenter*> centersList = getAllCenters();
    
    if (centersList.empty()) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }
    
    // Ordenar por capacidad (descendente)
    std::sort(centersList.begin(), centersList.end(),
              [](DistributionCenter* a, DistributionCenter* b) {
                  return a->getCapacity() > b->getCapacity();
              });
    
    std::cout << "\n=== Centros Ordenados por Capacidad ===" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (auto* center : centersList) {
        std::cout << center->toString() << std::endl;
    }
    std::cout << std::string(80, '-') << std::endl;
}

// Mostrar centros ordenados por paquetes procesados
void DistributionCenterService::displayCentersSortedByPackages() {
    std::vector<DistributionCenter*> centersList = getAllCenters();
    
    if (centersList.empty()) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }
    
    // Ordenar por paquetes diarios (descendente)
    std::sort(centersList.begin(), centersList.end(),
              [](DistributionCenter* a, DistributionCenter* b) {
                  return a->getDailyPackages() > b->getDailyPackages();
              });
    
    std::cout << "\n=== Centros Ordenados por Paquetes Diarios ===" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (auto* center : centersList) {
        std::cout << center->toString() << std::endl;
    }
    std::cout << std::string(80, '-') << std::endl;
}

// Mostrar centros ordenados por cantidad de empleados
void DistributionCenterService::displayCentersSortedByEmployees() {
    std::vector<DistributionCenter*> centersList = getAllCenters();
    
    if (centersList.empty()) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }
    
    // Ordenar por número de empleados (descendente)
    std::sort(centersList.begin(), centersList.end(),
              [](DistributionCenter* a, DistributionCenter* b) {
                  return a->getNumEmployees() > b->getNumEmployees();
              });
    
    std::cout << "\n=== Centros Ordenados por Cantidad de Empleados ===" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (auto* center : centersList) {
        std::cout << center->toString() << std::endl;
    }
    std::cout << std::string(80, '-') << std::endl;
}

// Verificar si un centro existe
bool DistributionCenterService::centerExists(const std::string& code) {
    return redDistribucion->hasNode(code);
}

// Obtener un centro por codigo
DistributionCenter* DistributionCenterService::getCenter(const std::string& code) {
    if (!redDistribucion->hasNode(code)) {
        return nullptr;
    }
    return any_cast<DistributionCenter*>(redDistribucion->getNode(code));
}

// Mostrar estadisticas generales
void DistributionCenterService::displayStatistics() {
    if (redDistribucion->getNodeCount() == 0) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }
    
    std::vector<DistributionCenter*> centersList = getAllCenters();
    
    int totalCapacity = 0;
    int totalPackages = 0;
    int totalEmployees = 0;
    
    for (auto* center : centersList) {
        totalCapacity += center->getCapacity();
        totalPackages += center->getDailyPackages();
        totalEmployees += center->getNumEmployees();
    }
    
    std::cout << "\n=== Estadisticas de Centros de Distribucion ===" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Total de centros: " << redDistribucion->getNodeCount() << std::endl;
    std::cout << "Capacidad total: " << totalCapacity << " paquetes" << std::endl;
    std::cout << "Paquetes diarios totales: " << totalPackages << std::endl;
    std::cout << "Empleados totales: " << totalEmployees << std::endl;
    std::cout << "\nPromedios:" << std::endl;
    std::cout << "  Capacidad promedio: " << (totalCapacity / redDistribucion->getNodeCount()) << " paquetes/centro" << std::endl;
    std::cout << "  Paquetes diarios promedio: " << (totalPackages / redDistribucion->getNodeCount()) << " paquetes/centro" << std::endl;
    std::cout << "  Empleados promedio: " << (totalEmployees / redDistribucion->getNodeCount()) << " empleados/centro" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    // Mostrar estadisticas del GraphHashTable
    std::cout << "\nEstadisticas de GraphHashTable:" << std::endl;
    redDistribucion->displayStatistics();
}

// Cargar centros de ejemplo (mock data)
void DistributionCenterService::loadMockCenters() {
    std::cout << "Cargando centros de distribucion de ejemplo..." << std::endl;
    
    addCenter("CBA", "CentroCordoba", "Cordoba", 5000, 2000, 120);
    addCenter("MZA", "CentroMendoza", "Mendoza", 3000, 1200, 80);
    addCenter("BUE", "CentroBuenosAires", "Buenos Aires", 8000, 5000, 200);
    addCenter("ROS", "CentroRosario", "Rosario", 4000, 1800, 100);
    addCenter("TUC", "CentroTucuman", "Tucuman", 2500, 900, 60);
    addCenter("SLA", "CentroSalta", "Salta", 2000, 800, 50);
    
    std::cout << " " << redDistribucion->getNodeCount() << " centros cargados exitosamente." << std::endl;
}



// === Gestion de Conexiones ===

bool DistributionCenterService::addConnection(const std::string& origin,
                                              const std::string& destination,
                                              double distance) {
    // Verificar que ambos centros existen
    if (!redDistribucion->hasNode(origin)) {
        std::cout << "Error: Centro origen '" << origin << "' no encontrado." << std::endl;
        return false;
    }
    
    if (!redDistribucion->hasNode(destination)) {
        std::cout << "Error: Centro destino '" << destination << "' no encontrado." << std::endl;
        return false;
    }
    
    // Agregar conexion bidireccional usando el grafo
    redDistribucion->addArista(origin, destination, distance);
    redDistribucion->addArista(destination, origin, distance);
    
    std::cout << "Conexion agregada: " << origin << " <-> " << destination
              << " (" << distance << " km)" << std::endl;
    return true;
}

void DistributionCenterService::showCenterConnections(const std::string& code) {
    if (!redDistribucion->hasNode(code)) {
        std::cout << "Error: Centro '" << code << "' no encontrado." << std::endl;
        return;
    }
    
    std::cout << "\n=== Conexiones del Centro " << code << " ===" << std::endl;
    
    List* edges = redDistribucion->getAristas(code);
    if (!edges || edges->getSize() == 0) {
        std::cout << "Este centro no tiene conexiones." << std::endl;
        return;
    }
    
    Node* current = edges->getHead();
    int count = 0;
    
    while (current != nullptr) {
        GraphArista* edge = any_cast<GraphArista*>(current->getData());
        std::cout << "  " << code << " -> " << edge->getDestination()
                  << " (" << edge->getWeight() << " km)" << std::endl;
        current = current->getNext();
        count++;
    }
    
    std::cout << "Total: " << count << " conexiones" << std::endl;
}

void DistributionCenterService::displayAllConnections() {
    std::cout << "\n=== Todas las Conexiones ===" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    List allCodes = redDistribucion->getNodeCodes();
    Node* centerNode = allCodes.getHead();
    bool hasConnections = false;
    
    while (centerNode != nullptr) {
        std::string code = any_cast<std::string>(centerNode->getData());
        List* edges = redDistribucion->getAristas(code);
        
        if (edges && edges->getSize() > 0) {
            hasConnections = true;
            Node* edgeNode = edges->getHead();
            while (edgeNode != nullptr) {
                GraphArista* edge = any_cast<GraphArista*>(edgeNode->getData());
                std::cout << code << " -> " << edge->getDestination()
                          << " (" << edge->getWeight() << " km)" << std::endl;
                edgeNode = edgeNode->getNext();
            }
        }
        
        centerNode = centerNode->getNext();
    }
    
    if (!hasConnections) {
        std::cout << "No hay conexiones registradas." << std::endl;
    }
    
    std::cout << std::string(60, '-') << std::endl;
}

void DistributionCenterService::loadMockConnections() {
    std::cout << "Cargando conexiones de ejemplo..." << std::endl;
    
    // Conexiones según el enunciado y logica geografica de Argentina
    addConnection("CBA", "MZA", 900);   // Cordoba - Mendoza
    addConnection("CBA", "BUE", 700);   // Cordoba - Buenos Aires
    addConnection("CBA", "ROS", 400);   // Cordoba - Rosario
    addConnection("MZA", "BUE", 1100);  // Mendoza - Buenos Aires
    addConnection("BUE", "ROS", 300);   // Buenos Aires - Rosario
    addConnection("TUC", "CBA", 550);   // Tucuman - Cordoba
    addConnection("TUC", "SLA", 300);   // Tucuman - Salta
    addConnection("SLA", "CBA", 800);   // Salta - Cordoba
    
    std::cout << " Conexiones cargadas exitosamente." << std::endl;
}

// === Algoritmo de Dijkstra ===

void DistributionCenterService::calculateShortestPath(const std::string& origin,
                                                       const std::string& destination) {
    DijkstraGraphResult* result = dijkstra(*redDistribucion, origin, destination);
    displayPathGraph(result, origin, destination);
    delete result;
}

void DistributionCenterService::calculateAllDistancesFrom(const std::string& origin) {
    DijkstraGraphResult* result = dijkstra(*redDistribucion, origin, ""); // destination vacío = calcular a todos
    displayDijkstraGraphResult(result, origin);
    delete result;
}

