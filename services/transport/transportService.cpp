#include "transportService.h"
#include <iostream>

TransportService::TransportService(List& transportsList) : transports(transportsList) {}

void TransportService::createTransport(int id, const std::string& type, double maxWeight) {
    Transport newTransport(id, type, maxWeight);
    transports.push(newTransport);
    std::cout << "Transport created successfully." << std::endl;
}

Transport* TransportService::getTransportById(int id) {
    Node* current = transports.getHead();
    while (current != nullptr) {
        try {
            Transport tr = std::any_cast<Transport>(current->getData());
            if (tr.getId() == id) {
                return new Transport(tr); // Return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}
void TransportService::updateTransport(int id, const std::string& type, double maxWeight) {
    List newList;
    Node* current = transports.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Transport tr = std::any_cast<Transport>(current->getData());
            if (tr.getId() == id) {
                Transport updatedTransport(id, type, maxWeight);
                newList.push(updatedTransport);
                found = true;
            } else {
                newList.push(tr);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        transports = newList;
        std::cout << "Transport updated successfully." << std::endl;
    } else {
        std::cout << "Transport with ID " << id << " not found." << std::endl;
    }
}

void TransportService::deleteTransport(int id) {
    List newList;
    Node* current = transports.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Transport tr = std::any_cast<Transport>(current->getData());
            if (tr.getId() == id) {
                found = true;
                // Skip adding this transport to the new list
            } else {
                newList.push(tr);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        transports = newList;
        std::cout << "Transport deleted successfully." << std::endl;
    } else {
        std::cout << "Transport with ID " << id << " not found." << std::endl;
    }
}

void TransportService::displayAllTransports() {
    std::cout << "All Transports:" << std::endl;
    Node* current = transports.getHead();
    while (current != nullptr) {
        try {
            Transport tr = std::any_cast<Transport>(current->getData());
            tr.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "error displaying transport" << std::endl;
        }
        current = current->getNext();
    }
}
int TransportService::getTransportCount() {
    return transports.getSize();
}