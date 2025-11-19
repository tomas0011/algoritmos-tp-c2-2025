#include "ShipmentManagerService.h"
#include <iostream>
#include "../../utils/algorithms/knapsackProblem/knapsack.h"
#include <any>

ShipmentManagerService::ShipmentManagerService(
    TransportService* transportService,
    DistributionCenterService* distributionCenterService,
    List& shipmentManagersList)
    : shipmentManagers(shipmentManagersList) {
    // Store the service pointers for use in methods
    this->transportService = transportService;
    this->distributionCenterService = distributionCenterService;
}

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

// -----------------------------------------------------
//        NUEVO MÉTODO: GENERAR CARGA ÓPTIMA
// -----------------------------------------------------
List ShipmentManagerService::generarCargaOptima(int transportId, std::string distributionCenterId) const {
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
    const List& paquetesDisponibles = centro->getWarehouse();

    // Hacer una copia porque el knapsack lo recibe por referencia no const
    List availablePackagesList = paquetesDisponibles;

    // List* availablePackagesList = new List();
    // for (const Package& pkg : paquetesDisponibles) {
    //     availablePackagesList->push(pkg);
    // }    

    // 4. Ejecutar la mochila 0-1
    ResultadoMochila resultado = resolverMochila(
        availablePackagesList,
        capacidad
    );

    // 5. Devolver los seleccionados convertidos a List
    List result;
    for (const Package& pkg : resultado.paquetesSeleccionados) {
        result.push(std::any(pkg));
    }
    
    delete transporte;
    delete centro;
    return result;
}
