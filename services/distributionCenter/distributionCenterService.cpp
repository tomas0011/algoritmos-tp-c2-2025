#include "distributionCenterService.h"
#include "../../utils/algorithms/dijkstra/dijkstra.h"
#include "../../utils/algorithms/sort/mergeSort.h"
#include <iomanip>

DistributionCenterService::DistributionCenterService(
    ConnectionService* connectionService,
    PackageService* packageService,
    DistributionCenterManager* manager,
    List& centersList,
    List& centerManagersList)
    : connectionService(connectionService),
    packageService(packageService),
    manager(manager),
    distributionCenters(centersList),
    distributionCenterManagers(centerManagersList) {}

DistributionCenterService::~DistributionCenterService() {
    // No need to delete since we use references to storage
}

// Mostrar la informacion de un centro de distribucion especifico
void DistributionCenterService::showCenterInfo(const std::string& code) {
    try {
        if (!manager->hasCenter(code)) {
            std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
            return;
        }

        DistributionCenter* distributionCenterFound = manager->getCenter(code);
        distributionCenterFound->display();
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// Agregar un nuevo centro
bool DistributionCenterService::addCenter(const std::string& code, const std::string& name,
                                           const std::string& city, int capacity,
                                           int dailyPackages, int numEmployees) {
    try {
        
        if (manager->hasCenter(code)) {
            std::cout << "Ya existe un centro con el codigo " << code << std::endl;
            return false;
        }

        manager->createDistributionCenter(code, name, city, capacity, dailyPackages, numEmployees);
        std::cout << "Centro agregado exitosamente." << std::endl;
        return true;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

// Agregar un paquete al almacén de un centro
void DistributionCenterService::addPackageToCenter(const std::string& centerCode, int id, const std::string& name, double price, int priority, double weight) {
    try {
        if (!manager->hasCenter(centerCode)) {
            std::cout << "Error: Centro con codigo '" << centerCode << "' no encontrado." << std::endl;
            return;
        }

        DistributionCenter* center = manager->getCenter(centerCode);
        if (center == nullptr) {
            std::cout << "Error al obtener el centro.\n";
            return;
        }

        packageService->createPackage(id, name, price, priority, weight);
        std::cout << "Paquete (ID: " << id << ") agregado al centro " << centerCode << " correctamente.\n";
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// Obtener el warehouse (lista de paquetes) de un centro por código
List DistributionCenterService::getWarehouseOfCenter(const std::string& centerCode) {
    List empty;
    try {
        List& warehouse = packageService->getPackagesOfCenter(centerCode);

        if (warehouse.isEmpty()) {
            std::cout << "[INFO] El centro " << centerCode << " tiene el warehouse vacio.\n";
        } else {
            std::cout << "[INFO] Warehouse del centro " << centerCode 
                      << " contiene " << warehouse.getSize() << " paquetes.\n";
        }
        return warehouse;
    } catch (const std::bad_any_cast&) {
        std::cout << "[ERROR] Fallo el any_cast a DistributionCenterManager*.\n";
        return empty;
    }
}

// Eliminar un centro existente
bool DistributionCenterService::removeCenter(const std::string& code) {
    try {
        if (!manager->hasCenter(code)) {
            std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
            return false;
        }

        std::cout << "Eliminando centro '" << code << "' y todas sus conexiones..." << std::endl;
        
        // 1. Eliminar todas las conexiones que involucran este centro del ConnectionService
        int connectionsRemoved = 0;
        if (connectionService) {
            connectionService->deleteConnectionsByCenter(code);
            std::cout << "  - Conexiones eliminadas del ConnectionService" << std::endl;
        }

        // 2. Eliminar aristas del grafo (salientes y entrantes)
        // Primero eliminamos las aristas salientes del centro a eliminar
        List* outgoingEdges = manager->getConnections(code);
        if (outgoingEdges && outgoingEdges->getSize() > 0) {
            connectionsRemoved += outgoingEdges->getSize();
        }
        
        // Eliminar aristas entrantes (de otros centros hacia este)
        List allCentersCodes = manager->getDistributionCentersCodes();
        Node* codeNode = allCentersCodes.getHead();
        while (codeNode != nullptr) {
            try {
                std::string otherCode = std::any_cast<std::string>(codeNode->getData());
                if (otherCode != code) {
                    // Verificar si hay aristas desde otherCode hacia code
                    List* edges = manager->getConnections(otherCode);
                    if (edges) {
                        Node* edgeNode = edges->getHead();
                        while (edgeNode != nullptr) {
                            try {
                                Arista* arista = std::any_cast<Arista*>(edgeNode->getData());
                                if (arista->destino == code) {
                                    connectionsRemoved++;
                                }
                            } catch (const std::bad_any_cast&) {}
                            edgeNode = edgeNode->getNext();
                        }
                    }
                }
            } catch (const std::bad_any_cast&) {}
            codeNode = codeNode->getNext();
        }
        
        // 3. Obtener la lista de centros y buscar el centro a eliminar
        List& centersList = manager->getDistributionCentersList();
        
        Node* current = centersList.getHead();
        Node* previous = nullptr;
        bool found = false;
        
        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                if (center->getCode() == code) {
                    // Eliminar el nodo de la lista
                    if (previous == nullptr) {
                        // Es el primer nodo
                        centersList.setHead(current->getNext());
                    } else {
                        previous->setNext(current->getNext());
                    }
                    
                    // Liberar la memoria del centro
                    delete center;
                    delete current;
                    found = true;
                    
                    break;
                }
                previous = current;
                current = current->getNext();
            } catch (const std::bad_any_cast&) {
                previous = current;
                current = current->getNext();
            }
        }
        
        if (found) {
            std::cout << "\nCentro '" << code << "' y sus conexiones fueron eliminados correctamente" << std::endl;
        }
        
        return found;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

// Actualizar informacion de un centro
bool DistributionCenterService::updateCenter(const std::string& code, int capacity,
                                             int dailyPackages, int numEmployees) {
    try {
        if (!manager->hasCenter(code)) {
            std::cout << "Error: Centro con codigo '" << code << "' no encontrado." << std::endl;
            return false;
        }

        // Obtener el centro
        DistributionCenter* center = manager->getCenter(code);
        if (center == nullptr) {
            std::cout << "Error al obtener el centro." << std::endl;
            return false;
        }

        // Actualizar los valores
        center->setCapacity(capacity);
        center->setDailyPackages(dailyPackages);
        center->setNumEmployees(numEmployees);

        std::cout << "Centro '" << code << "' actualizado exitosamente." << std::endl;
        std::cout << "  - Capacidad: " << capacity << std::endl;
        std::cout << "  - Paquetes diarios: " << dailyPackages << std::endl;
        std::cout << "  - Empleados: " << numEmployees << std::endl;
        
        return true;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

// Mostrar todos los centros
void DistributionCenterService::displayAllCenters() {
    try {
        List& centersList = manager->getDistributionCentersList();

        if (centersList.isEmpty()) {
            std::cout << "No hay centros registrados.\n";
            return;
        }

        std::cout << "\n=== Todos los Centros de Distribucion ===\n";
        std::cout << std::string(80, '-') << "\n";

        Node* current = centersList.getHead();
        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                center->display();
                std::cout << std::string(80, '-') << "\n";
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}



List DistributionCenterService::getAllCenters() {
    List result;
    
    if (distributionCenterManagers.isEmpty()) {
        return result;
    }

    try {
        return manager->getDistributionCentersList();
    } catch (const std::bad_any_cast&) {
        return result;
    }
}

// Mostrar centros ordenados por capacidad
void DistributionCenterService::displayCentersSortedByCapacity() {
    try {
        List& centersList = manager->getDistributionCentersList();

        if (centersList.isEmpty()) {
            std::cout << "No hay centros registrados.\n";
            return;
        }

        std::cout << "\n=== Centros Ordenados por Capacidad ===\n";

        // Use custom mergeSort with lambda comparator
        List sortedCenters = mergeSort(centersList, [](const std::any& a, const std::any& b) -> bool {
            try {
                DistributionCenter* centerA = std::any_cast<DistributionCenter*>(a);
                DistributionCenter* centerB = std::any_cast<DistributionCenter*>(b);
                return centerA->getCapacity() < centerB->getCapacity();
            } catch (const std::bad_any_cast&) {
                return false;
            }
        });

        // Display sorted centers
        Node* current = sortedCenters.getHead();
        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                center->display();
                std::cout << std::string(80, '-') << "\n";
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// Mostrar centros ordenados por paquetes procesados
void DistributionCenterService::displayCentersSortedByPackages() {
    try {
        List& centersList = manager->getDistributionCentersList();

        if (centersList.isEmpty()) {
            std::cout << "No hay centros registrados.\n";
            return;
        }

        std::cout << "\n=== Centros Ordenados por Paquetes Diarios ===\n";

        // Use custom mergeSort with lambda comparator
        List sortedCenters = mergeSort(centersList, [](const std::any& a, const std::any& b) -> bool {
            try {
                DistributionCenter* centerA = std::any_cast<DistributionCenter*>(a);
                DistributionCenter* centerB = std::any_cast<DistributionCenter*>(b);
                return centerA->getDailyPackages() < centerB->getDailyPackages();
            } catch (const std::bad_any_cast&) {
                return false;
            }
        });

        // Display sorted centers
        Node* current = sortedCenters.getHead();
        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                center->display();
                std::cout << std::string(80, '-') << "\n";
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// Mostrar centros ordenados por cantidad de empleados
void DistributionCenterService::displayCentersSortedByEmployees() {
    try {
        List& centersList = manager->getDistributionCentersList();

        if (centersList.isEmpty()) {
            std::cout << "No hay centros registrados.\n";
            return;
        }

        std::cout << "\n=== Centros Ordenados por Empleados ===\n";

        // Use custom mergeSort with lambda comparator
        List sortedCenters = mergeSort(centersList, [](const std::any& a, const std::any& b) -> bool {
            try {
                DistributionCenter* centerA = std::any_cast<DistributionCenter*>(a);
                DistributionCenter* centerB = std::any_cast<DistributionCenter*>(b);
                return centerA->getNumEmployees() < centerB->getNumEmployees();
            } catch (const std::bad_any_cast&) {
                return false;
            }
        });

        // Display sorted centers
        Node* current = sortedCenters.getHead();
        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                center->display();
                std::cout << std::string(80, '-') << "\n";
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}


// Verificar si un centro existe
bool DistributionCenterService::centerExists(const std::string& code) {
    if (distributionCenterManagers.isEmpty()) {
        return false;
    }

    try {
        return manager->hasCenter(code);
    } catch (const std::bad_any_cast&) {
        return false;
    }
}

// Obtener un centro por codigo
DistributionCenter* DistributionCenterService::getCenter(const std::string& code) {
    if (distributionCenterManagers.isEmpty()) {
        return nullptr;
    }
    try {
        return manager->getCenter(code);
    } catch (const std::bad_any_cast&) {
        return nullptr;
    }
}

// Mostrar estadisticas generales
void DistributionCenterService::displayStatistics() {
    try {
        List& centersList = manager->getDistributionCentersList();

        if (centersList.isEmpty()) {
            std::cout << "No hay centros de distribucion registrados." << std::endl;
            return;
        }

        int totalCapacity = 0;
        int totalPackages = 0;
        int totalEmployees = 0;
        int count = 0;

        Node* current = centersList.getHead();
        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                totalCapacity += center->getCapacity();
                totalPackages += center->getDailyPackages();
                totalEmployees += center->getNumEmployees();
                count++;
            } catch (const std::bad_any_cast&) {}
            current = current->getNext();
        }

        if (count == 0) {
            std::cout << "No hay centros validos registrados." << std::endl;
            return;
        }

        std::cout << "\n=== Estadisticas de Centros de Distribucion ===" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "Total de centros: " << count << std::endl;
        std::cout << "Capacidad total: " << totalCapacity << " paquetes" << std::endl;
        std::cout << "Paquetes diarios totales: " << totalPackages << std::endl;
        std::cout << "Empleados totales: " << totalEmployees << std::endl;
        std::cout << "\nPromedios:" << std::endl;
        std::cout << "  Capacidad promedio: " << (totalCapacity / count) << " paquetes/centro" << std::endl;
        std::cout << "  Paquetes diarios promedio: " << (totalPackages / count) << " paquetes/centro" << std::endl;
        std::cout << "  Empleados promedio: " << (totalEmployees / count) << " empleados/centro" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        // Mostrar estadisticas del GraphHashTable
        std::cout << "\nEstadisticas de GraphHashTable:" << std::endl;
        manager->displayStatistics();
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// === Gestion de Conexiones ===

bool DistributionCenterService::addConnection(const std::string& origin,
                                              const std::string& destination,
                                              double distance) {
    try {
        
        // Verificar que ambos centros existen
        if (!manager->hasCenter(origin)) {
            std::cout << "Error: Centro origen '" << origin << "' no encontrado." << std::endl;
            return false;
        }

        if (!manager->hasCenter(destination)) {
            std::cout << "Error: Centro destino '" << destination << "' no encontrado." << std::endl;
            return false;
        }

        // Agregar conexión unidireccional
        connectionService->createConnection(origin, destination, distance);

        std::cout << "Conexion agregada: " << origin << " -> " << destination
                  << " (" << distance << " km)" << std::endl;
        return true;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

bool DistributionCenterService::addBidirectionalConnection(const std::string& origin,
                                                          const std::string& destination,
                                                          double distance) {
    try {
        
        // Verificar que ambos centros existen
        if (!manager->hasCenter(origin)) {
            std::cout << "Error: Centro origen '" << origin << "' no encontrado." << std::endl;
            return false;
        }

        if (!manager->hasCenter(destination)) {
            std::cout << "Error: Centro destino '" << destination << "' no encontrado." << std::endl;
            return false;
        }

        connectionService->createBidirectionalConnection(origin, destination, distance);
        std::cout << "Conexion bidireccional agregada: " << origin << " <-> " << destination
                  << " (" << distance << " km)" << std::endl;
        return true;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

void DistributionCenterService::showCenterConnections(const std::string& code) {
    try {
        if (!manager->hasCenter(code)) {
            std::cout << "Error: Centro '" << code << "' no encontrado." << std::endl;
            return;
        }

        std::cout << "\n=== Conexiones del Centro " << code << " ===" << std::endl;

        List* edges = manager->getConnections(code);
        if (!edges || edges->getSize() == 0) {
            std::cout << "Este centro no tiene conexiones." << std::endl;
            return;
        }

        Node* current = edges->getHead();
        int count = 0;

        while (current != nullptr) {
            try {
                Connection* conn = std::any_cast<Connection*>(current->getData());
                std::cout << "  " << code << " -> " << conn->getDistributionCenterDestination()
                          << " (" << conn->getDistance() << " km)" << std::endl;
            } catch (const std::bad_any_cast&) {
                std::cout << "  [conexion invalida]" << std::endl;
            }
            current = current->getNext();
            count++;
        }

        std::cout << "Total: " << count << " conexiones" << std::endl;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

void DistributionCenterService::displayAllConnections() {
    try {
        std::cout << "\n=== Todas las Conexiones ===" << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        List& centersList = manager->getDistributionCentersList();
        Node* centerNode = centersList.getHead();
        bool hasConnections = false;

        while (centerNode != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(centerNode->getData());
                std::string code = center->getCode();
                List* edges = manager->getConnections(code);

                if (edges && edges->getSize() > 0) {
                    hasConnections = true;
                    Node* edgeNode = edges->getHead();
                    while (edgeNode != nullptr) {
                        try {
                            Connection* conn = std::any_cast<Connection*>(edgeNode->getData());
                            std::cout << code << " -> " << conn->getDistributionCenterDestination()
                                      << " (" << conn->getDistance() << " km)" << std::endl;
                        } catch (const std::bad_any_cast&) {
                            std::cout << code << " -> [conexion invalida]" << std::endl;
                        }
                        edgeNode = edgeNode->getNext();
                    }
                }
            } catch (const std::bad_any_cast&) {}
            centerNode = centerNode->getNext();
        }

        if (!hasConnections) {
            std::cout << "No hay conexiones registradas." << std::endl;
        }

        std::cout << std::string(60, '-') << std::endl;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// === Algoritmo de Dijkstra ===

void DistributionCenterService::calculateShortestPath(const std::string& origin,
                                                       const std::string& destination) {
    try {
        DijkstraGraphResult* result = dijkstra(manager->getNetwork(), origin, destination);
        displayPathGraph(result, origin, destination);
        delete result;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

void DistributionCenterService::calculateAllDistancesFrom(const std::string& origin) {
    try {
        DijkstraGraphResult* result = dijkstra(manager->getNetwork(), origin, ""); // destination vacío = calcular a todos
        displayDijkstraGraphResult(result, origin);
        delete result;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}