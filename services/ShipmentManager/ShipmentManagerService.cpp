#include "ShipmentManagerService.h"
#include <iostream>
#include <unordered_map>

ShipmentManagerService::ShipmentManagerService(List& shipmentManagersList) : shipmentManagers(shipmentManagersList) {}

void ShipmentManagerService::createShipmentManager(int id, int transportId, const List& path, int distributionCenterId) {
    ShipmentManager newShipmentManager(id, transportId, path, distributionCenterId);
    shipmentManagers.push(newShipmentManager);
    std::cout << "Shipment Manager created successfully." << std::endl;
}

ShipmentManager* ShipmentManagerService::getShipmentManagerById(int id) {
    Node* current = shipmentManagers.getHead();
    while (current != nullptr) {
        try {
            ShipmentManager sm = std::any_cast<ShipmentManager>(current->getData());
            if (sm.getId() == id) {
                return new ShipmentManager(sm); // Return a copy
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }
    return nullptr;
}

void ShipmentManagerService::updateShipmentManager(int id, int transportId, const List& path, int distributionCenterId) {
    List newList;
    Node* current = shipmentManagers.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            ShipmentManager sm = std::any_cast<ShipmentManager>(current->getData());
            if (sm.getId() == id) {
                ShipmentManager updatedShipmentManager(id, transportId, path, distributionCenterId);
                newList.push(updatedShipmentManager);
                found = true;
            } else {
                newList.push(sm);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        shipmentManagers = newList;
        std::cout << "Shipment Manager updated successfully." << std::endl;
    } else {
        std::cout << "Shipment Manager with ID " << id << " not found." << std::endl;
    }
}

void ShipmentManagerService::deleteShipmentManager(int id) {
    List newList;
    Node* current = shipmentManagers.getHead();
    bool found = false;

    while (current != nullptr) {
        try {
            ShipmentManager sm = std::any_cast<ShipmentManager>(current->getData());
            if (sm.getId() == id) {
                found = true;
            } else {
                newList.push(sm);
            }
        } catch (const std::bad_any_cast& e) {
            // Skip invalid entries
        }
        current = current->getNext();
    }

    if (found) {
        shipmentManagers = newList;
        std::cout << "Shipment Manager deleted successfully." << std::endl;
    } else {
        std::cout << "Shipment Manager with ID " << id << " not found." << std::endl;
    }
}

void ShipmentManagerService::displayAllShipmentManagers() {
    std::cout << "Shipment Managers List:" << std::endl;
    Node* current = shipmentManagers.getHead();
    while (current != nullptr) {
        try {
            ShipmentManager sm = std::any_cast<ShipmentManager>(current->getData());
            sm.display();
        } catch (const std::bad_any_cast& e) {
            std::cout << "Error displaying Shipment Manager" << std::endl;
        }
        current = current->getNext();
    }
}

int ShipmentManagerService::getShipmentManagerCount() {
    return shipmentManagers.getSize();
}
