#include "ShipmentManager.h"
#include <iostream>
#include "../../utils/algorithms/knapsackProblem/Knapsack.cpp"
#include "../services/TransportService.h"
#include "../entities/distributionCenterManager/DistributionCenterManager.h"
#include "../entities/distributionCenter/DistributionCenter.h"

ShipmentManager::ShipmentManager(int id, int transportId, const std::vector<Connection>& path, int distributionCenterId)
    : id(id), transportId(transportId), path(path), distributionCenterId(distributionCenterId) {}

void ShipmentManager::display() const {
    std::cout << "ID: " << id << ", TransportId: " << transportId
              << ", DistributionCenterId: " << distributionCenterId << std::endl;
    for (const auto& conn : path) {
        conn.display();
    }
}

int ShipmentManager::getId() const { return id; }
int ShipmentManager::getTransportId() const { return transportId; }
const std::vector<Connection>& ShipmentManager::getPath() const { return path; }
int ShipmentManager::getDistributionCenterId() const { return distributionCenterId; }

// -----------------------------------------------------
//        NUEVO MÉTODO: GENERAR CARGA ÓPTIMA
// -----------------------------------------------------
std::vector<Package> ShipmentManager::generarCargaOptima() const {

    // 1. Obtener el transporte
    TransportService transportService;
    Transport transporte = transportService.getTransportById(transportId);

    double capacidad = transporte.getMaxWeight();
    if (capacidad <= 0) {
        std::cout << "[Error] Transporte sin capacidad válida.\n";
        return {};
    }

    // 2. Obtener el DistributionCenter asociado
    DistributionCenterManager manager;
    DistributionCenter* centro = manager.getById(distributionCenterId);

    if (!centro) {
        std::cout << "[Error] Centro de distribución inválido.\n";
        return {};
    }

    // 3. Obtener los paquetes del warehouse
    List* paquetesDisponibles = centro->getWarehouse();

    // 4. Ejecutar la mochila 0-1
    ResultadoMochila resultado = resolverMochila(
        *paquetesDisponibles,
        capacidad
    );

    // 5. Devolver los seleccionados
    return resultado.paquetesSeleccionados;
}