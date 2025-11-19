#include "shipmentService.h"
//#include "../../utils/algorithms/sort/mergeSort.cpp"  // Comentado para evitar múltiples definiciones
#include <iostream>
#include <sstream>
#include <iomanip>

ShipmentService::ShipmentService(List& shipmentsList) : shipments(shipmentsList) {}

void ShipmentService::createShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                                    double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                                    const List& packages, std::string originId, std::string destinationId,
                                    int clientId, time_t createDate, time_t leftWarehouseDate,
                                    time_t estimatedDeliveryDate, time_t deliveryDate) {
    Shipment* newShipment = new Shipment(id, state, cost, priority, totalPrice, totalWeight, shimpmentManagerId,
                                        distributionCenterId, packages, originId, destinationId, clientId,
                                        createDate, leftWarehouseDate, estimatedDeliveryDate, deliveryDate);
    shipments.push(newShipment);
}

Shipment* ShipmentService::getShipmentById(int id) {
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            if (shipment->getId() == id) {
                return shipment;
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    return nullptr;
}

void ShipmentService::updateShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                                    double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                                    const List& packages, std::string originId, std::string destinationId,
                                    int clientId, time_t createDate, time_t leftWarehouseDate,
                                    time_t estimatedDeliveryDate, time_t deliveryDate) {
    Shipment* shipment = getShipmentById(id);
    if (shipment) {
        // Update logic would go here - creating new shipment with updated values
        // For now, just delete and recreate
        deleteShipment(id);
        createShipment(id, state, cost, priority, totalPrice, totalWeight, shimpmentManagerId,
                      distributionCenterId, packages, originId, destinationId, clientId,
                      createDate, leftWarehouseDate, estimatedDeliveryDate, deliveryDate);
    }
}

void ShipmentService::deleteShipment(int id) {
    Node* current = shipments.getHead();
    Node* prev = nullptr;
    
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            if (shipment->getId() == id) {
                if (prev) {
                    prev->setNext(current->getNext());
                } else {
                    shipments.setHead(current->getNext());
                }
                delete shipment;
                delete current;
                return;
            }
        } catch (const std::bad_any_cast&) {}
        prev = current;
        current = current->getNext();
    }
}

void ShipmentService::displayAllShipments() {
    std::cout << "All Shipments:" << std::endl;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            shipment->display();
            std::cout << "------------------------" << std::endl;
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
}

int ShipmentService::getShipmentCount() {
    int count = 0;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }
    return count;
}

int ShipmentService::totalShipmentsByCenterAndDate(std::string centerId, time_t start, time_t end) {
    int count = 0;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            if (shipment->getDistributionCenterId() == centerId &&
                shipment->getCreateDate() >= start && shipment->getCreateDate() <= end) {
                count++;
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    return count;
}

List ShipmentService::overloadedCenters() {
    List result;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            result.push(shipment->getDistributionCenterId());
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    return result;
}

List ShipmentService::findShipmentsByClient(int clientId) {
    List result;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            if (shipment->getClientId() == clientId) {
                result.push(shipment);
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    return result;
}

List ShipmentService::generarCargaOptima(int transportId, std::string distributionCenterId) const {
    List result;
    
    // Get packages from distribution center warehouse
    Node* current = shipments.getHead();
    List availablePackages;
    
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            if (shipment->getDistributionCenterId() == distributionCenterId) {
                // Add packages from this shipment to available packages
                const List& packages = shipment->getPackages();
                Node* packageNode = packages.getHead();
                while (packageNode != nullptr) {
                    availablePackages.push(packageNode->getData());
                    packageNode = packageNode->getNext();
                }
            }
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }
    
    // Use knapsack algorithm to optimize load
    // This would require converting List to array for knapsack algorithm
    // For now, return first few packages (simplified)
    Node* packageNode = availablePackages.getHead();
    int count = 0;
    while (packageNode != nullptr && count < 5) {
        result.push(packageNode->getData());
        packageNode = packageNode->getNext();
        count++;
    }
    
    return result;
}