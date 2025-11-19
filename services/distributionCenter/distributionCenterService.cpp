#include "distributionCenterService.h"
#include "../../utils/algorithms/dijkstra/dijkstra.h"
#include <algorithm>
#include <iomanip>

DistributionCenterService::DistributionCenterService(List& centersList, List& centerManagersList)
    : distributionCenters(centersList), distributionCenterManagers(centerManagersList) {}

DistributionCenterService::~DistributionCenterService() {
    // No need to delete since we use references to storage
}

// Mostrar la informacion de un centro de distribucion especifico
void DistributionCenterService::showCenterInfo(const std::string& code) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    if (!distributionCenterManager.hasCenter(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return;
    }

    DistributionCenter* distributionCenterFound = distributionCenterManager.getCenter(code);
    distributionCenterFound->display();
}

// Agregar un nuevo centro
bool DistributionCenterService::addCenter(const std::string& code, const std::string& name,
                                           const std::string& city, int capacity,
                                           int dailyPackages, int numEmployees) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    if (distributionCenterManager.hasCenter(code)) {
        std::cout << "Error: Ya existe un centro con codigo '" << code << "'." << std::endl;
        return false;
    }
    distributionCenterManager.createDistributionCenter(code, name, city, capacity, dailyPackages, numEmployees);
    
    // Actualizar el manager en la lista
    List newList;
    newList.push(distributionCenterManager);
    Node* current = distributionCenterManagers.getHead()->getNext();
    while (current != nullptr) {
        newList.push(current->getData());
        current = current->getNext();
    }
    distributionCenterManagers = newList;
    
    std::cout << "Centro '" << code << "' agregado exitosamente." << std::endl;
    return true;
}

// Eliminar un centro existente
bool DistributionCenterService::removeCenter(const std::string& code) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    if (!distributionCenterManager.hasCenter(code)) {
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
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    if (!distributionCenterManager.hasCenter(code)) {
        std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
        return false;
    }

    // Update in graph
    DistributionCenter* distributionCenterFound = distributionCenterManager.getCenter(code);
    distributionCenterFound->setCapacity(capacity);
    distributionCenterFound->setDailyPackages(dailyPackages);
    distributionCenterFound->setNumEmployees(numEmployees);

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
    DistributionCenterManager distributionCenterManager =
        any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());

    int count = distributionCenterManager.getDistributionCentersCount();

    if (count == 0) {
        std::cout << "No hay centros de distribucion registrados.\n";
        return;
    }

    std::cout << "\n=== Todos los Centros de Distribucion ===\n";
    std::cout << "Total: " << count << " centros\n";
    std::cout << std::string(80, '-') << "\n";

    List codes = distributionCenterManager.getDistributionCentersCodes();
    Node* current = codes.getHead();

    while (current) {
        std::string code = any_cast<std::string>(current->getData());
        DistributionCenter* c = distributionCenterManager.getCenter(code);
        std::cout << c->toString() << "\n";
        current = current->getNext();
    }

    std::cout << std::string(80, '-') << "\n";
}



List DistributionCenterService::getAllCenters() {
    DistributionCenterManager manager =
        any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());

    List result;
    List codes = manager.getDistributionCentersCodes();

    Node* current = codes.getHead();

    while (current) {
        std::string code = any_cast<std::string>(current->getData());
        result.push(manager.getCenter(code));
        current = current->getNext();
    }

    return result;
}

// Mostrar centros ordenados por capacidad
void DistributionCenterService::displayCentersSortedByCapacity() {
    DistributionCenterManager manager =
        any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());

    if (manager.getDistributionCentersCount() == 0) {
        std::cout << "No hay centros registrados.\n";
        return;
    }

    List listCenters = getAllCenters();
    std::vector<DistributionCenter*> centers;

    Node* current = listCenters.getHead();
    while (current) {
        centers.push_back(any_cast<DistributionCenter*>(current->getData()));
        current = current->getNext();
    }

    std::sort(centers.begin(), centers.end(),
              [](DistributionCenter* a, DistributionCenter* b) {
                  return a->getCapacity() > b->getCapacity();
              });

    std::cout << "\n=== Centros Ordenados por Capacidad ===\n";

    for (auto* c : centers)
        std::cout << c->toString() << "\n";

    std::cout << std::string(80, '-') << "\n";
}

// Mostrar centros ordenados por paquetes procesados
void DistributionCenterService::displayCentersSortedByPackages() {
    DistributionCenterManager manager =
        any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());

    if (manager.getDistributionCentersCount() == 0) {
        std::cout << "No hay centros registrados.\n";
        return;
    }

    List listCenters = getAllCenters();
    std::vector<DistributionCenter*> centers;

    Node* current = listCenters.getHead();
    while (current) {
        centers.push_back(any_cast<DistributionCenter*>(current->getData()));
        current = current->getNext();
    }

    std::sort(centers.begin(), centers.end(),
              [](DistributionCenter* a, DistributionCenter* b) {
                  return a->getDailyPackages() > b->getDailyPackages();
              });

    std::cout << "\n=== Centros Ordenados por Paquetes ===\n";

    for (auto* c : centers)
        std::cout << c->toString() << "\n";

    std::cout << std::string(80, '-') << "\n";
}

