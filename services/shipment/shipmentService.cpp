#include "shipmentService.h"
//#include "../../utils/algorithms/sort/mergeSort.cpp"  // Comentado para evitar múltiples definiciones
#include <iostream>
#include <sstream>
#include <iomanip>

ShipmentService::ShipmentService(
    TransportService* transportService,
    PackageService* packageService,
    DistributionCenterService* distributionCenterService,
    List& shipmentsList)
    : transportService(transportService),
    packageService(packageService),
    distributionCenterService(distributionCenterService),
    shipments(shipmentsList) {}

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
    std::unordered_map<std::string, int> shipmentCount;
    List overloaded;
    Node* current = shipments.getHead();
    while (current != nullptr) {
        try {
            Shipment* shipment = std::any_cast<Shipment*>(current->getData());
            shipmentCount[shipment->getDistributionCenterId()]++;
        } catch (const std::bad_any_cast&) {
            std::cout << "UN ERROR" << std::endl;
        }
        current = current->getNext();
    }
    for (const auto& [centerId, count] : shipmentCount) {
        DistributionCenter* center = distributionCenterService->getCenter(centerId);
        int weeklyLimit = center ? center->getDailyPackages() * 7 : 0;
        if (center) {
            std::cout << "Limite semanal de " << center->getCode() << " es " << weeklyLimit << " y tiene " << count << std::endl;
        } else {
            std::cout << "Centro no encontrado para ID: " << centerId << ", limite semanal: " << weeklyLimit << std::endl;
        }
        if (count > weeklyLimit) {
            overloaded.push(centerId);
        }
    }
    return overloaded;
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

List ShipmentService::generateOptimalCargoForTransport(int transportId, std::string distributionCenterId) const {
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

    // 2. Obtener los paquetes del warehouse
    std::cout << "[DEBUG] 1\n";
    List& availablePackagesList = packageService->getPackagesOfCenter(distributionCenterId);

    std::cout << "[DEBUG] 2\n";
    // 3. Ejecutar la mochila 0-1
    ResultadoMochila resultado = resolverMochila(
        availablePackagesList,
        capacidad
    );
    std::cout << "[DEBUG] 3\n";

    // 4. Devolver los seleccionados
    delete transporte;
    List selected = resultado.paquetesSeleccionados;
    return selected;
}
