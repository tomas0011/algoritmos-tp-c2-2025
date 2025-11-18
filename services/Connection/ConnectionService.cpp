#include "ConnectionService.h"
#include <iostream>

ConnectionService::ConnectionService(List& connectionsList) : connections(connectionsList) {}

void ConnectionService::createConnection(int id, int distributionCenterOrigin, int distributionCenterDestination, double distance) {
    Connection newConnection(id, distributionCenterOrigin, distributionCenterDestination, distance);
    connections.push(newConnection);
    std::cout << "Connection created successfully." << std::endl;
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

void ConnectionService::updateConnection(int id, int distributionCenterOrigin, int distributionCenterDestination, double distance) {
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
        std::cout << "Connection updated successfully." << std::endl;
    } else {
        std::cout << "Connection with ID " << id << " not found." << std::endl;
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
        std::cout << "Connection deleted successfully." << std::endl;
    } else {
        std::cout << "Connection with ID " << id << " not found." << std::endl;
    }
}

void ConnectionService::displayAllConnections() {
    std::cout << "All Connections:" << std::endl;
    Node* current = connections.getHead();
    while (current != nullptr) {
        try {
            Connection conn = std::any_cast<Connection>(current->getData());
            conn.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error displaying connection" << std::endl;
        }
        current = current->getNext();
    }
}

int ConnectionService::getConnectionCount() {
    return connections.getSize();
}