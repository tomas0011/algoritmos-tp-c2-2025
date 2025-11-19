#include "distributionCenterService.h"
#include "../../utils/algorithms/sort/mergeSort.cpp"
#include <iostream>
#include <string>

DistributionCenterService::DistributionCenterService(List& centersList, List& centerManagersList) 
    : distributionCenters(centersList), distributionCenterManagers(centerManagersList) {}

DistributionCenterService::~DistributionCenterService() {}

void DistributionCenterService::showCenterInfo(const std::string& code) {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        DistributionCenter* center = manager->getCenter(code);
        
        if (center != nullptr) {
            std::cout << "=== Informacion del Centro ===" << std::endl;
            center->display();
        } else {
            std::cout << "Centro con codigo " << code << " no encontrado." << std::endl;
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

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

bool DistributionCenterService::removeCenter(const std::string& code) {
    std::cout << "Funcion removeCenter no implementada." << std::endl;
    return false;
}

bool DistributionCenterService::updateCenter(const std::string& code, int capacity,
                                            int dailyPackages, int numEmployees) {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return false;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        DistributionCenter* center = manager->getCenter(code);
        
        if (center != nullptr) {
            center->setCapacity(capacity);
            center->setDailyPackages(dailyPackages);
            center->setNumEmployees(numEmployees);
            std::cout << "Centro actualizado exitosamente." << std::endl;
            return true;
        } else {
            std::cout << "Centro con codigo " << code << " no encontrado." << std::endl;
            return false;
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
        return false;
    }
}

void DistributionCenterService::displayAllCenters() {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        int count = manager->getDistributionCentersCount();

        if (count == 0) {
            std::cout << "No hay centros de distribucion registrados.\n";
            return;
        }

        std::cout << "\n=== Todos los Centros de Distribucion ===\n";
        std::cout << "Total: " << count << " centros\n";
        std::cout << std::string(80, '-') << "\n";

        List& centersList = manager->getDistributionCentersList();
        Node* current = centersList.getHead();

        while (current != nullptr) {
            try {
                DistributionCenter* center = std::any_cast<DistributionCenter*>(current->getData());
                center->display();
                std::cout << std::string(80, '-') << "\n";
            } catch (const std::bad_any_cast&) {
                std::cout << "Error al mostrar centro" << std::endl;
            }
            current = current->getNext();
        }
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

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
        mergeSort(centersList, [](const std::any& a, const std::any& b) -> bool {
            try {
                DistributionCenter* centerA = std::any_cast<DistributionCenter*>(a);
                DistributionCenter* centerB = std::any_cast<DistributionCenter*>(b);
                return centerA->getCapacity() < centerB->getCapacity();
            } catch (const std::bad_any_cast&) {
                return false;
            }
        });

        // Display sorted centers
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

void DistributionCenterService::displayCentersSortedByPackages() {
    std::cout << "Funcion displayCentersSortedByPackages no completamente implementada." << std::endl;
}

void DistributionCenterService::displayCentersSortedByEmployees() {
    std::cout << "Funcion displayCentersSortedByEmployees no completamente implementada." << std::endl;
}

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

void DistributionCenterService::displayStatistics() {
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        manager->displayStatistics();
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

void DistributionCenterService::loadMockCenters() {
    std::cout << "Cargando centros de prueba..." << std::endl;
    
    if (distributionCenterManagers.isEmpty()) {
        std::cout << "No hay gestores de centros disponibles.\n";
        return;
    }

    try {
        DistributionCenterManager* manager = std::any_cast<DistributionCenterManager*>(distributionCenterManagers.getHead()->getData());
        
        // Create some test centers
        manager->createDistributionCenter("BUE", "Buenos Aires", "Buenos Aires", 1000, 50, 20);
        manager->createDistributionCenter("MZA", "Mendoza", "Mendoza", 800, 30, 15);
        manager->createDistributionCenter("CBA", "Cordoba", "Cordoba", 600, 40, 18);
        
        std::cout << "Centros de prueba cargados exitosamente." << std::endl;
    } catch (const std::bad_any_cast&) {
        std::cout << "Error al acceder al gestor de centros." << std::endl;
    }
}

bool DistributionCenterService::addConnection(const std::string& origin, const std::string& destination, double distance) {
    std::cout << "Funcion addConnection no implementada." << std::endl;
    return false;
}

void DistributionCenterService::showCenterConnections(const std::string& code) {
    std::cout << "Funcion showCenterConnections no implementada." << std::endl;
}

void DistributionCenterService::displayAllConnections() {
    std::cout << "Funcion displayAllConnections no implementada." << std::endl;
}

void DistributionCenterService::calculateShortestPath(const std::string& origin, const std::string& destination) {
    std::cout << "Funcion calculateShortestPath no implementada." << std::endl;
}

void DistributionCenterService::calculateAllDistancesFrom(const std::string& origin) {
    std::cout << "Funcion calculateAllDistancesFrom no implementada." << std::endl;
}

