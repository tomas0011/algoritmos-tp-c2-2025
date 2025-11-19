#include "distributionCenterService.h"
#include "../../utils/algorithms/dijkstra/dijkstra.h"
#include "../../utils/algorithms/sort/mergeSort.h"
#include <iomanip>

DistributionCenterService::DistributionCenterService(List& centersList, List& centerManagersList)
    : distributionCenters(centersList), distributionCenterManagers(centerManagersList) {}

DistributionCenterService::~DistributionCenterService() {
    // No need to delete since we use references to storage
}

// Mostrar la informacion de un centro de distribucion especifico
void DistributionCenterService::showCenterInfo(const std::string& code) {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return false;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        
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
void DistributionCenterService::addPackageToCenter(const std::string& centerCode, const Package& pkg) {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        if (!manager->hasCenter(centerCode)) {
            std::cout << "Error: Centro con codigo '" << centerCode << "' no encontrado." << std::endl;
            return;
        }

        DistributionCenter* center = manager->getCenter(centerCode);
        if (center == nullptr) {
            std::cout << "Error al obtener el centro.\n";
            return;
        }

        // Validación simple: revisar capacidad (opcional)
        // Si querés que el centro no acepte más paquetes cuando supera capacity,
        // descomentá las siguientes líneas:
        /*
        if (center->getWarehouse().getSize() >= center->getCapacity()) {
            std::cout << "Imposible agregar paquete: centro alcanzó su capacidad máxima.\n";
            return;
        }
        */

        center->addPackage(pkg);
        std::cout << "Paquete (ID: " << pkg.getId() << ") agregado al centro " << centerCode << " correctamente.\n";
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

// Obtener el warehouse (lista de paquetes) de un centro por código
List DistributionCenterService::getWarehouseOfCenter(const std::string& centerCode) {
    List empty;

    if (distributionCenterManagers.isEmpty()) {
        std::cout << "[WARN] No hay DistributionCenterManagers cargados.\n";
        return empty;
    }

    try {
        DistributionCenterManager* manager =
            std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());

        if (!manager->hasCenter(centerCode)) {
            std::cout << "[WARN] El manager NO tiene un centro con codigo: " << centerCode << "\n";
            return empty;
        }

        DistributionCenter* center = manager->getCenter(centerCode);
        if (center == nullptr) {
            std::cout << "[WARN] getCenter devolvio nullptr para: " << centerCode << "\n";
            return empty;
        }

        List warehouse = center->getWarehouse();

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
    std::cout << "Funcion removeCenter no implementada." << std::endl;
    return false;
}

// Actualizar informacion de un centro
bool DistributionCenterService::updateCenter(const std::string& code, int capacity,
                                             int dailyPackages, int numEmployees) {
    std::cout << "Funcion updateCenter no implementada." << std::endl;
    return false;
}

// Mostrar todos los centros
void DistributionCenterService::displayAllCenters() {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        return manager->getDistributionCentersList();
    } catch (const std::bad_any_cast&) {
        return result;
    }
}

// Mostrar centros ordenados por capacidad
void DistributionCenterService::displayCentersSortedByCapacity() {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        return manager->getCenter(code);
    } catch (const std::bad_any_cast&) {
        return nullptr;
    }
}

// Mostrar estadisticas generales
void DistributionCenterService::displayStatistics() {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return false;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        
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
        manager->createConnection(origin, destination, distance);

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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return false;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        
        // Verificar que ambos centros existen
        if (!manager->hasCenter(origin)) {
            std::cout << "Error: Centro origen '" << origin << "' no encontrado." << std::endl;
            return false;
        }

        if (!manager->hasCenter(destination)) {
            std::cout << "Error: Centro destino '" << destination << "' no encontrado." << std::endl;
            return false;
        }

        // Agregar conexión bidireccional
        manager->createBidirectionalConnection(origin, destination, distance);

        std::cout << "Conexion agregada: " << origin << " <-> " << destination
                  << " (" << distance << " km)" << std::endl;
        return true;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

void DistributionCenterService::showCenterConnections(const std::string& code) {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
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
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        DijkstraGraphResult* result = dijkstra(manager->getNetwork(), origin, destination);
        displayPathGraph(result, origin, destination);
        delete result;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

void DistributionCenterService::calculateAllDistancesFrom(const std::string& origin) {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        DijkstraGraphResult* result = dijkstra(manager->getNetwork(), origin, ""); // destination vacío = calcular a todos
        displayDijkstraGraphResult(result, origin);
        delete result;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}