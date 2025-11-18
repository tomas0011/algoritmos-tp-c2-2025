#include "distributionCenterService.h"
#include "../../utils/algorithms/dijkstra/dijkstra.h"
#include <algorithm>
#include <iomanip>

DistributionCenterService::DistributionCenterService(List& centersList, GraphHashTable& network)
    : distributionCenters(centersList), distributionNetwork(network) {}

DistributionCenterService::~DistributionCenterService() {
    // No need to delete since we use references to storage
}

// Mostrar la informacion de un centro de distribucion especifico
void DistributionCenterService::showCenterInfo(const std::string& code) {
    if (!distributionNetwork.hasNode(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return;
    }

    HashGraphNode* node = distributionNetwork.getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
    center->display();
}

// Agregar un nuevo centro
bool DistributionCenterService::addCenter(const std::string& code, const std::string& name,
                                          const std::string& city, int capacity,
                                          int dailyPackages, int numEmployees) {
    if (distributionNetwork.hasNode(code)) {
        std::cout << "Error: Ya existe un centro con codigo '" << code << "'." << std::endl;
        return false;
    }

    DistributionCenter* newCenter = new DistributionCenter(
        code, name, city, capacity, dailyPackages, numEmployees
    );

    distributionCenters.push(*newCenter);  // Add to storage list
    distributionNetwork.addNode(code, newCenter);
    std::cout << "Centro '" << code << "' agregado exitosamente." << std::endl;
    return true;
}

// Eliminar un centro existente
bool DistributionCenterService::removeCenter(const std::string& code) {
    if (!distributionNetwork.hasNode(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return false;
    }

    // Remove from list
    List newList;
    Node* current = distributionCenters.getHead();
    bool found = false;
    while (current != nullptr) {
        try {
            DistributionCenter center = std::any_cast<DistributionCenter>(current->getData());
            if (center.getCode() != code) {
                newList.push(center);
            } else {
                found = true;
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    if (found) {
        distributionCenters = newList;
    }

    // Note: GraphHashTable doesn't have removeNode implemented
    // The node remains in the graph but with invalid data
    std::cout << "Centro '" << code << "' eliminado exitosamente." << std::endl;
    std::cout << "Nota: El nodo permanece en el grafo." << std::endl;
    return true;
}

// Actualizar informacion de un centro
bool DistributionCenterService::updateCenter(const std::string& code, int capacity,
                                             int dailyPackages, int numEmployees) {
    if (!distributionNetwork.hasNode(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return false;
    }

    // Update in graph
    HashGraphNode* node = distributionNetwork.getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
    center->setCapacity(capacity);
    center->setDailyPackages(dailyPackages);
    center->setNumEmployees(numEmployees);

    // Update in list
    List newList;
    Node* current = distributionCenters.getHead();
    while (current != nullptr) {
        try {
            DistributionCenter c = std::any_cast<DistributionCenter>(current->getData());
            if (c.getCode() == code) {
                c.setCapacity(capacity);
                c.setDailyPackages(dailyPackages);
                c.setNumEmployees(numEmployees);
                newList.push(c);
            } else {
                newList.push(c);
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    distributionCenters = newList;

    std::cout << " Centro '" << code << "' actualizado exitosamente." << std::endl;
    return true;
}

// Mostrar todos los centros
void DistributionCenterService::displayAllCenters() {
    if (distributionNetwork.getNodeCount() == 0) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }

    std::cout << "\n=== Todos los Centros de Distribucion ===" << std::endl;
    std::cout << "Total: " << distributionNetwork.getNodeCount() << " centros" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    List allCodes = distributionNetwork.getNodeCodes();
    Node* current = allCodes.getHead();

    while (current != nullptr) {
        std::string code = any_cast<std::string>(current->getData());
        HashGraphNode* node = distributionNetwork.getNode(code);
        DistributionCenter* center = any_cast<DistributionCenter*>(node->getData());
        std::cout << center->toString() << std::endl;
        current = current->getNext();
    }
    std::cout << std::string(80, '-') << std::endl;
}

// Obtener todos los centros como vector
std::vector<DistributionCenter*> DistributionCenterService::getAllCenters() {
    std::vector<DistributionCenter*> result;

    List allCodes = distributionNetwork.getNodeCodes();
    Node* current = allCodes.getHead();

    while (current != nullptr) {
        std::string code = any_cast<std::string>(current->getData());
        HashGraphNode* node = distributionNetwork.getNode(code);
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
    return distributionNetwork.hasNode(code);
}

// Obtener un centro por codigo
DistributionCenter* DistributionCenterService::getCenter(const std::string& code) {
    if (!distributionNetwork.hasNode(code)) {
        return nullptr;
    }
    return any_cast<DistributionCenter*>(distributionNetwork.getNode(code)->getData());
}

// Mostrar estadisticas generales
void DistributionCenterService::displayStatistics() {
    if (distributionNetwork.getNodeCount() == 0) {
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
    std::cout << "Total de centros: " << distributionNetwork.getNodeCount() << std::endl;
    std::cout << "Capacidad total: " << totalCapacity << " paquetes" << std::endl;
    std::cout << "Paquetes diarios totales: " << totalPackages << std::endl;
    std::cout << "Empleados totales: " << totalEmployees << std::endl;
    std::cout << "\nPromedios:" << std::endl;
    std::cout << "  Capacidad promedio: " << (totalCapacity / distributionNetwork.getNodeCount()) << " paquetes/centro" << std::endl;
    std::cout << "  Paquetes diarios promedio: " << (totalPackages / distributionNetwork.getNodeCount()) << " paquetes/centro" << std::endl;
    std::cout << "  Empleados promedio: " << (totalEmployees / distributionNetwork.getNodeCount()) << " empleados/centro" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Mostrar estadisticas del GraphHashTable
    std::cout << "\nEstadisticas de GraphHashTable:" << std::endl;
    distributionNetwork.displayStatistics();
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

    std::cout << " " << distributionNetwork.getNodeCount() << " centros cargados exitosamente." << std::endl;
}



// === Gestion de Conexiones ===

bool DistributionCenterService::addConnection(const std::string& origin,
                                              const std::string& destination,
                                              double distance) {
    // Verificar que ambos centros existen
    if (!distributionNetwork.hasNode(origin)) {
        std::cout << "Error: Centro origen '" << origin << "' no encontrado." << std::endl;
        return false;
    }

    if (!distributionNetwork.hasNode(destination)) {
        std::cout << "Error: Centro destino '" << destination << "' no encontrado." << std::endl;
        return false;
    }

    // Agregar conexion bidireccional usando el grafo
    distributionNetwork.addArista(origin, destination, distance);
    distributionNetwork.addArista(destination, origin, distance);

    std::cout << "Conexion agregada: " << origin << " <-> " << destination
              << " (" << distance << " km)" << std::endl;
    return true;
}

void DistributionCenterService::showCenterConnections(const std::string& code) {
    if (!distributionNetwork.hasNode(code)) {
        std::cout << "Error: Centro '" << code << "' no encontrado." << std::endl;
        return;
    }

    std::cout << "\n=== Conexiones del Centro " << code << " ===" << std::endl;

    List* edges = distributionNetwork.getAristas(code);
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

    List allCodes = distributionNetwork.getNodeCodes();
    Node* centerNode = allCodes.getHead();
    bool hasConnections = false;

    while (centerNode != nullptr) {
        std::string code = any_cast<std::string>(centerNode->getData());
        List* edges = distributionNetwork.getAristas(code);

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
    DijkstraGraphResult* result = dijkstra(distributionNetwork, origin, destination);
    displayPathGraph(result, origin, destination);
    delete result;
}

void DistributionCenterService::calculateAllDistancesFrom(const std::string& origin) {
    DijkstraGraphResult* result = dijkstra(distributionNetwork, origin, ""); // destination vacío = calcular a todos
    displayDijkstraGraphResult(result, origin);
    delete result;
}

