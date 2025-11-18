#include "shipmentService.h"
#include <iostream>
#include <unordered_map>

ShipmentService::ShipmentService(List& shipmentsList) : shipments(shipmentsList) {}

void ShipmentService::createShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                                    double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                                    const std::vector<Package>& packages, int originId, int destinationId,
                                    int clientId, time_t createDate, time_t leftWarehouseDate,
                                    time_t estimatedDeliveryDate, time_t deliveryDate) {
    Shipment newShipment(id, state, cost, priority, totalPrice, totalWeight, shimpmentManagerId,
                        distributionCenterId, packages, originId, destinationId, clientId,
                        createDate, leftWarehouseDate, estimatedDeliveryDate, deliveryDate);
    shipments.push(newShipment);
    std::cout << "Shipment created successfully." << std::endl;
}

Shipment* ShipmentService::getShipmentById(int id) {
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            if (ship.getId() == id) {
                return new Shipment(ship); // Return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}

void ShipmentService::updateShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                                    double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                                    const std::vector<Package>& packages, int originId, int destinationId,
                                    int clientId, time_t createDate, time_t leftWarehouseDate,
                                    time_t estimatedDeliveryDate, time_t deliveryDate) {
    List newList;
    Node* current = shipments.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            if (ship.getId() == id) {
                Shipment updatedShipment(id, state, cost, priority, totalPrice, totalWeight, shimpmentManagerId,
                                        distributionCenterId, packages, originId, destinationId, clientId,
                                        createDate, leftWarehouseDate, estimatedDeliveryDate, deliveryDate);
                newList.push(updatedShipment);
                found = true;
            } else {
                newList.push(ship);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        shipments = newList;
        std::cout << "Shipment updated successfully." << std::endl;
    } else {
        std::cout << "Shipment with ID " << id << " not found." << std::endl;
    }
}

void ShipmentService::deleteShipment(int id) {
    List newList;
    Node* current = shipments.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            if (ship.getId() != id) {
                newList.push(ship);
            } else {
                found = true;
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        shipments = newList;
        std::cout << "Shipment deleted successfully." << std::endl;
    } else {
        std::cout << "Shipment with ID " << id << " not found." << std::endl;
    }
}

void ShipmentService::displayAllShipments() {
    std::cout << "All Shipments:" << std::endl;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            ship.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error displaying shipment" << std::endl;
        }
        current = current->getNext();
    }
}

int ShipmentService::getShipmentCount() {
    return shipments.getSize();
}



//Punto B

int ShipmentService::totalShipmentsByCenterAndDate(std::string centerId, time_t start, time_t end) {
    int count = 0;
    Node* current = shipments.getHead();

    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            if (ship.getDistributionCenterId() == centerId &&
                ship.getCreateDate() >= start && ship.getCreateDate() <= end) {
                count++;
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }

    // Complejidad temporal: O(n)
    return count;
}

std::vector<std::string> ShipmentService::overloadedCenters(int weeklyLimit) {
    std::unordered_map<std::string, int> shipmentCount;
    std::vector<std::string> overloaded;
    Node* current = shipments.getHead();

    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            shipmentCount[ship.getDistributionCenterId()]++;
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }

    for (const auto& [centerId, count] : shipmentCount) {
        if (count > weeklyLimit) {
            overloaded.push_back(centerId);
        }
    }

    // Complejidad temporal: O(n)
    return overloaded;
}

std::vector<Shipment> ShipmentService::findShipmentsByClient(int clientId) {
    std::vector<Shipment> result;
    Node* current = shipments.getHead();

    while (current != nullptr) {
        try {
            Shipment ship = std::any_cast<Shipment>(current->getData());
            if (ship.getClientId() == clientId) {
                result.push_back(ship);
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }

    // Complejidad temporal: O(n)
    return result;
}