#include "connectionService.h"
#include "../../storage/storage.h"
#include "../../entities/distributionCenter/DistributionCenter.h"
#include "../../entities/distributionCenterManager/DistributionCenterManager.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Inicializar el contador estático
int ConnectionService::nextId = 1;

ConnectionService::ConnectionService(
    DistributionCenterManager* manager,
    List& connectionsList)
    : manager(manager),
    connections(connectionsList) {}

int ConnectionService::generateNextId() {
    // Buscar el ID más alto existente y generar el siguiente
    int maxId = 0;
    Node* current = connections.getHead();
    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            if (conn.getId() > maxId) {
                maxId = conn.getId();
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    
    // Usar el mayor entre nextId y maxId + 1
    nextId = std::max(nextId, maxId + 1);
    return nextId++;
}

bool ConnectionService::centerExists(const std::string& centerCode) {    
    try {
        if (manager) {
            return manager->hasCenter(centerCode);
        }
    } catch (const std::bad_any_cast& e) {
        // Manager no encontrado o inválido
    }
    
    return false;
}

bool ConnectionService::centerExists(const std::string& centerCode, const DistributionCenterManager* manager) {
    if (manager) {
        return manager->hasCenter(centerCode);
    }
    return false;
}

// Version con ID automático
void ConnectionService::createConnection(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance) {
    // Validar que los centros existan
    if (!centerExists(distributionCenterOrigin) || !centerExists(distributionCenterDestination)) {
        std::cout << "Error: Uno o ambos centros de distribucion no existen." << std::endl;
        std::cout << "Origen: " << distributionCenterOrigin << " - " << (centerExists(distributionCenterOrigin) ? "Existe" : "No existe") << std::endl;
        std::cout << "Destino: " << distributionCenterDestination << " - " << (centerExists(distributionCenterDestination) ? "Existe" : "No existe") << std::endl;
        return;
    }
    
    int id = generateNextId();
    manager->createConnection(distributionCenterOrigin, distributionCenterDestination, distance);
    Connection newConnection(id, distributionCenterOrigin, distributionCenterDestination, distance);
    connections.push(newConnection);
    std::cout << "Conexion creada exitosamente con ID: " << id << std::endl;
}

void ConnectionService::createConnectionWithoutValidation(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance) {
    int id = generateNextId();
    Connection newConnection(id, distributionCenterOrigin, distributionCenterDestination, distance);
    connections.push(newConnection);
    // No mostrar mensaje - se maneja en el DistributionCenterManager
}

void ConnectionService::createBidirectionalConnection(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance) {
    // Crear conexion de ida
    createConnection(distributionCenterOrigin, distributionCenterDestination, distance);
    
    // Crear conexion de vuelta
    createConnection(distributionCenterDestination, distributionCenterOrigin, distance);
    
    std::cout << "Conexion bidireccional creada: " << distributionCenterOrigin << " <-> " << distributionCenterDestination << " (" << distance << " km)" << std::endl;
}

void ConnectionService::createBidirectionalConnectionWithoutValidation(const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance) {
    // Crear conexión de ida
    createConnectionWithoutValidation(distributionCenterOrigin, distributionCenterDestination, distance);
    
    // Crear conexión de vuelta
    createConnectionWithoutValidation(distributionCenterDestination, distributionCenterOrigin, distance);
    
    // No mostrar mensaje - se maneja en el DistributionCenterManager
}

void ConnectionService::createConnection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance) {
    // Validar que los centros existan
    if (!centerExists(distributionCenterOrigin) || !centerExists(distributionCenterDestination)) {
        std::cout << "Error: Uno o ambos centros de distribucion no existen." << std::endl;
        std::cout << "Origen: " << distributionCenterOrigin << " - " << (centerExists(distributionCenterOrigin) ? "Existe" : "No existe") << std::endl;
        std::cout << "Destino: " << distributionCenterDestination << " - " << (centerExists(distributionCenterDestination) ? "Existe" : "No existe") << std::endl;
        return;
    }
    
    Connection newConnection(id, distributionCenterOrigin, distributionCenterDestination, distance);
    connections.push(newConnection);
    std::cout << "Conexion creada exitosamente." << std::endl;
}

Connection* ConnectionService::getConnectionById(int id) {
    Node* current = connections.getHead();
    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            if (conn.getId() == id) {
                return new Connection(conn); // Return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}

void ConnectionService::updateConnection(int id, const std::string& distributionCenterOrigin, const std::string& distributionCenterDestination, double distance) {
    List newList;
    Node* current = connections.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            if (conn.getId() == id) {
                Connection updatedConnection(id, distributionCenterOrigin, distributionCenterDestination, distance);
                newList.push(updatedConnection);
                found = true;
            } else {
                newList.push(conn);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        connections = newList;
        std::cout << "Conexion actualizada exitosamente." << std::endl;
    } else {
        std::cout << "Conexion con ID " << id << " no encontrada." << std::endl;
    }
}

void ConnectionService::deleteConnection(int id) {
    List newList;
    Node* current = connections.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            if (conn.getId() == id) {
                found = true;
                // Skip adding this connection to the new list
            } else {
                newList.push(conn);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        connections = newList;
        std::cout << "Conexion eliminada exitosamente." << std::endl;
    } else {
        std::cout << "Conexion con ID " << id << " no encontrada." << std::endl;
    }
}

void ConnectionService::displayAllConnections() {
    std::cout << "\n=== CONEXIONES (Connection Service) ===" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    if (connections.isEmpty()) {
        std::cout << "No hay conexiones registradas en el Connection Service." << std::endl;
        std::cout << "(Las conexiones se manejan principalmente en el Distribution Center Manager)" << std::endl;
    } else {
        Node* current = connections.getHead();
        int index = 1;
        while (current != nullptr) {
            try {
                Connection conn = std::any_cast<Connection>(current->getData());
                std::cout << std::setw(3) << index << ". ";
                conn.display();
                index++;
            } catch (const std::bad_any_cast& e) {
                std::cout << "Error displaying connection" << std::endl;
            }
            current = current->getNext();
        }
    }
    std::cout << std::string(60, '-') << std::endl;
}

int ConnectionService::getConnectionCount() {
    return connections.getSize();
}