#include "shipmentService.h"
#include <iostream>

ShipmentService::ShipmentService(List& shipmentsList) : shipments(shipmentsList) {}

void ShipmentService::createShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                                    double totalWeight, int shimpmentManagerId, int distributionCenterId,
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
                                    double totalWeight, int shimpmentManagerId, int distributionCenterId,
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