// Mostrar centros ordenados por cantidad de empleados
void DistributionCenterService::displayCentersSortedByEmployees() {
    DistributionCenterManager manager =
        any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());

    if (manager.getDistributionCentersCount() == 0) {
        std::cout << "No hay centros registrados.\n";
        return;
    }

    List listCenters = getAllCenters();
    std::vector<DistributionCenter*> centers;

    Node* current = listCenters.getHead();
    while (current) {
        centers.push_back(any_cast<DistributionCenter*>(current->getData()));
        current = current->getNext();
    }

    std::sort(centers.begin(), centers.end(),
              [](DistributionCenter* a, DistributionCenter* b) {
                  return a->getNumEmployees() > b->getNumEmployees();
              });

    std::cout << "\n=== Centros Ordenados por Empleados ===\n";

    for (auto* c : centers)
        std::cout << c->toString() << "\n";

    std::cout << std::string(80, '-') << "\n";
}


// Verificar si un centro existe
bool DistributionCenterService::centerExists(const std::string& code) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    return distributionCenterManager.hasCenter(code);
}

// Obtener un centro por codigo
DistributionCenter* DistributionCenterService::getCenter(const std::string& code) {
    // This function returns a pointer to a temporary object
    // Return nullptr to avoid crash - needs architectural redesign
    return nullptr;
}

// Mostrar estadisticas generales
void DistributionCenterService::displayStatistics() {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    if (distributionCenterManager.getDistributionCentersCount() == 0) {
        std::cout << "No hay centros de distribucion registrados." << std::endl;
        return;
    }

    const std::vector<DistributionCenter>& centersList = distributionCenterManager.getDistributionCenters();

    int totalCapacity = 0;
    int totalPackages = 0;
    int totalEmployees = 0;

    for (const auto& center : centersList) {
        totalCapacity += center.getCapacity();
        totalPackages += center.getDailyPackages();
        totalEmployees += center.getNumEmployees();
    }

    std::cout << "\n=== Estadisticas de Centros de Distribucion ===" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Total de centros: " << distributionCenterManager.getDistributionCentersCount() << std::endl;
    std::cout << "Capacidad total: " << totalCapacity << " paquetes" << std::endl;
    std::cout << "Paquetes diarios totales: " << totalPackages << std::endl;
    std::cout << "Empleados totales: " << totalEmployees << std::endl;
    std::cout << "\nPromedios:" << std::endl;
    std::cout << "  Capacidad promedio: " << (totalCapacity / distributionCenterManager.getDistributionCentersCount()) << " paquetes/centro" << std::endl;
    std::cout << "  Paquetes diarios promedio: " << (totalPackages / distributionCenterManager.getDistributionCentersCount()) << " paquetes/centro" << std::endl;
    std::cout << "  Empleados promedio: " << (totalEmployees / distributionCenterManager.getDistributionCentersCount()) << " empleados/centro" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Mostrar estadisticas del GraphHashTable
    std::cout << "\nEstadisticas de GraphHashTable:" << std::endl;
    distributionCenterManager.displayStatistics();
}

// === Gestion de Conexiones ===

bool DistributionCenterService::addConnection(const std::string& origin,
                                              const std::string& destination,
                                              double distance) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    // Verificar que ambos centros existen
    if (!distributionCenterManager.hasCenter(origin)) {
        std::cout << "Error: Centro origen '" << origin << "' no encontrado." << std::endl;
        return false;
    }

    if (!distributionCenterManager.hasCenter(destination)) {
        std::cout << "Error: Centro destino '" << destination << "' no encontrado." << std::endl;
        return false;
    }

    // Agregar conexion bidireccional usando el grafo
    distributionCenterManager.relateDistributionCenter(origin, destination, distance);
    distributionCenterManager.relateDistributionCenter(destination, origin, distance);

    // Actualizar el manager en la lista
    List newList;
    newList.push(distributionCenterManager);
    Node* current = distributionCenterManagers.getHead()->getNext();
    while (current != nullptr) {
        newList.push(current->getData());
        current = current->getNext();
    }
    distributionCenterManagers = newList;

    std::cout << "Conexion agregada: " << origin << " <-> " << destination
              << " (" << distance << " km)" << std::endl;
    return true;
}

void DistributionCenterService::showCenterConnections(const std::string& code) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    if (!distributionCenterManager.hasCenter(code)) {
        std::cout << "Error: Centro '" << code << "' no encontrado." << std::endl;
        return;
    }

    std::cout << "\n=== Conexiones del Centro " << code << " ===" << std::endl;

    List* edges = distributionCenterManager.getConnections(code);
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
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    std::cout << "\n=== Todas las Conexiones ===" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    List allCodes = distributionCenterManager.getDistributionCentersCodes();
    Node* centerNode = allCodes.getHead();
    bool hasConnections = false;

    while (centerNode != nullptr) {
        std::string code = any_cast<std::string>(centerNode->getData());
        List* edges = distributionCenterManager.getConnections(code);

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

// === Algoritmo de Dijkstra ===

void DistributionCenterService::calculateShortestPath(const std::string& origin,
                                                       const std::string& destination) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    DijkstraGraphResult* result = dijkstra(distributionCenterManager.getNetwork(), origin, destination);
    displayPathGraph(result, origin, destination);
    delete result;
}

void DistributionCenterService::calculateAllDistancesFrom(const std::string& origin) {
    DistributionCenterManager distributionCenterManager = any_cast<DistributionCenterManager>(distributionCenterManagers.getHead()->getData());
    DijkstraGraphResult* result = dijkstra(distributionCenterManager.getNetwork(), origin, ""); // destination vacío = calcular a todos
    displayDijkstraGraphResult(result, origin);
    delete result;
}

