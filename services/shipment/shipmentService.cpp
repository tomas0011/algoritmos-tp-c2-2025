#include "shipmentService.h"
#include <iostream>
#include <unordered_map>

ShipmentService::ShipmentService(
    TransportService* transportService,
    DistributionCenterService* distributionCenterService,
    List& shipmentsList) : shipments(shipmentsList) {}

void ShipmentService::createShipment(int id, const std::string& state, double cost, int priority, double totalPrice,
                                    double totalWeight, int shimpmentManagerId, std::string distributionCenterId,
                                    const std::vector<Package>& packages, std::string originId, std::string destinationId,
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
                                    const std::vector<Package>& packages, std::string originId, std::string destinationId,
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

std::vector<std::string> ShipmentService::overloadedCenters() {
    std::unordered_map<std::string, int> shipmentCount;
    std::vector<std::string> overloaded;
    Node* current = shipments.getHead();

    while (current != nullptr) {
        try {
            Shipment shipment = std::any_cast<Shipment>(current->getData());
            shipmentCount[shipment.getDistributionCenterId()]++;
        } catch (const std::bad_any_cast&) {}
        current = current->getNext();
    }

    for (const auto& [centerId, count] : shipmentCount) {
        DistributionCenter* center = distributionCenterService->getCenter(centerId);
        int weeklyLimit = center ? center->getDailyPackages() * 7 : 0;
        std::cout << "Limite semanal de " << center->getCode() << " es: " << weeklyLimit << std::endl;
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

std::vector<Package> ShipmentService::generateOptimalCargoForTransport(int transportId, std::string distributionCenterId) const {
    // 1. Obtener el transporte
    Transport* transporte = transportService->getTransportById(transportId);
    if (!transporte) {
        std::cout << "[Error] Transporte no encontrado.\n";
        return {};
    }

    double capacidad = transporte->getMaxWeight();
    if (capacidad <= 0) {
        std::cout << "[Error] Transporte sin capacidad válida.\n";
        delete transporte;
        return {};
    }

    // 2. Obtener el DistributionCenter asociado
    DistributionCenter* centro = distributionCenterService->getCenter(distributionCenterId);

    if (!centro) {
        std::cout << "[Error] Centro de distribución inválido.\n";
        delete transporte;
        return {};
    }

    // 3. Obtener los paquetes del warehouse
    std::vector<Package> paquetesDisponibles = centro->getWarehouse();
    List* availablePackagesList = new List();
    for (const Package& pkg : paquetesDisponibles) {
        availablePackagesList->push(pkg);
    }    

    // 4. Ejecutar la mochila 0-1
    ResultadoMochila resultado = resolverMochila(
        *availablePackagesList,
        capacidad
    );

    // 5. Devolver los seleccionados
    delete transporte;
    delete centro;
    return resultado.paquetesSeleccionados;
}
